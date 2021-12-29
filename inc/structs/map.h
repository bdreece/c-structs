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
  int (*cmp)(const void *, const void *, size_t);
  long (*search)(const struct map *, const void *);
} map_t;

int map_init(map_t *map, const size_t key_size, const size_t val_size,
             bool ordered, int (*cmp)(const void *, const void *, size_t),
             const unsigned long initial_capacity);

int map_deinit(map_t *map);

int map_set(map_t *map, const void *key, const void *val);

bool map_contains(const map_t *map, const void *key);

int map_get(const map_t *map, const void *key, void *val);

int map_getp(const map_t *map, const void *key, void **val);

int map_del(map_t *map, const void *key);

int map_clear(map_t *map);

extern long map_size(const map_t *map);

int map_keys(const map_t *map, vla_t *keys);

int map_vals(const map_t *map, vla_t *vals);

int map_pairs(const map_t *map, vla_t *pairs);

#ifdef __cplusplus
}
#endif

#endif // MAP_H
