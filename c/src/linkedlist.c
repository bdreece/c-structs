/*! \file linkedlist.c
 *  \brief LinkedList Implementation
 *  The implementation of the LinkedList data structure
 */

#include "linkedlist.h"

#include <stdlib.h>
#include <string.h>

int linkedlist_init(LinkedList_t *list, size_t element_size, bool circular)
{
  if (list == NULL)
    return -1;

  list->circular = circular;
  list->size = 0;
  list->elem_size = element_size;
  list->first = NULL;
  list->last = NULL;
}

int linkedlist_deinit(LinkedList_t *list)
{
  if (list == NULL || list->first == NULL || list->last == NULL)
    return -1;

  list->size = 0;

  if (list->first->next == list->last)
  {
    free(list->first->element);
    free(list->first);
    list->first = NULL;
  } else
  {
    Node_t *walk = list->first->next;

    while (walk != NULL)
    {
      free(walk->prev->element);
      free(walk->prev);
      walk->prev = NULL;
      walk = walk->next;
    }
  }

  free(list->last->element);
  free(list->last);
  list->last = NULL;
  return 0;
}

Node_t *linkedlist_insert_after(LinkedList_t *list, Node_t *node, void *element)
{
  if (list == NULL || list->first == NULL || list->last == NULL || node == NULL)
    return NULL;

  Node_t *new_node = linkedlist_create_node(list, element);

  new_node->prev = node;
  node->next = new_node;

  if (node == list->last)
  {
    list->last = new_node;

    if (list->circular)
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

Node_t *linkedlist_insert_before(LinkedList_t *list, Node_t *node, void *element)
{
  if (list == NULL || list->first == NULL || list->last == NULL || node == NULL)
    return NULL;

  Node_t *new_node = linkedlist_create_node(list, element);

  new_node->next = node;
  node->prev = new_node;

  if (node == list->first)
  {
    list->first = new_node;

    if (list->circular)
    {
      new_node->prev = list->last;
      list->last->next = new_node;
    }
  } else if (node->prev != NULL)
  {
    new_node->prev = node->prev;
    node->prev->next = new_node;
  } else return NULL;

  return new_node;
}

Node_t *linkedlist_add(LinkedList_t *list, void *element)
{
  if (list == NULL)
    return NULL;

  Node_t *new_node = linkedlist_create_node(list, element);

  if (list->first == NULL && list->last == NULL)
  {
    list->first = new_node;
  }

  if (list->first == list->last)
  {
    list->last = new_node;
  } else
  {
    list->last->next = new_node;
    new_node->prev = list->last;

    if (list->circular)
      list->first->prev = new_node;

    list->last = new_node;
  }

  return new_node;
}

void *linkedlist_remove(LinkedList_t *list, Node_t *node)
{

}

void *linkedlist_set(LinkedList_t *list, Node_t *node, void *val)
{

}

static Node_t *linkedlist_create_node(void *val)
{
  Node_t *new_node = malloc(sizeof(struct Node));
  new_node->element = malloc(list->elem_size);
  new_node->prev = NULL;
  new_node->next = NULL;
  memcpy(new_node->element, element, list->elem_size);
  return new_node;
}
