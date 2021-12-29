/**
 * \file    util.cpp
 * \brief   Utility functions' implementation
 * \author  Brian Reece
 * \date    12/28/2021
 */

#include "util.hpp"

int cmp(const void *a, const void *b, size_t size) {
  if (*(char *)a < *(char *)b)
    return -1;
  else if (*(char *)a > *(char *)b)
    return 1;
  else
    return 0;
}
