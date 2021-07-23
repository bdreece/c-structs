/*! \file hashmap.h
 *  \brief Hash Map data structure
 *  \author Brian Reece  
 *  \version 0.1.0
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "structs/error.h"
#include "structs/vla.h"
#include "structs/map.h"

typedef struct hashmap
{
    unsigned long hash_val, initial_capacity;
    float load_factor;
    vla_t vla;
} hashmap_t;

int hashmap_init(hashmap_t *map, size_t key_size, size_t val_size, unsigned long initial_capacity, float load_factor);

int hashmap_deinit(hashmap_t *map);

int hashmap_get(hashmap_t *map, void *key, void *value);

int hashmap_set(hashmap_t *map, void *key, void *value);

int hashmap_del(hashmap_t *map, void *key);

#ifdef __cplusplus
}
#endif

#endif // HASHMAP_H
