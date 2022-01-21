/*! \file       map.h
 *  \brief      Map data structure
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/28/2021
 */

#ifndef STRUCTS_MAP_H
#define STRUCTS_MAP_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif

#include <stdbool.h>
#include <stddef.h>

#ifdef STRUCTS_MAP_IMPL
#define STRUCTS_VLA_IMPL
#endif  // STRUCTS_MAP_IMPL
#include "structs/vla.h"

//! \brief Key-value pair struct
typedef struct pair {
  void *key;  //!< Key
  void *val;  //!< Value
} pair_t;

//! \brief Map data structure
typedef struct map {
  vla_t vla;        //!< VLA of pairs
  size_t key_size;  //!< Size of keys
  size_t val_size;  //!< Size of values
  int (*cmp)(const void *, const void *,
             const size_t);  //!< Key comparison function
  size_t (*search)(const struct map *const,
                   const void *const);  //!< Map search function
} map_t;

/*! \brief Map construction function
 *  \details Constructs an ordered/unordered map of key-value pairs.
 *  \param[in] map A pointer to the initialized map
 *  \param[in] key_size The size of keys
 *  \param[in] val_size The size of values
 *  \param[in] ordered Whether the map is to be ordered
 *  \param[in] cmp The key comparison function
 *  \param[in] initial_capacity The initial capacity of the inner VLA
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_init(map_t *const map, const size_t key_size,
                         const size_t val_size, bool ordered,
                         int (*cmp)(const void *, const void *, size_t),
                         const size_t initial_capacity);

/*! \brief Map destruction function
 *  \details Calls the VLA destruction function and deinitializes
 *           other map struct members.
 *  \param[in] map The map to destruct
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_deinit(map_t *const map);

/*! \brief Map set function
 *  \details Sets the value associated with the given key
 *           If the key does not exist, a new pair will be
 *           created.
 *  \param[in] map The respective map
 *  \param[in] key The key to be associated with the new value
 *  \param[in] val The value to be set in the map
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_set(map_t *const map, const void *const key,
                        const void *restrict val);

/*! \brief Map contains function
 *  \details Find whether the key exists in the map
 *  \param[in] map The respective map
 *  \param[in] key The key to find
 *  \return True if found, false otherwise
 */
STRUCTS_DEF bool map_contains(const map_t *const map, const void *const key);

/*! \brief Map get function
 *  \details Gets the value associated with the given key in the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \param[out] val The value if found
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_get(const map_t *const map, const void *const key,
                        void *restrict val);

/*! \brief Map get pointer function
 *  \details Gets a pointer to the value associated with the
 *           given key in the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \param[out] val The value if found
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_getp(const map_t *const map, const void *const key,
                         void **const val);

/*! \brief Map delete function
 *  \details Deletes a given key-value pair from the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_del(map_t *const map, const void *const key);

/*! \brief Map clear function
 *  \details Clears the map
 *  \param[in] map The respective map
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_clear(map_t *const map);

/*! \brief Map size getter
 *  \param[in] map The respective map
 *  \return The current size of the map
 */
STRUCTS_DEF size_t map_size(const map_t *const map);

STRUCTS_DEF size_t map_capacity(const map_t *const map);

