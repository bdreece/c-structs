/*! \file hashmap.c
 *  \brief HashMap data structure implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"
#include "structs/vla.h"
#include "structs/map.h"
#include "structs/hashmap.h"

static unsigned long hashmap_hash(hashmap_t *map, void *key)
{
    return *(unsigned long *)key % map->hash_val;
}

static int hashmap_rehash(hashmap_t *map)
{
	if (!map)
        return ERR_NULL;

    unsigned long i, key_size, val_size;
    map_t tmp;

    if (vla_get(&map->vla, 0, (void *)&tmp) < 0)
        return ERR_FAILURE;

    key_size = tmp.key_size;
    val_size = tmp.val_size;

    for (i = 0; i < vla_size(&map->vla); i++)
    {    
        map_t *new_map = (map_t *)malloc(sizeof(map_t));
        if (map_init(new_map, true, key_size, val_size, map->initial_capacity) < 0)
			return ERR_FAILURE;

		if (vla_enq(&map->vla, (void *)new_map) < 0)
			return ERR_FAILURE;
    }

    map->hash_val = vla_size(&map->vla) - 1;

    return ERR_NONE;
}

int hashmap_init(hashmap_t *map, size_t key_size, size_t val_size, unsigned long initial_capacity, float load_factor)
{
	if (!map)
	  return ERR_NULL;

	if (key_size < 1 || val_size < 1 || initial_capacity < 1 || load_factor < 0 || load_factor > 1)
	  return ERR_INVALID_ARGUMENT;

	if (vla_init(&map->vla, sizeof(map_t), initial_capacity) < 0)
	  return ERR_FAILURE;

	int i;
    map_t tmp;
	if (map_init(&tmp, true, key_size, val_size, initial_capacity) < 0)
	  return ERR_FAILURE;
	
    for (i = 0; i < map->vla.capacity; i++)
	{
	  if (vla_enq(&map->vla, (void *)&tmp) < 0)
		return ERR_FAILURE;
	}

    map->initial_capacity = initial_capacity;
	map->load_factor = load_factor;
	map->hash_val = map->vla.size - 1;

	return ERR_NONE;
}

int hashmap_deinit(hashmap_t *map)
{
	int i; 

    vla_deinit(&map->vla);
    map->initial_capacity = 0;
    map->load_factor = 0;
    map->hash_val = 0;

    return ERR_NONE;
}

int hashmap_get(hashmap_t *map, void *key, void *val)
{
    if (!map || !key || !val)
        return ERR_NULL;

    if (map->vla.size < 1)
        return ERR_EMPTY;

    unsigned long hash_val = hashmap_hash(map, key);
    map_t tmp_map;
    
    if (vla_get(&map->vla, hash_val, (void *)&tmp_map) < 0)
        return ERR_FAILURE;

    if (map_get(&tmp_map, key, val) < 0)
        return ERR_FAILURE;

    return ERR_NONE;
}

int hashmap_set(hashmap_t *map, void *key, void *val)
{
    if (!map || !key || !val)
        return ERR_NULL;

    unsigned long hash_val = hashmap_hash(map, key);
    map_t tmp_map;

    if (vla_get(&map->vla, hash_val, (void *)&tmp_map) < 0)
      return ERR_FAILURE;

    if (map_set(&tmp_map, key, val) < 0)
      return ERR_FAILURE;

    if (vla_set(&map->vla, hash_val, (void *)&tmp_map) < 0)
      return ERR_FAILURE;

    if (map->load_factor > 0 && tmp_map.vla.size > map->load_factor * tmp_map.vla.capacity)
        if (hashmap_rehash(map) < 0)
            return ERR_FAILURE;

    return ERR_NONE;
}

int hashmap_del(hashmap_t *map, void *key)
{
    if (!map || !key)
        return ERR_NULL;

    unsigned long hash_val = hashmap_hash(map, key);
    map_t tmp_map;

    if (vla_get(&map->vla, hash_val, (void *)&tmp_map) < 0)
        return ERR_FAILURE;

    if (map_del(&tmp_map, key) < 0)
        return ERR_FAILURE;

    return ERR_NONE;
}
