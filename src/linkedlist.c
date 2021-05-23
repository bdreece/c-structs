/*! \file linkedlist.c
 *  \brief LinkedList Implementation
 *  The implementation of the LinkedList data structure
 */

#include "linkedlist.h"

#include <stdlib.h>
#include <string.h>

static Node_t *linkedlist_create_node(LinkedList_t *list, void *elem);

int linkedlist_init(LinkedList_t *list, size_t size, bool circ)
{
  if (list == NULL)
    return -1;

  list->circ = circ;
  list->len = 0;
  list->size = size;
  list->first = NULL;
  list->last = NULL;

  return 0;
}

int linkedlist_deinit(LinkedList_t *list)
{
  if (list == NULL || list->first == NULL || list->last == NULL)
    return -1;

  list->len = 0;

  if (list->first->next == list->last)
  {
    free(list->first->elem);
    free(list->first);
    list->first = NULL;
  } else
  {
    Node_t *walk = list->first->next;

    while (walk != NULL)
    {
      free(walk->prev->elem);
      free(walk->prev);
      walk->prev = NULL;
      walk = walk->next;
    }
  }

  free(list->last->elem);
  free(list->last);
  list->last = NULL;
  return 0;
}

Node_t *linkedlist_insert_after(LinkedList_t *list, Node_t *node, void *elem)
{
  if (list == NULL || list->first == NULL || list->last == NULL || node == NULL)
    return NULL;

  Node_t *new_node = linkedlist_create_node(list, elem);

  new_node->prev = node;
  node->next = new_node;

  if (node == list->last)
  {
    list->last = new_node;

    if (list->circ)
    {
      new_node->next = list->first;
      list->first->prev = new_node;
    }
  } else if (node->next != NULL)
  {
    new_node->next = node->next;
    node->next->prev = new_node;
  } else return NULL;

  return new_node;
}

Node_t *linkedlist_insert_before(LinkedList_t *list, Node_t *node, void *elem)
{
  if (list == NULL || list->first == NULL || list->last == NULL || node == NULL)
    return NULL;

  Node_t *new_node = linkedlist_create_node(list, elem);

  new_node->next = node;
  node->prev = new_node;

  if (node == list->first)
  {
    list->first = new_node;

    if (list->circ)
    {
      new_node->prev = list->last;
      list->last->next = new_node;
    }
  } else if (node->prev != NULL)
  {
    new_node->prev = node->prev;
    node->prev->next = new_node;
  } else return NULL;

	list->len++;

  return new_node;
}

Node_t *linkedlist_add(LinkedList_t *list, void *elem)
{
  if (list == NULL)
    return NULL;

  Node_t *new_node = linkedlist_create_node(list, elem);

  if (list->first == NULL && list->last == NULL)
  {
    list->first = new_node;
    list->last = new_node;
  } else if (list->first == list->last)
  {
    list->last = new_node;
  } else
  {
    list->last->next = new_node;
    new_node->prev = list->last;

    if (list->circ)
      list->first->prev = new_node;

    list->last = new_node;
  }

	list->len++;

  return new_node;
}

int linkedlist_remove(LinkedList_t *list, Node_t *node, void *elem)
{
  if (list == NULL || list->first == NULL || list->last == NULL || node == NULL || elem == NULL)
    return -1;

  if (node == list->first)
  {
    if (node == list->last)
    {
      list->first = NULL;
      list->last = NULL;
    } else
    {
      Node_t *new_first = node->next;

      if (list->circ)
        new_first->prev = list->last;
      else
        new_first->prev = NULL;
    }
  } else if (node == list->last)
  {
    Node_t *new_last = node->prev;

    if (list->circ)
      new_last->next = list->first;
    else
      new_last->next = NULL;
  } else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  node->prev = NULL;
  node->next = NULL;
  memcpy(elem, node->elem, list->size);

  free(node->elem);
  free(node);
  node = NULL;

	list->len--;

  return 0;
}

int linkedlist_set(LinkedList_t *list, Node_t *node, void *elem)
{
  if (list == NULL || list->first == NULL || elem == NULL)
    return -1;

  if (node->elem == NULL)
    node->elem = malloc(list->size);

  memcpy(node->elem, elem, list->size);

  return 0;
}

int linkedlist_get(LinkedList_t *list, Node_t *node, void *elem)
{
	if (list == NULL || list->first == NULL || elem == NULL)
		return -1;

	memcpy(elem, node->elem, list->size);

	return 0;
}

static Node_t *linkedlist_create_node(LinkedList_t *list, void *elem)
{
  Node_t *new_node = malloc(sizeof(struct Node));
  new_node->elem = malloc(list->size);
  new_node->prev = NULL;
  new_node->next = NULL;
  memcpy(new_node->elem, elem, list->size);
  return new_node;
}
