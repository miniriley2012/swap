#include <swap/swap.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

void print_usage();

void print_error(const char *format, ...) __printflike(1, 2);

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
        print_error("swap %s with %s: %s\n", from, to, strerror(errno));
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

void print_error(const char *format, ...) {
    fprintf(stderr, "swap: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
