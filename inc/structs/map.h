/**
 * MIT License
 *
 * Copyright (c) 2022 Brian Reece
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
typedef struct map_pair {
    void *key;  //!< Key
    void *val;  //!< Value
} map_pair_t;

typedef struct map_search_result {
    size_t index;
    bool found;
} map_search_result_t;

//! \brief Map data structure
typedef struct map {
    vla_t vla;                               //!< VLA of pairs
    size_t key_size;                         //!< Size of keys
    size_t val_size;                         //!< Size of values
    int (*cmp)(const void *, const void *);  //!< Key comparison function
    map_search_result_t (*search)(const struct map *const,
                                  const void *const);  //!< Map search function
} map_t;

/*! \brief Map construction function
 *  \details Constructs an ordered/unordered map of key-value pairs.
 *  \param[in] key_size The size of keys
 *  \param[in] val_size The size of values
 *  \param[in] ordered Whether the map is to be ordered
 *  \param[in] cmp The key comparison function
 *  \param[in] initial_capacity The initial capacity of the inner VLA
 *  \return The new map
 */
STRUCTS_DEF map_t map_init(const size_t key_size, const size_t val_size,
                           bool ordered, int (*cmp)(const void *, const void *),
                           const size_t capacity);

/*! \brief Map destruction function
 *  \details Calls the VLA destruction function and deinitializes
 *           other map struct members.
 *  \param[in] map The map to destruct
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_deinit(map_t *const map);

/*! \brief Map set function
 *  \details Sets the value associated with the given key
 *           If the key-value pair does not exist, an ERR_NOT_FOUND
 *           will be returned.
 *  \param[in] map The respective map
 *  \param[in] key The key to be associated with the new value
 *  \param[in] val The value to be set in the map
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_set(map_t *const map, const void *const key,
                        const void *restrict val);

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

/*! \brief Map insert function
 *  \details Inserts a given key-value pair into the map
 *  \param[in] map The respective map
 *  \param[in] key The given key
 *  \param[in] val The given value
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int map_ins(map_t *const map, const void *const key,
                        const void *const val);

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

/*! \brief Map length getter
 *  \param[in] map The respective map
 *  \return The length of the map
 */
STRUCTS_DEF long map_length(const map_t *const map);

/*! \brief Map val size getter
 *  \param[in] map The respective map
 *  \return The val size of the map
 */
STRUCTS_DEF long map_val_size(const map_t *const map);

/*! \brief Map key size getter
 *  \param[in] map The respective map
 *  \return The key size of the map
 */
STRUCTS_DEF long map_key_size(const map_t *const map);

/*! \brief Map capacity getter
 *  \param[in] map The respective map
 *  \return The current capacity of the map
 */
STRUCTS_DEF long map_capacity(const map_t *const map);

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

#ifdef STRUCTS_MAP_IMPL

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"

static inline map_pair_t map_create_pair(const map_t *const map,
                                         const void *const key,
                                         const void *const val) {
    map_pair_t p = {.key = malloc(map->key_size), .val = malloc(map->val_size)};

    ASSERT(memcpy(p.key, key, map->key_size));
    ASSERT(memcpy(p.val, val, map->val_size));

    return p;
}

static inline int map_destroy_pair(map_pair_t *const p) {
    if (!p || !p->key || !p->val) return ERR_NULL;

    free(p->key);
    free(p->val);
    return ERR_NONE;
}

static map_search_result_t umap_search(const map_t *const map,
                                       const void *const key) {
    map_search_result_t result = {
        .index = 0,
        .found = false,
    };

    const map_pair_t *p;

    // Linear search
    for (result.index = 0; result.index < map->vla.length; result.index++) {
        // we don't take ownership of p here
        ASSERT(vla_getp(&map->vla, result.index, (void **)&p) == ERR_NONE);
        if (map->cmp(key, p->key) == 0) {
            result.found = true;
            return result;
        }
    }

    // key not found
    return result;
}

static map_search_result_t omap_search_helper(const map_t *const map,
                                              const void *const key, size_t l,
                                              size_t r) {
    map_search_result_t result = {
        .index = 0,
        .found = false,
    };

    if (r - l < 2) {
        result.index = l;
        return result;
    }

    int compare;
    const map_pair_t *p;
    result.index = (l + r) / 2;

    ASSERT(vla_getp(&map->vla, result.index, (void **)&p) == ERR_NONE);
    compare = map->cmp(key, p->key);
    switch (compare) {
        case -1:
            return omap_search_helper(map, key, l, result.index);
        case 0:
            result.found = true;
            return result;
        case 1:
            return omap_search_helper(map, key, result.index + 1, r);
    }
}

static map_search_result_t omap_search(const map_t *const map,
                                       const void *const key) {
    return omap_search_helper(map, key, 0, map->vla.length);
}

map_t map_init(const size_t key_size, const size_t val_size, bool ordered,
               int (*cmp)(const void *, const void *),
               const size_t initial_capacity) {
    map_t map = {
        .vla = vla_init(sizeof(map_pair_t), initial_capacity),
        .key_size = key_size,
        .val_size = val_size,
        .cmp = cmp,
        .search = ordered ? omap_search : umap_search,
    };

    return map;
}

