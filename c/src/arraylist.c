/*! \file arraylist.c
 *  \brief ArrayList Implementation
 */

#include "arraylist.h"

#include <stdlib.h>

int arraylist_init(ArrayList_t *list, int length)
{
  if (list == NULL)
    return -1;

  list->capacity = length;
  list->size = 0;

  list->data = malloc(length * sizeof(void *));

  if (list->data == NULL)
    return -1;

  list->first = list->data;
  list->last = list->data;

  return 0;
}

int arraylist_deinit(ArrayList_t *list)
{
  if (list == NULL || list->data == NULL)
    return -1;

  free(list->data);
  list->capacity = 0;
  list->size = 0;
  list->first = NULL;
  list->last = NULL;

  return 0;
}

int arraylist_add(ArrayList_t *list, void *val)
{
  if (list == NULL || list->data == NULL)
    return -1;

  if (list->size >= list->capacity)
  {
    if (arraylist_resize(list) < 0)
      return -1;
  }

  list->data[++(list->size)] = val;
  return 0;
}

int arraylist_insert(ArrayList_t *list, int i, void *val)
{
  if (list == NULL || list->data == NULL)
    return -1;

  if (i < 0 || i > list->size)
    return -1;

  if (list->size >= list->capacity)
  {
    if (arraylist_resize(list) < 0)
      return -1;
  }

  if (list->data[i] != NULL)
  {
    int j;
    for (j = list->size; j > i; j--)
      list->data[j] = list->data[j - 1];
  }

  list->data[i] = val;
  list->size++;
  return 0;
}

void *arraylist_set(ArrayList_t *list, int i, void *val)
{
  if (list == NULL || list->data == NULL)
    return NULL;

  if (i < 0 || i > list->size)
    return NULL;

  if (list->size >= list->capacity)
  {
    if (arraylist_resize(list) < 0)
      return NULL;
  }

  void *retval = list->data[i];
  list->data[i] = val;
  return retval;
}

void *arraylist_remove(ArrayList_t *list, int i)
{
  if (list == NULL || list->data == NULL)
    return NULL;

  if (i < 0 || i >= list->size)
    return NULL;

  void *retval = list->data[i];

  int j;
  for (j = i; j < list->size - 1; j++)
  {
    list->data[j] = list->data[j + 1];
  }

  return retval;
}

static int arraylist_resize(ArrayList_t *list)
{
  void **tmp = realloc(list->data, 2 * list->capacity * sizeof(void *));
  if (tmp == NULL)
    return -1;

  list->data = tmp;
  return 0;
}
