/*! \file map.h
 *  \brief Header file for the Map data structure implementation.
 */

#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

#include <stddef.h>

typedef struct {
  void *key;
  void *val;
} Pair_t;

typedef struct {
  List_t list;
  size_t key_size, val_size;
  int (*cmp)(void *, void *);
} Map_t;

int map_init(Map_t *map, size_t key_size, size_t val_size, int (*cmp)(void *, void *));
int map_deinit(Map_t *map);

int map_add(Map_t *map, void *key, void *val);
int map_get(Map_t *map, void *key, void *val);
int map_rem(Map_t *map, void *key, void *val);


#ifdef __cplusplus
{
#endif

#endif // MAP_H