int map_deinit(map_t *const map) {
    if (!map || !map->vla.elements) return ERR_NULL;

    size_t i;
    int ret;
    map_pair_t *p;
    for (i = 0; i < map->vla.length; i++) {
        ERR_PROP(ret, vla_getp(&map->vla, i, (void **)&p));
        ERR_PROP(ret, map_destroy_pair(p));
    }

    ERR_PROP(ret, vla_deinit(&map->vla));
    ASSERT(memset(map, 0, sizeof(map_t)));

    return ERR_NONE;
}

int map_set(map_t *const map, const void *const key, const void *val) {
    if (!map || !map->vla.elements) return ERR_NULL;

    int ret;
    map_pair_t *const p;
    const map_search_result_t result = map->search(map, key);

    if (!result.found) {
        return ERR_NOT_FOUND;
    }

    ERR_PROP(ret, vla_getp(&map->vla, result.index, (void **)&p));
    ASSERT(memcpy(p->val, val, map->val_size));

    return ERR_NONE;
}

int map_get(const map_t *const map, const void *const key, void *val) {
    if (!map || !map->vla.elements || !key || !val) return ERR_NULL;

    int ret;
    const map_pair_t *p;
    const map_search_result_t result = map->search(map, key);

    if (!result.found) {
        return ERR_NOT_FOUND;
    }

    // Key found
    // vla_getp to avoid double copy
    ERR_PROP(ret, vla_getp(&map->vla, result.index, (void **)&p));

    // Copy val from pair
    ASSERT(memcpy(val, p->val, map->val_size) != NULL);

    return ERR_NONE;
}

int map_getp(const map_t *const map, const void *const key, void **const val) {
    if (!map || !map->vla.elements || !key || !val) return ERR_NULL;

    int ret;
    const map_pair_t *p;
    const map_search_result_t result = map->search(map, key);

    // Key not found
    if (!result.found) {
        return ERR_NOT_FOUND;
    }

    // Key found
    // vla_getp to avoid double copy
    ERR_PROP(ret, vla_getp(&map->vla, result.index, (void **)&p));

    // Copy pointer to val
    *val = p->val;

    return ERR_NONE;
}

int map_ins(map_t *const map, const void *const key, const void *const val) {
    if (!map || !map->vla.elements || !key || !val) return ERR_NULL;

    int ret;
    map_pair_t p;
    const map_search_result_t result = map->search(map, key);

    if (!result.found) {
        p = map_create_pair(map, key, val);
        ERR_PROP(ret, vla_ins(&map->vla, result.index, (void *)&p));
    } else {
        ERR_PROP(ret, vla_get(&map->vla, result.index, (void *)&p));
        ASSERT(memcpy(p.val, val, map->val_size));
    }
    return ERR_NONE;
}

int map_del(map_t *const map, const void *const key) {
    if (!map || !map->vla.elements) return ERR_NULL;

    int ret;
    map_pair_t *p;
    const map_search_result_t result = map->search(map, key);

    // Key not found
    if (!result.found) {
        return ERR_NOT_FOUND;
    }

    // Key found
    // vla_getp to access heap pointer, instead of copying
    ERR_PROP(ret, vla_getp(&map->vla, result.index, (void **)&p));

    // Free key and value
    ERR_PROP(ret, map_destroy_pair(p));

    // Remove from vla
    ERR_PROP(ret, vla_del(&map->vla, result.index));

    return ERR_NONE;
}

int map_clear(map_t *const map) {
    if (!map || !map->vla.elements) return ERR_NULL;

    int ret;
    ERR_PROP(ret, vla_clear(&map->vla));

    return ERR_NONE;
}

long map_length(const map_t *const map) { return vla_length(&map->vla); }

long map_key_size(const map_t *const map) {
    return (!map || !map->vla.elements) ? ERR_NULL : map->key_size;
}

long map_val_size(const map_t *const map) {
    return (!map || !map->vla.elements) ? ERR_NULL : map->val_size;
}

long map_capacity(const map_t *const map) { return vla_capacity(&map->vla); }

int map_keys(const map_t *const map, vla_t *keys) {
    if (!map || !map->vla.elements || !keys || !keys->elements) return ERR_NULL;

    int ret;
    size_t i;
    const map_pair_t *p;

    for (i = 0; i < map_length(map); i++) {
        // vla_getp for subsequent copy, to avoid double copying
        ERR_PROP(ret, vla_getp(&map->vla, i, (void **)&p));
        ERR_PROP(ret, vla_enq(keys, (const void *)p->key));
    }

    return ERR_NONE;
}

int map_vals(const map_t *const map, vla_t *vals) {
    if (!map || !map->vla.elements || !vals || !vals->elements) return ERR_NULL;

    int ret;
    size_t i;
    const map_pair_t *p;

    for (i = 0; i < map_length(map); i++) {
        ERR_PROP(ret, vla_getp(&map->vla, i, (void **)&p));
        ERR_PROP(ret, vla_enq(vals, (const void *)p->val));
    }

    return ERR_NONE;
}

int map_pairs(const map_t *const map, vla_t *pairs) {
    if (!map || !map->vla.elements || !pairs || !pairs->elements)
        return ERR_NULL;

    int ret;
    size_t i;
    const map_pair_t *p;

    for (i = 0; i < map_length(map); i++) {
        ERR_PROP(ret, vla_getp(&map->vla, i, (void **)&p));
        ERR_PROP(ret, vla_enq(pairs, (const void *)p));
    }

    return ERR_NONE;
}

#endif  // STRUCTS_MAP_IMPL
#endif  // MAP_H
