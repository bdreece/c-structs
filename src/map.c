/*! \file map.c
 *  \brief Map data structure implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"
#include "structs/map.h"
#include "structs/vla.h"

static unsigned long map_binary_search(map_t * map, void *key, unsigned long low, unsigned long high, bool err)
{
	unsigned long mid;
	unsigned long cmp;
	pair_t pair;

	if (low > high)
	{
		if (err) 
			return ERR_NOT_FOUND;
		else 
			return low - 1;
	}

	mid = (low + high) / 2;
	if (vla_get(&map->vla, mid, (void *)&pair) < 0)
		return ERR_FAILURE;

	cmp = memcmp(key, pair.key, map->key_size);
	
	if (cmp == 0)
		return mid;
	else if (cmp < 0)
		return map_binary_search(map, key, low, mid - 1, err);
	else
		return map_binary_search(map, key, mid + 1, high, err);

	return ERR_FAILURE;
}

static unsigned long map_linear_search(map_t *map, void *key, bool err)
{
	unsigned long i;
	pair_t pair;

	for(i = 0; i < map->vla.size; i++)
	{
		if(vla_get(&map->vla, i, (void *)&pair) < 0)
			return ERR_FAILURE;
		if(memcmp(key, pair.key, map->key_size) == 0)
			return i;
	}

	return map->vla.size;
}

static pair_t *map_create_pair(map_t *map, void *key, void *val)
{
	if (!map || !key || !val) return NULL;
	pair_t *p = (struct pair *) malloc(sizeof(struct pair));
	p->key = malloc(map->key_size);
	p->val = malloc(map->val_size);

	return p;
}

static int map_destroy_pair(pair_t *p)
{
	if (!p || !p->key || !p->val)
		return ERR_NULL;

	free(p->key);
	free(p->val);
	free(p);
	return ERR_NONE;
}

int map_init(map_t *map, bool sorted, size_t key_size, size_t val_size, unsigned long initial_capacity)
{
	if (!map)
		return ERR_NULL;

	if (key_size < 1 || val_size < 1 || initial_capacity < 1)
		return ERR_EMPTY;

	if (vla_init(&map->vla, sizeof(pair_t), initial_capacity) < 0)
		return ERR_FAILURE;

	map->sorted = sorted;
	map->key_size = key_size;
	map->val_size = val_size;

	return ERR_NONE;
}

int map_deinit(map_t *map)
{
	if (!map)
		return ERR_NULL;

	if (vla_deinit(&map->vla) < 0)
		return ERR_FAILURE;

	map->key_size = map->val_size = 0;

	return ERR_NONE;
}

int map_get(map_t *map, void *key, void *val)
{
	if (!map || !map->vla.elements)
		return ERR_NULL;

	if (map->vla.size < 1)
		return ERR_EMPTY;

	unsigned long i = map->sorted ? map_binary_search(map, key, 0, map->vla.size - 1, true) : map_linear_search(map, key, true);
	pair_t p;

	if (i < 0)
		return ERR_NOT_FOUND;

	if (vla_get(&map->vla, i, (void *)&p) < 0)
		return ERR_FAILURE;

	memcpy(val, p.val, map->val_size);

	return ERR_NONE;

}

int map_set(map_t *map, void *key, void *val)
{
	if (!map || !map->vla.elements)
		return ERR_NULL;

	if (map->vla.size < 1)
		return ERR_EMPTY;

	unsigned long i = map->sorted ? map_binary_search(map, key, 0, map->vla.size - 1, false) : map_linear_search(map, key, false);

	if (i < 0)
		return ERR_FAILURE;

	pair_t *p = map_create_pair(map, key, val);

	if (vla_ins(&map->vla, i, (void *)p) < 0)
			return ERR_FAILURE;

	return ERR_NONE;	
}

int map_del(map_t *map, void *key)
{
	if (!map || !map->vla.elements)
		return ERR_NULL;

	if (map->vla.size < 1)
		return ERR_EMPTY;

	unsigned long i = map->sorted ? map_binary_search(map, key, 0, map->vla.size - 1, true) : map_linear_search(map, key, true);

	if (i < 0)
		return ERR_NOT_FOUND;

	pair_t *p;
	if (vla_get(&map->vla, i, (void *)&p) < 0)
		return ERR_FAILURE;

	if (map_destroy_pair(p) < 0)
		return ERR_FAILURE;

	if (vla_del(&map->vla, i) < 0)
		return ERR_FAILURE;

	return ERR_NONE;
}

int map_clear(map_t *map)
{
	if (!map || !map->vla.elements)
		return ERR_FAILURE;

	if (vla_clear(&map->vla) < 0)
		return ERR_FAILURE;

	return ERR_NONE;
}
