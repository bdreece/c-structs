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
  stack = (Stack_t *) malloc(sizeof(Stack_t));
  if (stack == NULL) return -1;

  stack->data = (LinkedList_t *) malloc(sizeof(LinkedList_t));
  if (stack->data == NULL) return -1;

  stack->size = size;

  if (linkedlist_init(stack->data, size, false) < 0) return -1;

  return 0;
}

int stack_deinit(Stack_t *stack)
{
  if (linkedlist_deinit(stack->data) < 0)
    return -1;

  free(stack->data);
  free(stack);

  return 0;
}

int stack_push(Stack_t *stack, void *element)
{
  Node_t *ret = linkedlist_insert_before(stack->data, stack->data->first, element);
  if (ret != NULL) stack->len++;
  return (ret == NULL) ? -1 : 0;
}

int stack_pop(Stack_t *stack, void *element)
{
  int ret = linkedlist_remove(stack->data, stack->data->first, element);
  if (ret) stack->len--;
  return ret;
}

int stack_peep(Stack_t *stack, void *element)
{
  if (memcpy(element, stack->data->first->element, stack->size) < 0)
    return -1;

  return 0;
}

#ifdef __cplusplus
}
#endif

