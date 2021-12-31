/*! \file map.c
 *  \brief Map data structure implementation
 *  \author Brian Reece
 *  \version 0.1.1
 */

#include "structs/map.h"

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"
#include "structs/vla.h"

static inline pair_t map_create_pair(map_t *map, const void *key,
                                     const void *val) {
  pair_t p = {.key = malloc(map->key_size), .val = malloc(map->val_size)};

  ASSERT(memcpy(p.key, key, map->key_size) != NULL);
  ASSERT(memcpy(p.val, val, map->val_size) != NULL);

  return p;
}

static inline int map_destroy_pair(pair_t *p) {
  if (!p || !p->key || !p->val) return ERR_NULL;

  free(p->key);
  free(p->val);
  return ERR_NONE;
}

long umap_search(const struct map *map, const void *key) {
  if (!map || !map->vla.elements | !key) return ERR_NULL;

  int ret;
  long i;
  pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    // we don't take ownership of p here
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;
    if (map->cmp(key, p->key, map->key_size) == 0) return i;
  }

  return map_size(map);
}

long omap_search(const struct map *map, const void *key) {
  int ret, compare;
  long l, r, m;
  pair_t *p;

  l = 0;
  r = map_size(map);

  while (l <= r) {
    m = (long)(l + (r - l) / 2);

    // Not copying p here
    if ((ret = vla_getp(&map->vla, m, (void **)&p)) < 0) return ret;

    compare = map->cmp(key, p->key, map->key_size);

    if (compare > 0)
      l = m + 1;
    else if (compare < 0)
      r = m - 1;
    else
      return m;
  }

  return map_size(map);
}

int map_init(map_t *map, const size_t key_size, const size_t val_size,
             bool ordered, int (*cmp)(const void *, const void *, size_t),
             const unsigned long initial_capacity) {
  int ret;
  if (!map) return ERR_NULL;

  if (key_size < 1 || val_size < 1 || initial_capacity < 1)
    return ERR_INVALID_ARGUMENT;

  if ((ret = vla_init(&map->vla, sizeof(pair_t), initial_capacity)) < 0)
    return ret;

  map->key_size = key_size;
  map->val_size = val_size;
  map->cmp = cmp;

  if (ordered)
    map->search = omap_search;
  else
    map->search = umap_search;

  return ERR_NONE;
}

int map_deinit(map_t *map) {
  if (!map) return ERR_NULL;

  int i, ret;
  pair_t *p;
  for (i = 0; i < map_size(map); i++) {
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;
    if ((ret = map_destroy_pair(p)) < 0) return ret;
  }

  if ((ret = vla_deinit(&map->vla)) < 0) return ret;

  map->key_size = map->val_size = 0;
  map->cmp = NULL;
  map->search = NULL;

  return ERR_NONE;
}

int map_set(map_t *map, const void *key, const void *val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int ret;
  long i = map->search(map, key);

  // Got an error
  if (i < 0) return i;

  pair_t p = map_create_pair(map, key, val);

  if (i == map_size(map)) {
    // Key not found
    if ((ret = vla_enq(&map->vla, (void *)&p)) < 0) return ret;
  } else {
    // Key found
    if ((ret = vla_set(&map->vla, i, (void *)&p)) < 0) return ret;
  }

  return ERR_NONE;
}

// TODO: map_contains
bool map_contains(const map_t *map, const void *key) { return false; }

int map_get(const map_t *map, const void *key, void *restrict val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (map_size(map) < 1) return ERR_EMPTY;

  long i = map->search(map, key);

  // Got error
  if (i < 0) return i;

  // Key not found
  if (i == map_size(map)) return ERR_NOT_FOUND;

  int ret;
  pair_t *p;

  // vla_getp to avoid double copy
  if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

  // Copy val from pair
  ASSERT(memcpy(val, p->val, map->val_size) != NULL);

  return ERR_NONE;
}

int map_getp(const map_t *map, const void *key, void **restrict val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (map_size(map) < 1) return ERR_EMPTY;

  long i = map->search(map, key);

  // Got error
  if (i < 0) return i;

  // Key not found
  if (i == map_size(map)) return ERR_NOT_FOUND;

  int ret;
  pair_t *p;

  // vla_getp to avoid double copy
  if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

  // Copy pointer to val
  *val = p->val;

  return ERR_NONE;
}

int map_del(map_t *map, const void *key) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (map_size(map) < 1) return ERR_EMPTY;

  long i = map->search(map, key);

  // Got error
  if (i < 0) return i;

  // Key not found
  if (i == map_size(map)) return ERR_NOT_FOUND;

  int ret;
  pair_t *p;
  // vla_getp to access heap pointer, instead of copying
  if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

  if ((ret = map_destroy_pair(p)) < 0) return ret;

  if ((ret = vla_del(&map->vla, i)) < 0) return ret;

  return ERR_NONE;
}

int map_clear(map_t *map) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int ret;
  if ((ret = vla_clear(&map->vla)) < 0) return ret;

  return ERR_NONE;
}

inline long map_size(const map_t *map) { return vla_size(&map->vla); }

int map_keys(const map_t *map, vla_t *keys) {
  if (!map || !map->vla.elements || !keys || !keys->elements) return ERR_NULL;

  int ret;
  long i;
  pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    // vla_getp for subsequent copy, to avoid double copying
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

    if ((ret = vla_enq(keys, (const void *)p->key)) < 0) return ret;
  }

  return ERR_NONE;
}

int map_vals(const map_t *map, vla_t *vals) {
  if (!map || !map->vla.elements || !vals || !vals->elements) return ERR_NULL;

  int ret;
  long i;
  pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

    if ((ret = vla_enq(vals, (const void *)p->val)) < 0) return ret;
  }

  return ERR_NONE;
}

int map_pairs(const map_t *map, vla_t *pairs) {
  if (!map || !map->vla.elements || !pairs || !pairs->elements) return ERR_NULL;

  int ret;
  long i;
  pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

    if ((ret = vla_enq(pairs, (const void *)p)) < 0) return ret;
  }

  return ERR_NONE;
}
