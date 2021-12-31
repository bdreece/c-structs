/**
 * \file        hashmap.h
 * \brief       Hashmap data structure
 * \author      Brian Reece
 * \version     v0.3-alpha
 * \date        12/27/2021
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include <stddef.h>

#include "structs/map.h"
#include "structs/vla.h"

#ifdef __cplusplus
extern "C" {
#endif

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
int hashmap_init(hashmap_t *map, const size_t key_size, const size_t val_size,
                 int (*cmp)(const void *, const void *, size_t),
                 long (*hash)(long, const void *), long initial_breadth,
                 long depth);

/*! \brief Hashmap destruction function
 *  \details Deinitializes and frees memory associated
 *           with the given hashmap.
 *  \param[in] map The respective hashmap
 *  \return Zero if successful, non-zero otherwise
 */
int hashmap_deinit(hashmap_t *map);

/*! \brief Hashmap contains function
 *  \details Finds whether the given key exists in the
 *           map.
 *  \param[in] map The respective hashmap
 *  \param[in] key The given key
 *  \return Zero if successful, non-zero otherwise.
 */
bool hashmap_contains(const hashmap_t *map, const void *key);

/*! \brief Hashmap get function
 *  \details Gets the value associated with the given
 *           key in the map, if it exists.
 *  \param[in] map The respective hashmap
 *  \param[in] key The given key
 *  \param[out] val The value, if found
 *  \return Zero if successful, non-zero otherwise.
 */
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

#endif  // HASHMAP_H
