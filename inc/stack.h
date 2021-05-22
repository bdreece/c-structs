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

typedef struct
{
  LinkedList_t *data;
  size_t size;
  size_t len;
} Stack_t;

int stack_init(Stack_t *stack, size_t size);
int stack_deinit(Stack_t *stack);

int stack_push(Stack_t *stack, void *element);
int stack_pop(Stack_t *stack, void *element);
int stack_peep(Stack_t *stack, void *element);

#ifdef __cplusplus
}
#endif

#endif // STACK_H
