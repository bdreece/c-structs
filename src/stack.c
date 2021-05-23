//! \file stack.c

#include "stack.h"
#include "linkedlist.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int stack_init(Stack_t *stack, size_t size)
{
  if (stack == NULL) return -1;

  stack->data = (LinkedList_t *) malloc(sizeof(LinkedList_t));
  if (stack->data == NULL) return -1;

  return linkedlist_init(stack->data, size, false);
}

int stack_deinit(Stack_t *stack)
{
  int ret = linkedlist_deinit(stack->data);

  free(stack->data);

  return ret;
}

int stack_push(Stack_t *stack, void *elem)
{
  Node_t *ret = linkedlist_insert_before(stack->data, stack->data->first, elem);
  return (ret != NULL) ? 0 : -1;
}

int stack_pop(Stack_t *stack, void *elem)
{
  return linkedlist_remove(stack->data, stack->data->first, elem);
}

int stack_peep(Stack_t *stack, void *elem)
{
  return linkedlist_get(stack->data, stack->data->first, elem);
}

#ifdef __cplusplus
}
#endif
