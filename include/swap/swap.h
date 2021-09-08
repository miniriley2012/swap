//
// Created by Riley Quinn on 9/7/21.
//

#ifndef SWAP_SWAP_H
#define SWAP_SWAP_H

#include <stdio.h>

/// Swap the name of two files.
/// \param first_fd A file descriptor used to resolve first_path. May be `AT_FDCWD` to use the current directory
/// \param first_path first path to swap relative to first_fd
/// \param second_fd A file descriptor used to resolve second_path. May be `AT_FDCWD` to use the current directory
/// \param second_path second path to swap relative to second_fd
/// \return 0 on success or -1 on error, sets errno to the last error
int swap_names(int first_fd, const char *first_path, int second_fd, const char *second_path);

#endif //SWAP_SWAP_H
