/*! \file       map.h
 *  \brief      Map data structure
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/28/2021
 */

#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "structs/vla.h"

//! \brief Key-value pair struct
typedef struct pair {
  void *key; //!< Key
  void *val; //!< Value
} pair_t;

//! \brief Map data structure
typedef struct map {
  vla_t vla;                                        //!< VLA of pairs
  size_t key_size;                                  //!< Size of keys
  size_t val_size;                                  //!< Size of values
  int (*cmp)(const void *, const void *, size_t);   //!< Key comparison function
  long (*search)(const struct map *, const void *); //!< Map search function
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
int map_init(map_t *map, const size_t key_size, const size_t val_size,
             bool ordered, int (*cmp)(const void *, const void *, size_t),
             const unsigned long initial_capacity);

/*! \brief Map destruction function
 *  \details Calls the VLA destruction function and deinitializes
 *           other map struct members.
 *  \param[in] map The map to destruct
 *  \return Zero if successful, non-zero otherwise
 */
int map_deinit(map_t *map);

/*! \brief Map set function
 *  \details Sets the value associated with the given key
 *           If the key does not exist, a new pair will be
 *           created.
 *  \param[in] map The respective map
 *  \param[in] key The key to be associated with the new value
 *  \param[in] val The value to be set in the map
 *  \return Zero if successful, non-zero otherwise
 */
int map_set(map_t *map, const void *key, const void *val);

/*! \brief Map contains function
 *  \details Find whether the key exists in the map
 *  \param[in] map The respective map
 *  \param[in] key The key to find
 *  \return True if found, false otherwise
 */
bool map_contains(const map_t *map, const void *key);

/*! \brief Map get function
 *  \details Gets the value associated with the given key in the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \param[out] val The value if found
 *  \return Zero if successful, non-zero otherwise
 */
int map_get(const map_t *map, const void *key, void *val);

/*! \brief Map get pointer function
 *  \details Gets a pointer to the value associated with the
 *           given key in the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \param[out] val The value if found
 *  \return Zero if successful, non-zero otherwise
 */
int map_getp(const map_t *map, const void *key, void **val);

/*! \brief Map delete function
 *  \details Deletes a given key-value pair from the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \return Zero if successful, non-zero otherwise
 */
int map_del(map_t *map, const void *key);

/*! \brief Map clear function
 *  \details Clears the map
 *  \param[in] map The respective map
 *  \return Zero if successful, non-zero otherwise
 */
int map_clear(map_t *map);

/*! \brief Map size getter
 *  \param[in] map The respective map
 *  \return The current size of the map
 */
extern long map_size(const map_t *map);

/*! \brief Map keys function
 *  \details Gets a VLA of all the keys in the map
 *  \param[in] map The respective map
 *  \param[out] keys An initialized VLA for key elements
 *  \return Zero if successful, non-zero otherwise
 */
int map_keys(const map_t *map, vla_t *keys);

/*! \brief Map values function
 *  \details Gets a VLA of all the values in the map
 *  \param[in] map The respective map
 *  \param[out] vals An initialized VLA for value elements
 *  \return Zero if successful, non-zero otherwise
 */
int map_vals(const map_t *map, vla_t *vals);

/*! \brief Map pairs function
 *  \details Gets a VLA of all the key-value pairs in the map
 *  \param[in] map The respective map
 *  \param[out] pairs An initialized VLA for pair elements
 *  \return Zero if successful, non-zero otherwise
 */
int map_pairs(const map_t *map, vla_t *pairs);

#ifdef __cplusplus
}
#endif

#endif // MAP_H
