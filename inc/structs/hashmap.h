/**
 * \file    hashmap.h
 * \brief   Hashmap data structure
 * \author  Brian Reece
 * \date    12/27/2021
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

#include "structs/map.h"
#include "structs/vla.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hashmap {
  vla_t vla;
  size_t key_size, val_size;
  int (*cmp)(const void *, const void *, size_t);
  long (*search)(const struct map *, const void *);
  float load_factor;
} hashmap_t;

int hashmap_init(hashmap_t *map, size_t key_size, size_t val_size,
                 int (*cmp)(const void *, const void *, size_t),
                 float load_factor);

int hashmap_deinit(hashmap_t *map);

#ifdef __cplusplus
}
#endif

#endif // HASHMAP_H
