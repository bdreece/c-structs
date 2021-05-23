/*! \file List.c
 *  \brief List Implementation
 */

#include "list.h"

#include <stdlib.h>
#include <string.h>

static int list_resize(List_t *list);

int list_init(List_t *list, size_t size, size_t cap)
{
  if (list == NULL)
    return -1;

  list->cap = cap;
  list->size = size;
  list->len = 0;

  list->data = malloc(cap * size);

  if (list->data == NULL)
    return -1;

  list->first = list->data;
  list->last = list->data;

	list->add = list_add;
	list->rem = list_rem;
	list->get = list_get;
	list->set = list_set;

  return 0;
}

int list_deinit(List_t *list)
{
  if (list == NULL || list->data == NULL)
    return -1;

  free(list->data);
  list->cap = 0;
  list->size = 0;
  list->len = 0;
  list->first = NULL;
  list->last = NULL;

  return 0;
}

int list_add(List_t *list, int i, void *elem)
{
  if (list == NULL || list->data == NULL)
    return -1;

  if (i < 0 || i > list->len)
    return -1;

  if (list->len >= list->cap)
  {
    if (list_resize(list) < 0)
      return -1;
  }

  if (list->data[i] != NULL)
  {
    int j;
    for (j = list->len; j > i; j--)
      list->data[j] = list->data[j - 1];
  }

  memcpy(list->data[i], elem, list->size);
  list->len++;
  return 0;
}

int list_rem(List_t *list, int i, void *elem)
{
  if (list == NULL || list->data == NULL || elem == NULL)
    return -1;

  if (i < 0 || i >= list->len)
    return -1;

  memcpy(elem, list->data[i], list->size);

  int j;
  for (j = i; j < list->len - 1; j++)
  {
    list->data[j] = list->data[j + 1];
  }

  return 0;
}

int list_set(List_t *list, int i, void *elem)
{
  if (list == NULL || list->data == NULL || elem == NULL)
    return -1;

  if (i < 0 || i > list->len)
    return -1;

  if (list->len >= list->cap)
  {
    if (list_resize(list) < 0)
      return -1;
  }

  memcpy(list->data[i], elem, list->size);
  return 0;
}

int list_get(List_t *list, int i, void *elem)
{
	if (list == NULL || list->data == NULL || elem == NULL)
		return -1;

	if (i < 0 || i > list->len)
		return -1;

	memcpy(elem, list->data[i], list->size);
	return 0;
}

static int list_resize(List_t *list)
{
  void **tmp = realloc(list->data, 2 * list->cap * list->size);
  if (tmp == NULL)
    return -1;

  list->data = tmp;
  return 0;
}
