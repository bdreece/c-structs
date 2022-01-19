/**
 * \file    util.hpp
 * \brief   Testing library utility functions
 * \author  Brian Reece
 * \date    12/28/2021
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <stddef.h>

int cmp(const void *a, const void *b, size_t size) {
  if (*(char *)a < *(char *)b)
    return -1;
  else if (*(char *)a > *(char *)b)
    return 1;
  else
    return 0;
}

#endif  // UTIL_HPP
