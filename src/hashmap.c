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

    unsigned long i, key_size, val_size, j = 0;
    int retval = 0;
    map_t *tmp;
    pair_t *pairs = (pair_t *) malloc(hashmap_size(map) * sizeof(pair_t));

    for (i = 0; i < vla_size(&map->vla); i++)
    {
      if ((retval = vla_getp(&map->vla, i, (void *)tmp)) < 0)
        return retval;

      if ((retval = map_pairs(tmp, map_size(tmp), pairs + j)) < 0)
        return retval;

      j += map_size(tmp);
      if ((retval = map_deinit(tmp)) < 0)
        return retval;

      free(tmp);

    }

    vla_clear(&map->vla);
    map->size = 0;

    for (i = 0; i < 2 * vla_size(&map->vla); i++)
    {    
        tmp = (map_t *)malloc(sizeof(map_t));
        
        if (!tmp)
          return ERR_FAILURE;

        if ((retval = map_init(tmp, true, key_size, val_size, map->initial_capacity)) < 0)
			return retval;

		if ((vla_enq(&map->vla, (void *)tmp)) < 0)
			return retval;
    }

    map->hash_val = 2 * vla_size(&map->vla) - 1;

    for (i = 0; i < j; i++)
    {
      if ((retval = hashmap_set(map, (pairs + i)->key, (pairs + i)->val)) < 0)
        return retval;
    }

    if (j != hashmap_size(map))
      return ERR_FAILURE;

    return ERR_NONE;
}

int hashmap_init(hashmap_t *map, size_t key_size, size_t val_size, unsigned long initial_capacity, float load_factor)
{
	if (!map)
	  return ERR_NULL;

	if (key_size < 1 || val_size < 1 || initial_capacity < 1 || load_factor < 0 || load_factor > 1)
	  return ERR_INVALID_ARGUMENT;


	int i, retval = 0;
    map_t tmp;

	if ((retval = vla_init(&map->vla, sizeof(map_t), initial_capacity)) < 0)
	  return retval;
	
    for (i = 0; i < map->vla.capacity; i++)
	{
      if ((retval = map_init(&tmp, true, key_size, val_size, initial_capacity)) < 0)
	    return retval;
	  if ((retval = vla_enq(&map->vla, (void *)&tmp)) < 0)
		return retval;
	}

    map->initial_capacity = initial_capacity;
	map->load_factor = load_factor;
	map->hash_val = map->vla.size - 1;

	return ERR_NONE;
}

int hashmap_deinit(hashmap_t *map)
{
  int i, retval = 0;
  map_t *tmp;
  
  for (i = 0; i < vla_size(&map->vla); i++)
  {
    if ((retval = vla_getp(&map->vla, i, (void *)&tmp)) < 0)
      return retval;

    if ((retval = map_deinit(tmp)) < 0)
      return retval;

    free(tmp);
  }

    vla_deinit(&map->vla);
    map->initial_capacity = 0;
    map->load_factor = 0;
    map->hash_val = 0;
    map->size = 0;

    return ERR_NONE;
}

int hashmap_get(hashmap_t *map, void *key, void *val)
{
    if (!map || !key || !val)
        return ERR_NULL;

    if (map->vla.size < 1)
        return ERR_EMPTY;

    unsigned long hash_val = hashmap_hash(map, key);
    int retval = 0;
    map_t tmp;
    
    if ((retval = vla_get(&map->vla, hash_val, (void *)&tmp)) < 0)
        return retval;

    if ((retval = map_get(&tmp, key, val)) < 0)
        return retval;

    return ERR_NONE;
}

int hashmap_set(hashmap_t *map, void *key, void *val)
{
    if (!map || !key || !val)
        return ERR_NULL;

    unsigned long hash_val = hashmap_hash(map, key);
    int retval = 0;
    map_t *tmp;

    if ((retval = vla_getp(&map->vla, hash_val, (void *)tmp)) < 0)
      return retval;

    if ((retval = map_set(tmp, key, val)) < 0)
      return retval;

    map->size++;

    if (map->load_factor > 0 && tmp->vla.size > map->load_factor * tmp->vla.capacity)
        if ((retval = hashmap_rehash(map)) < 0)
            return retval;

    return ERR_NONE;
}

int hashmap_del(hashmap_t *map, void *key)
{
    if (!map || !key)
        return ERR_NULL;

    unsigned long hash_val = hashmap_hash(map, key);
    int retval = 0;
    map_t tmp_map;

    if ((retval = vla_get(&map->vla, hash_val, (void *)&tmp_map)) < 0)
        return retval;

    if ((retval = map_del(&tmp_map, key)) < 0)
        return retval;

    map->size--;

    return ERR_NONE;
}

int hashmap_clear(hashmap_t *map)
{
  if (!map)
    return ERR_NULL;

  int i, retval = 0;
  map_t *tmp;

  for (i = 0; i < vla_size(&map->vla); i++)
  {
    if ((retval = vla_getp(&map->vla, i, (void *)tmp)) < 0)
      return retval;

    if ((retval = map_clear(tmp)) < 0)
      return retval;
  }
}

unsigned long hashmap_size(hashmap_t *map)
{
  return map->size;
}
