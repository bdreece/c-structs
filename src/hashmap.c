/*! \file hashmap.c
 *  \brief HashMap data structure implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "c-structs/error.h"
#include "c-structs/vla.h"
#include "c-structs/map.h"
#include "c-structs/hashmap.h"

static int hashmap_rehash(hashmap_t *map)
{
	return 0;
}

int hashmap_init(hashmap_t *map, size_t key_size, size_t val_size, unsigned long initial_capacity, float load_factor)
{
	if (!map)
		return ERR_NULL;

	if (key_size < 1 || val_size < 1 || initial_capacity < 1)
		return ERR_FAILURE;

	if (vla_init(&map->vla, sizeof(map_t), initial_capacity) < 0)
		return ERR_FAILURE;

	int i;
	for (i = 0; i < map->vla.capacity - 1; i++)
	{
		map_t *tmp = (map_t *) malloc(sizeof(map_t));
		if (map_init(tmp, key_size, val_size, initial_capacity) < 0)
			return ERR_FAILURE;

		if (vla_enq(&map->vla, (void *)tmp) < 0)
			return ERR_FAILURE;
	}

	map->load_factor = load_factor;
	map->hash_val = map->vla.size - 1;

	return ERR_NONE;
}

int hashmap_deinit(hashmap_t *map)
{
	return 0;
}
