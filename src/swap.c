//
// Created by Riley Quinn on 9/7/21.
//

#include "swap/swap.h"

#include <stdlib.h>

int swap_names(int first_fd, const char *first_path, int second_fd, const char *second_path) {
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_12
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