/*! \brief Map keys function
 *  \details Gets a VLA of all the keys in the map
 *  \param[in] map The respective map
 *  \param[out] keys An initialized VLA for key elements
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_keys(const map_t *const map, vla_t *restrict keys);

/*! \brief Map values function
 *  \details Gets a VLA of all the values in the map
 *  \param[in] map The respective map
 *  \param[out] vals An initialized VLA for value elements
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_vals(const map_t *const map, vla_t *restrict vals);

/*! \brief Map pairs function
 *  \details Gets a VLA of all the key-value pairs in the map
 *  \param[in] map The respective map
 *  \param[out] pairs An initialized VLA for pair elements
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_pairs(const map_t *const map, vla_t *restrict pairs);

STRUCTS_DEF size_t umap_search(const map_t *const map, const void *const key);

STRUCTS_DEF size_t omap_search(const map_t *const map, const void *const key);

#ifdef STRUCTS_MAP_IMPL

#include <stdlib.h>

#ifndef STRUCTS_NO_STRING_H

#ifndef STRUCTS_STRING_H
#define STRUCTS_STRING_H

#include <string.h>
#define STRUCTS_MEMCPY(d, s, n) memcpy((d), (s), (n))
#define STRUCTS_MEMMOVE(d, s, n) memmove((d), (s), (n))
#define STRUCTS_MEMSET(d, c, n) memset((d), (c), (n))

#endif  // STRUCTS_STRING_H

#endif  // STRUCTS_NO_STRING_H

#include "structs/error.h"

static inline pair_t map_create_pair(const map_t *const map,
                                     const void *const key,
                                     const void *const val) {
  pair_t p = {.key = malloc(map->key_size), .val = malloc(map->val_size)};

  ASSERT(STRUCTS_MEMCPY(p.key, key, map->key_size) != NULL);
  ASSERT(STRUCTS_MEMCPY(p.val, val, map->val_size) != NULL);

  return p;
}

static inline int map_destroy_pair(pair_t *const p) {
  if (!p || !p->key || !p->val) return ERR_NULL;

  free(p->key);
  free(p->val);
  return ERR_NONE;
}

size_t umap_search(const map_t *const map, const void *const key) {
  if (!map || !map->vla.elements | !key) return ERR_NULL;

  int ret;
  size_t i;
  const pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    // we don't take ownership of p here
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;
    if (map->cmp(key, p->key, map->key_size) == 0) return i;
  }

  return map_size(map) + 1;
}

// FIXME: This is broken
size_t omap_search(const map_t *const map, const void *const key) {
  int ret, compare;
  size_t l, r, m;
  const pair_t *p;

  l = 0;
  r = map_size(map);

  if (r == 0) return r;

  while (l < r) {
    m = (size_t)((r - l) / 2);

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

  return map_size(map) + 1;
}

int map_init(map_t *const map, const size_t key_size, const size_t val_size,
             bool ordered, int (*cmp)(const void *, const void *, size_t),
             const size_t initial_capacity) {
  int ret;
  if (!map || !cmp) return ERR_NULL;

  if (key_size < 1 || val_size < 1 || initial_capacity < 1)
    return ERR_INVALID_ARGUMENT;

  if ((ret = vla_init(&map->vla, sizeof(pair_t), initial_capacity)) < 0)
    return ret;

  map->key_size = key_size;
  map->val_size = val_size;
  map->cmp = cmp;

  map->search = ordered ? omap_search : umap_search;

  return ERR_NONE;
}

int map_deinit(map_t *const map) {
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

int map_set(map_t *const map, const void *key, const void *val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int ret;
  const size_t i = map->search(map, key);

  // Got an error
  if (i < 0) return i;

  if (i >= map_size(map)) {
    // Key not found
    const pair_t p = map_create_pair(map, key, val);
    if ((ret = vla_enq(&map->vla, (void *)&p)) < 0) return ret;
  } else {
    // Key found
    pair_t *const p;
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;
    ASSERT(STRUCTS_MEMCPY(p->val, val, map->val_size) != NULL);
  }

  return ERR_NONE;
}

// TODO: map_contains
bool map_contains(const map_t *const map, const void *const key) {
  return false;
}

int map_get(const map_t *const map, const void *const key, void *val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (map_size(map) < 1) return ERR_EMPTY;

  const size_t i = map->search(map, key);

  // Got error
  if (i < 0) return i;

  // Key not found
  if (i == map_size(map)) return ERR_NOT_FOUND;

  int ret;
  const pair_t *p;

  // vla_getp to avoid double copy
  if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

  // Copy val from pair
  ASSERT(STRUCTS_MEMCPY(val, p->val, map->val_size) != NULL);

  return ERR_NONE;
}

int map_getp(const map_t *const map, const void *const key, void **const val) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (map_size(map) < 1) return ERR_EMPTY;

  const size_t i = map->search(map, key);

  // Got error
  if (i < 0) return i;

  // Key not found
  if (i == map_size(map)) return ERR_NOT_FOUND;

  int ret;
  const pair_t *p;

  // vla_getp to avoid double copy
  if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

  // Copy pointer to val
  *val = p->val;

  return ERR_NONE;
}

int map_del(map_t *const map, const void *const key) {
  if (!map || !map->vla.elements) return ERR_NULL;

  if (map_size(map) < 1) return ERR_EMPTY;

  const size_t i = map->search(map, key);

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

int map_clear(map_t *const map) {
  if (!map || !map->vla.elements) return ERR_NULL;

  int ret;
  if ((ret = vla_clear(&map->vla)) < 0) return ret;

  return ERR_NONE;
}

size_t map_size(const map_t *const map) { return vla_size(&map->vla); }

size_t map_capacity(const map_t *const map) { return vla_capacity(&map->vla); }

int map_keys(const map_t *const map, vla_t *keys) {
  if (!map || !map->vla.elements || !keys || !keys->elements) return ERR_NULL;

  int ret;
  size_t i;
  const pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    // vla_getp for subsequent copy, to avoid double copying
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

    if ((ret = vla_enq(keys, (const void *)p->key)) < 0) return ret;
  }

  return ERR_NONE;
}

int map_vals(const map_t *const map, vla_t *vals) {
  if (!map || !map->vla.elements || !vals || !vals->elements) return ERR_NULL;

  int ret;
  size_t i;
  const pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

    if ((ret = vla_enq(vals, (const void *)p->val)) < 0) return ret;
  }

  return ERR_NONE;
}

int map_pairs(const map_t *const map, vla_t *pairs) {
  if (!map || !map->vla.elements || !pairs || !pairs->elements) return ERR_NULL;

  int ret;
  size_t i;
  const pair_t *p;

  for (i = 0; i < map_size(map); i++) {
    if ((ret = vla_getp(&map->vla, i, (void **)&p)) < 0) return ret;

    if ((ret = vla_enq(pairs, (const void *)p)) < 0) return ret;
  }

  return ERR_NONE;
}

#endif  // STRUCTS_MAP_IMPL
#endif  // MAP_H
