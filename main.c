#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>

void print_usage();

int swap_names(int first_fd, const char *first_path, int second_fd, const char *second_path);

int main(int argc, char **argv) {
    static int help_flag;
    static int verbose_flag;
    static struct option long_options[] = {
            {.name = "help", .has_arg = no_argument, .flag = &help_flag, .val = 0},
            {.name = "verbose", .has_arg = no_argument, .flag = &verbose_flag, .val = 0}
    };
    int c;
    int option_index = 0;
    while (1) {
        c = getopt_long(argc, argv, "hv", long_options, &option_index);

        if (c == -1) break;

        switch (c) {
            case 0:
                break;
            case 'h':
                help_flag = 1;
                break;
            case 'v':
                verbose_flag = 1;
                break;
            case '?':
                break;
            default:
                abort();
        }
    }

    if (help_flag) {
        print_usage();
        return 0;
    }

    if (argc - optind != 2) {
        print_usage();
        return 0;
    }

    const char *from = argv[optind];
    const char *to = argv[optind + 1];

    if (swap_names(AT_FDCWD, from, AT_FDCWD, to) != 0) {
        fprintf(stderr, "swap: swap %s with %s: %s\n", from, to, strerror(errno));
        return -1;
    }

    if (verbose_flag) {
        printf("swap: %s <-> %s\n", from, to);
    }

    return 0;
}

void print_usage() {
    printf("usage: swap [-v] file1 file2\n");
}

int swap_names(int first_fd, const char *first_path, int second_fd, const char *second_path) {
#if defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_12
    return renameatx_np(first_fd, first_path, second_fd, second_path, RENAME_SWAP);
#elif __has_feature(renameat2)
    return renameat2(first_fd, first_path, second_fd, second_path, RENAME_EXCHANGE);
#else
    // TODO make this an atomic operation
    char temp_name[7] = "XXXXXX";
    if (!mktemp(temp_name)) return -1;
    int err;
    if ((err = renameat(first_fd, first_path, first_fd, temp_name)) != 0) return err;
    if ((err = renameat(second_fd, second_path, first_fd, first_path)) != 0) return err;
    if ((err = renameat(first_fd, temp_name, second_fd, second_path)) != 0) return err;
    return 0;
#endif
}
