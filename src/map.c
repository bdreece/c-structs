//! \file map.c

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "map.h"
#include "list.h"

static Pair_t *map_create_pair(Map_t *map, void *key, void *val);
static int map_redist(Map_t *map);

int map_init(Map_t *map, size_t key_size, size_t val_size, int (*cmp)(void *, void *))
{
  if (map == NULL || key_size <= 0 || val_size <=0 || cmp == NULL) return -1;

  return list_init(&map->list, sizeof(Pair_t), 8);
}

int map_deinit(Map_t *map)
{
  // TODO: Deinitialize map
  return 0;
}

int map_add(Map_t *map, void *key, void *val)
{
  // TODO: Add pair to map
  return 0;
}

int map_rem(Map_t *map, void *key, void *val)
{
  // TODO: Remove pair from map
  return 0;
}

int map_get(Map_t *map, void *key, void *val)
{
  // TODO: Deinitialize map
  return 0;
}

static Pair_t *map_create_pair(Map_t *map, void *key, void *val)
{
  // TODO: Malloc Pair for map
  return NULL;
}

static int map_redist(Map_t *map)
{
  // TODO: redistribute pairs and resize list
  return 0;
}

#ifdef __cplusplus
}
#endif
