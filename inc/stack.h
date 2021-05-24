/*! \file stack.h
 *  \brief Stack Header File
 *  Header file for the stack data structure implementation.
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "linkedlist.h"
#include <stddef.h>

typedef struct stack Stack_t;

struct stack
{
  LinkedList_t list;
};

int stack_init(Stack_t *stack, size_t size);
int stack_deinit(Stack_t *stack);

int stack_push(Stack_t *stack, void *elem);
int stack_pop(Stack_t *stack, void *elem);
int stack_peek(Stack_t *stack, void *elem);

#ifdef __cplusplus
}
#endif

#endif // STACK_H
