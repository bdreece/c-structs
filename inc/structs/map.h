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

typedef struct umap {
  vla_t vla;
  size_t key_size, val_size;
  int (*cmp)(const void *, const void *, size_t);
} umap_t;

int umap_init(umap_t *map, const size_t key_size, const size_t val_size,
              int (*cmp)(const void *, const void *, size_t),
              const unsigned long initial_capacity);

int umap_deinit(umap_t *map);

int umap_set(umap_t *map, const void *key, const void *val);

int umap_get(umap_t *map, const void *key, void *val);

int umap_del(umap_t *map, const void *key);

int umap_clear(umap_t *map);

extern long umap_size(umap_t *map);

int umap_keys(umap_t *map, void *keys);

int umap_vals(umap_t *map, void *vals);

int umap_pairs(umap_t *map, pair_t *pairs);

#ifdef __cplusplus
}
#endif

#endif // MAP_H
