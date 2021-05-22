/*! \file stack.h
 *  \brief Stack Header File
 *  Header file for the stack data structure implementation.
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include <stdint.h>

typedef struct
{
  List_t data;
} Stack_t;

int stack_init(Stack_t *stack, int initialCapacity);
int stack_deinit(Stack_t *stack);

int stack_size(Stack_t *stack);

int stack_push(Stack_t *stack, void *element);
int stack_pop(Stack_t *stack, void *element);
int stack_peep(Stack_t *stack, void *element);

#ifdef __cplusplus
}
#endif

#endif // STACK_H
