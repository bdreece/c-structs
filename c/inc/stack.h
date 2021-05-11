/*! \file stack.h
 *  \brief Stack Header File
 *  Header file for the stack data structure implementation.
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  ArrayList_t data;
} Stack_t;

void stack_init(Stack_t *stack, int initialCapacity);
void stack_deinit(Stack_t *stack);

void stack_push(Stack_t *stack, void *element);
void 

#ifdef __cplusplus
}
#endif

#endif // STACK_H
