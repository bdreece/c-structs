/*! \file heap.h
 *  \brief Header file for the Heap data structure implementation.
 */

#ifndef HEAP_H
#define HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  MINHEAP = 0,
  MAXHEAP = 1
} HeapType_t;

typedef struct {
  List_t list;
  HeapType_t type;
  int (*cmp)(void *, void *);
} Heap_t;

int heap_init(Heap_t *heap, size_t size, HeapType_t type, int (*cmp)(void *, void *));
int heap_deinit(Heap_t *heap);

int heap_add(Heap_t *heap, void *element);
int heap_remove(Heap_t *heap, void *element);

static int heapify(Heap_t *heap);

#ifdef __cplusplus
}
#endif

#endif // HEAP_H
