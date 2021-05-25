/*! \file heap.h
 *  \brief Header file for the Heap data structure implementation.
 */

#ifndef HEAP_H
#define HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "list.h"

enum heap_type {
  MINHEAP = 0,
  MAXHEAP = 1
};

typedef struct {
  List_t list;
  enum heap_type type;
  int (*cmp)(void *, void *);
} Heap_t;

int heap_init(Heap_t *heap, size_t size, enum heap_type type, int (*cmp)(void *, void *));
int heap_deinit(Heap_t *heap);

int heap_add(Heap_t *heap, void *elem);
int heap_rem(Heap_t *heap, void *elem);

#ifdef __cplusplus
}
#endif

#endif // HEAP_H
