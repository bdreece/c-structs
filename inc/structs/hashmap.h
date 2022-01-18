/**
 * \file        hashmap.h
 * \brief       Hashmap data structure
 * \author      Brian Reece
 * \version     v0.3-alpha
 * \date        12/27/2021
 */

#ifndef STRUCTS_HASHMAP_H
#define STRUCTS_HASHMAP_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif  // STRUCTS_DEF

#include <stdbool.h>
#include <stddef.h>

#ifdef STRUCTS_HASHMAP_IMPL
#define STRUCTS_MAP_IMPL
#include "structs/map.h"
#define STRUCTS_VLA_IMPL
#include "structs/vla.h"
#endif  // STRUCTS_HASHMAP_IMPL

//! \brief Hashmap data structure
typedef struct hashmap {
  vla_t vla;                                       //!< VLA of maps
  size_t key_size;                                 //!< Size of keys
  size_t val_size;                                 //!< Size of values
  int (*cmp)(const void *, const void *, size_t);  //!< Key comparison function
  long (*hash)(long, const void *);                //!< Key hashing function
} hashmap_t;

/*! \brief Hashmap construction function
 *  \details Initializes internal VLA and constructs
 *           `initial_breadth` maps of `depth` depth.
 *  \param[in] map The respective hashmap
 *  \param[in] key_size The size of keys
 *  \param[in] val_size The size of values
 *  \param[in] cmp The key comparison function
 *  \param[in] hash The key hashing function
 *  \param[in] initial_breadth The initial number of maps
 *  \param[in] depth The max depth of maps before rehashing
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int hashmap_init(hashmap_t *map, const size_t key_size,
                             const size_t val_size,
                             int (*cmp)(const void *, const void *, size_t),
                             long (*hash)(long, const void *),
                             long initial_breadth, long depth);

/*! \brief Hashmap destruction function
 *  \details Deinitializes and frees memory associated
 *           with the given hashmap.
 *  \param[in] map The respective hashmap
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int hashmap_deinit(hashmap_t *map);

/*! \brief Hashmap contains function
 *  \details Finds whether the given key exists in the
 *           map.
 *  \param[in] map The respective hashmap
 *  \param[in] key The given key
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF bool hashmap_contains(const hashmap_t *map, const void *key);

/*! \brief Hashmap get function
 *  \details Gets the value associated with the given
 *           key in the map, if it exists.
 *  \param[in] map The respective hashmap
 *  \param[in] key The given key
 *  \param[out] val The value, if found
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int hashmap_get(const hashmap_t *map, const void *key, void *val);

STRUCTS_DEF int hashmap_getp(const hashmap_t *map, const void *key, void **val);

STRUCTS_DEF int hashmap_set(hashmap_t *map, const void *key, const void *val);

STRUCTS_DEF int hashmap_del(hashmap_t *map, const void *key);

STRUCTS_DEF int hashmap_clear(hashmap_t *map);

STRUCTS_DEF long hashmap_size(const hashmap_t *map);

STRUCTS_DEF int hashmap_keys(const hashmap_t *map, vla_t *keys);

STRUCTS_DEF int hashmap_vals(const hashmap_t *map, vla_t *vals);

STRUCTS_DEF int hashmap_pairs(const hashmap_t *map, vla_t *pairs);

#ifdef STRUCTS_HASHMAP_IMPL

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"

static int hashmap_rehash(hashmap_t *map) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int i, ret;
  map_t *m;

  for (i = 0; i < vla_size(&map->vla); i++) {
  }

  return 0;
}

int hashmap_init(hashmap_t *map, const size_t key_size, const size_t val_size,
                 int (*cmp)(const void *, const void *, size_t),
                 long (*hash)(long, const void *), long initial_breadth,
                 long depth) {
  if (!map) return ERR_NULL;

  if (!cmp || key_size < 1 || val_size < 1 || initial_breadth < 1 || depth < 1)
    return ERR_INVALID_ARGUMENT;

  int i, ret;
  // VLA of pointers to maps
  if ((ret = vla_init(&map->vla, sizeof(map_t *), initial_breadth)) < 0)
    return ret;

  map->cmp = cmp;
  map->hash = hash;

  map_t *m;
  for (i = 0; i < initial_breadth; i++) {
    m = (map_t *)malloc(sizeof(map_t));
    if ((ret = map_init(m, key_size, val_size, true, cmp, depth)) < 0)
      return ret;

    // Copy pointer into vla
    if ((ret = vla_enq(&map->vla, (const void *)&m)) < 0) return ret;
  }

  return ERR_NONE;
}

int hashmap_deinit(hashmap_t *map) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int ret;
  long i, n = vla_size(&map->vla);
  map_t *m;

  for (i = 0; i < n; i++) {
    // Get map
    if ((ret = vla_get(&map->vla, i, (void *)&m)) < 0) return ret;

    // Deinitialize map
    if ((ret = map_deinit(m)) < 0) return ret;

    // Free map
    free(m);
  }

  // Deinitialize VLA
  if ((ret = vla_deinit(&map->vla)) < 0) return ret;

  map->key_size = map->val_size = 0;
  map->cmp = (int (*)(const void *, const void *, size_t))NULL;
  map->hash = (long (*)(long, const void *))NULL;

  return ERR_NONE;
}

// TODO: hashmap_contains
bool hashmap_contains(const hashmap_t *map, const void *key) { return false; }

int hashmap_get(const hashmap_t *map, const void *key, void *val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!key || !val) return ERR_INVALID_ARGUMENT;

  int ret;
  map_t *m;

  // Compute key hash
  long index = map->hash(hashmap_size(map), key);

  // Fetch corresponding map
  if ((ret = vla_get(&map->vla, index, (void *)&m)) < 0) return ret;

  // Get value from map
  if ((ret = map_get(m, key, val)) < 0) return ret;

  return ERR_NONE;
}

int hashmap_getp(const hashmap_t *map, const void *key, void **val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!key || !val) return ERR_INVALID_ARGUMENT;

  int ret;
  map_t *m;

  // Compute key hash
  long index = map->hash(hashmap_size(map), key);

  // Fetch corresponding map
  if ((ret = vla_get(&map->vla, index, (void *)&m)) < 0) return ret;

  if ((ret = map_getp(m, key, val)) < 0) return ret;

  return ERR_NONE;
}

int hashmap_set(hashmap_t *map, const void *key, const void *val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!key || !val) return ERR_INVALID_ARGUMENT;

  int ret;
  map_t *m;
  long index = map->hash(hashmap_size(map), key);

  if ((ret = vla_get(&map->vla, index, (void *)&m)) < 0) return ret;

  if ((ret = map_set(m, key, val)) < 0) return ret;

  return ERR_NONE;
}

int hashmap_del(hashmap_t *map, const void *key) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!key) return ERR_INVALID_ARGUMENT;

  int ret;
  map_t *m;
  long index = map->hash(hashmap_size(map), key);

  if ((ret = vla_get(&map->vla, index, (void *)&m)) < 0) return ret;

  if ((ret = map_del(m, key)) < 0) return ret;

  return ERR_NONE;
}

int hashmap_clear(hashmap_t *map) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int i, ret;
  long n = hashmap_size(map);
  map_t *m;

  for (i = 0; i < n; i++) {
    if ((ret = vla_get(&map->vla, i, (void *)&m)) < 0) return ret;

    if ((ret = map_clear(m)) < 0) return ret;
  }

  return ERR_NONE;
}

long hashmap_size(const hashmap_t *map) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int i, ret;
  long total = 0;
  map_t *m;

  for (i = 0; i < vla_size(&map->vla); i++) {
    if ((ret = vla_get(&map->vla, i, (void *)&m)) < 0) return ret;

    total += map_size(m);
  }

  return total;
}

int hashmap_keys(const hashmap_t *map, vla_t *keys) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!keys || !keys->elements) return ERR_INVALID_ARGUMENT;

  int i, ret;
  map_t *m;
  vla_t tmp;

  // Initialzie temp VLA
  if ((ret = vla_init(&tmp, keys->element_size, keys->capacity)) < 0)
    return ret;

  for (i = 0; i < vla_size(&map->vla); i++) {
    // Fetch a map
    if ((ret = vla_get(&map->vla, i, (void *)&m)) < 0) return ret;

    // Get map's keys
    if ((ret = map_keys(m, &tmp)) < 0) return ret;

    // Extend keys VLA
    if ((ret = vla_ext(keys, &tmp)) < 0) return ret;

    // Clear temp VLA
    if ((ret = vla_clear(&tmp)) < 0) return ret;
  }

  return ERR_NONE;
}

int hashmap_vals(const hashmap_t *map, vla_t *vals) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!vals || !vals->elements) return ERR_INVALID_ARGUMENT;

  int i, ret;
  map_t *m;
  vla_t tmp;

  // Initialize temp VLA
  if ((ret = vla_init(&tmp, vals->element_size, vals->capacity)) < 0)
    return ret;

  for (i = 0; i < vla_size(&map->vla); i++) {
    // Fetch a map
    if ((ret = vla_get(&map->vla, i, (void *)&m)) < 0) return ret;

    // Get map's vals
    if ((ret = map_vals(m, &tmp)) < 0) return ret;

    // Extend vals VLA
    if ((ret = vla_ext(vals, &tmp)) < 0) return ret;

    // Clear temp VLA
    if ((ret = vla_clear(&tmp)) < 0) return ret;
  }

  return ERR_NONE;
}

int hashmap_pairs(const hashmap_t *map, vla_t *pairs) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (!pairs || !pairs->elements) return ERR_INVALID_ARGUMENT;

  int i, ret;
  map_t *m;
  vla_t tmp;

  // Initialize temp VLA
  if ((ret = vla_init(&tmp, sizeof(pair_t), pairs->capacity)) < 0) return ret;

  for (i = 0; i < vla_size(&map->vla); i++) {
    // Fetch a map
    if ((ret = vla_get(&map->vla, i, (void *)&m)) < 0) return ret;

    // Get map's pairs
    if ((ret = map_pairs(m, &tmp)) < 0) return ret;

    // Extend pairs VLA
    if ((ret = vla_ext(pairs, &tmp)) < 0) return ret;

    // Clear temp VLA
    if ((ret = vla_clear(&tmp)) < 0) return ret;
  }

  return ERR_NONE;
}

#endif  // STRUCTS_HASHMAP_IMPL
#endif  // STRUCTS_HASHMAP_H
