/*! \file map.c
 *  \brief Map data structure implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "vla.h"

static unsigned long map_binary_search(map_t * map, void *key)
{
	return 0;
}

static unsigned long map_linear_search(map_t *map, void *key)
{
	return 0;
}

static pair_t *map_create_pair(map_t *map, void *key, void *val)
{
	pair_t *p = (struct pair *) malloc(sizeof(struct pair));
	p->key = malloc(map->key_size);
	p->val = malloc(map->val_size);

	return p;
}

int map_init(map_t *map, bool sorted, size_t key_size, size_t val_size, unsigned long initial_capacity)
{
	if (!map)
		return MAP_FAILURE;

	if (vla_init(&map->vla, sizeof(pair_t), initial_capacity) == VLA_FAILURE)
		return MAP_FAILURE;

	map->sorted = sorted;
	map->key_size = key_size;
	map->val_size = val_size;

	return MAP_SUCCESS;
}

int map_deinit(map_t *map)
{
	if (!map)
		return MAP_FAILURE;

	if (vla_deinit(&map->elements) == VLA_FAILURE)
		return MAP_FAILURE;

	map->key_size = map->val_size = 0;

	return MAP_SUCCESS;
}

int map_get(map_t *map, void *key, void *val)
{
	if (!map || !map->vla->elements)
		return MAP_FAILURE;

	if (map->vla->size < 1)
		return MAP_EMPTY;

	unsigned long i = map->sorted ? map_binary_search(map, key) : map_linear_search(map, key);
	pair_t p;

	if (i < 0)
		return MAP_UNKNOWN_KEY;

	if (vla_get(&map->vla, i, &p) < 0)
		return MAP_FAILURE;

	return MAP_SUCCESS;

}

int map_set(map_t *map, void *key, void *val)
{
	if (!map || !map->elements->elements)
		return MAP_FAILURE;

	if (map->elements->size < 1)
		return MAP_EMPTY;

	unsigned long tmp = map->sorted ? map_binary_search(map, key) : map->elements->size;

	pair_t *p = map_create_pair(map, key, val);

	if (tmp < 0)
		return MAP_UNKNOWN_KEY;

	if (tmp == map->elements->size)
	{
		if (vla_enq(&map->elements, val) < 0)
			return MAP_FAILURE;
	} else
	{
		if (vla_set(&map->elements, tmp, val) < 0)
			return MAP_FAILURE;
	}

	return MAP_SUCCESS;	
}

int map_delete(map_t *map, void *key)
{
	return 0;
}

int map_clear(map_t *map)
{
	if (!map || !map->elements->elements)
		return MAP_FAILURE;
}
