/*! \file map.c
 *  \brief Map data structure implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"
#include "structs/map.h"
#include "structs/vla.h"

static long umap_search(map_t *map, const void *key) {
  unsigned long i;
  pair_t *p;

  for (i = 0; i < umap_size(map); i++) {
    // we don't take ownership of p here
    if (vla_getp(&map->vla, i, (void *)&p) < 0)
      return ERR_FAILURE;
    if (map->cmp(key, p->key, map->key_size) == 0)
      return i;
  }

  return map->vla.size;
}

static pair_t map_create_pair(map_t *map, const void *key, const void *val) {
  pair_t p = {.key = malloc(map->key_size), .val = malloc(map->val_size)};

  memcpy(p.key, key, map->key_size);
  memcpy(p.val, val, map->val_size);

  return p;
}

static inline int map_destroy_pair(pair_t *p) {
  if (!p || !p->key || !p->val)
    return ERR_NULL;

  free(p->key);
  free(p->val);
  return ERR_NONE;
}

int map_init(map_t *map, const size_t key_size, const size_t val_size,
              int (*cmp)(const void *, const void *, size_t),
              const unsigned long initial_capacity) {
  if (!map)
    return ERR_NULL;

  if (key_size < 1 || val_size < 1 || initial_capacity < 1)
    return ERR_EMPTY;

  if (vla_init(&map->vla, sizeof(pair_t), initial_capacity) < 0)
    return ERR_FAILURE;

  map->key_size = key_size;
  map->val_size = val_size;
  map->cmp = cmp;

  return ERR_NONE;
}

int map_deinit(map_t *map) {
  if (!map)
    return ERR_NULL;

  int i;
  pair_t *p;
  for (i = 0; i < umap_size(map); i++) {
    if (vla_getp(&map->vla, i, (void *)&p) < 0)
      return ERR_FAILURE;
    if (map_destroy_pair(p) < 0)
      return ERR_FAILURE;
  }

  if (vla_deinit(&map->vla) < 0)
    return ERR_FAILURE;

  map->key_size = map->val_size = 0;
  map->cmp = NULL;

  return ERR_NONE;
}

int umap_set(map_t *map, const void *key, const void *val) {
  if (!map || !map->vla.elements)
    return ERR_NULL;

  long i = umap_search(map, key);

  if (i < 0)
    return ERR_FAILURE;

  pair_t p = map_create_pair(map, key, val);
  if (i == umap_size(map)) {
    if (vla_enq(&map->vla, (void *)&p) < 0)
      return ERR_FAILURE;
  } else {
    if (vla_set(&map->vla, i, (void *)&p) < 0)
      return ERR_FAILURE;
  }

  return ERR_NONE;
}

// TODO: omap_set
int omap_set(map_t *map, const void *key, const void *val) {
  return 0;
}

int umap_get(map_t *map, const void *key, void *val) {
  if (!map || !map->vla.elements)
    return ERR_NULL;

  if (umap_size(map) < 1)
    return ERR_EMPTY;

  long i = umap_search(map, key);

  if (i < 0 || i == umap_size(map))
    return ERR_NOT_FOUND;

  pair_t *p;
  // vla_getp to avoid double copy
  if (vla_getp(&map->vla, i, (void *)&p) < 0)
    return ERR_FAILURE;

  memcpy(val, p->val, map->val_size);

  return ERR_NONE;
}

// TODO: omap_get
int omap_get(map_t *map, const void *key, void *val) {
  return 0;
}

// TODO: umap_getp
int umap_getp(map_t *map, const void *key, void **val) {
  return 0;
}

// TODO: omap_getp
int omap_getp(map_t *map, const void *key, void **val) {
  return 0;
}

int umap_del(map_t *map, const void *key) {
  if (!map || !map->vla.elements)
    return ERR_NULL;

  if (umap_size(map) < 1)
    return ERR_EMPTY;

  long i = umap_search(map, key);

  if (i < 0 || i == umap_size(map))
    return ERR_NOT_FOUND;

  pair_t *p;
  // vla_getp to access heap pointer, instead of copying
  if (vla_getp(&map->vla, i, (void *)&p) < 0)
    return ERR_FAILURE;

  if (map_destroy_pair(p) < 0)
    return ERR_FAILURE;

  if (vla_del(&map->vla, i) < 0)
    return ERR_FAILURE;

  return ERR_NONE;
}

// TODO: omap_del
int omap_del(map_t *map, const void *key) {
  return 0;
}

int map_clear(map_t *map) {
  if (!map || !map->vla.elements)
    return ERR_FAILURE;

  if (vla_clear(&map->vla) < 0)
    return ERR_FAILURE;

  return ERR_NONE;
}

inline long map_size(map_t *map) { return vla_size(&map->vla); }

int map_keys(map_t *map, void *keys) {
  if (!map || !keys)
    return ERR_NULL;

  long i;
  pair_t *p;

  for (i = 0; i < umap_size(map); i++) {
    // vla_getp for subsequent copy, to avoid double copying
    if (vla_getp(&map->vla, i, (void *)&p) < 0)
      return ERR_FAILURE;

    memcpy(keys + (i * map->key_size), p->key, map->key_size);
  }

  return ERR_NONE;
}

int map_vals(map_t *map, void *vals) {
  if (!map || !vals)
    return ERR_NULL;

  int i;
  pair_t *p;

  for (i = 0; i < umap_size(map); i++) {
    if (vla_getp(&map->vla, i, (void *)&p) < 0)
      return ERR_FAILURE;

    memcpy(vals + (i * map->val_size), p->val, map->val_size);
  }

  return ERR_NONE;
}

int map_pairs(map_t *map, pair_t *pairs) {
  if (!map || !pairs)
    return ERR_NULL;

  int i;
  pair_t *p;

  for (i = 0; i < umap_size(map); i++) {
    if (vla_getp(&map->vla, i, (void *)&p) < 0)
      return ERR_FAILURE;

    memcpy(pairs + i, p, sizeof(pair_t));
  }

  return ERR_NONE;
}
