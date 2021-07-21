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
#include "c-structs/error.h"
#include "c-structs/vla.h"
#include "c-structs/map.h"

typedef struct hashmap
{
    unsigned long size;
    vla_t vla;
} hashmap_t;

int hashmap_init(hashmap_t *map, unsigned long size);

int hashmap_deinit(hashmap_t *map);

int hashmap_get(hashmap_t *map, void *key, void *value);

int hashmap_set(hashmap_t *map, void *key, void *value);

int hashmap_del(hashmap_t *map, void *key);

#ifdef __cplusplus
}
#endif

#endif // HASHMAP_H