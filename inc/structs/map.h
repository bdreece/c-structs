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

#include <stddef.h>
#include <stdbool.h>
#include "structs/vla.h"

typedef struct pair
{
  void *key, *val;
} pair_t;

typedef struct map
{
  vla_t vla;
  bool sorted;
  size_t key_size, val_size;
} map_t;

int map_init(map_t *map, bool sorted, size_t key_size, size_t val_size, unsigned long initial_capacity);

int map_deinit(map_t *map);

int map_set(map_t *map, void *key, void *val);

int map_get(map_t *map, void *key, void *val);

int map_del(map_t *map, void *key);

int map_clear(map_t *map);

#ifdef __cplusplus
}
#endif

#endif // MAP_H
