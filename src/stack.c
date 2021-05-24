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

  return linkedlist_init(&stack->list, size, false);
}

int stack_deinit(Stack_t *stack)
{
  return linkedlist_deinit(&stack->list);
}

int stack_push(Stack_t *stack, void *elem)
{
  Node_t *ret = linkedlist_insert_before(&stack->list, stack->list.first, elem);
  return (ret != NULL) ? 0 : -1;
}

int stack_pop(Stack_t *stack, void *elem)
{
  return linkedlist_rem(&stack->list, stack->list.first, elem);
}

int stack_peek(Stack_t *stack, void *elem)
{
  return linkedlist_get(&stack->list, stack->list.first, elem);
}

#ifdef __cplusplus
}
#endif
