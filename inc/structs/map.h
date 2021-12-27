/*! \file map.h
 *  \brief Map data structure
 *  \author Brian Reece
 *  \version 0.1.0
 */

#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "structs/vla.h"

typedef struct pair {
  void *key, *val;
} pair_t;

typedef struct map {
  vla_t vla;
  size_t key_size, val_size;
  bool ordered;
  int (*cmp)(const void *, const void *, size_t);
} map_t;

int map_init(map_t *map, const size_t key_size, const size_t val_size,
              int (*cmp)(const void *, const void *, size_t),
              const unsigned long initial_capacity);

int map_deinit(map_t *map);

int map_set(map_t *map, const void *key, const void *val);

int map_get(map_t *map, const void *key, void *val);

int map_getp(map_t *map, const void *key, void **val);

int map_del(map_t *map, const void *key);

int map_clear(map_t *map);

extern long map_size(map_t *map);

int map_keys(map_t *map, void *keys);

int map_vals(map_t *map, void *vals);

int map_pairs(map_t *map, pair_t *pairs);

#ifdef __cplusplus
}
#endif

#endif // MAP_H
