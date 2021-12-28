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
  float load_factor;
} hashmap_t;

int hashmap_init(hashmap_t *map, const size_t key_size, const size_t val_size,
                 int (*cmp)(const void *, const void *, size_t),
                 long initial_breadth, long depth, float load_factor);

int hashmap_deinit(hashmap_t *map);

int hashmap_get(const hashmap_t *map, const void *key, void *val);

int hashmap_getp(const hashmap_t *map, const void *key, void **val);

int hashmap_set(hashmap_t *map, const void *key, const void *val);

int hashmap_del(hashmap_t *map, const void *key);

int hashmap_clear(hashmap_t *map);

long hashmap_size(const hashmap_t *map);

int hashmap_keys(const hashmap_t *map, vla_t *keys);

int hashmap_vals(const hashmap_t *map, vla_t *vals);

int hashmap_pairs(const hashmap_t *map, vla_t *pairs);

#ifdef __cplusplus
}
#endif

#endif // HASHMAP_H
