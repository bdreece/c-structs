//! \file heap.c

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "list.h"
#include "heap.h"

static int heap_bubble(Heap_t *heap, int i);
static int heap_sink(Heap_t *heap, int i);

int heap_init(Heap_t *heap, size_t size, enum heap_type type, int (*cmp)(void *, void *))
{
  if (heap == NULL || size <= 0 || cmp == NULL) return -1;

  heap->type = type;
  heap->cmp = cmp;

  return list_init(&heap->list, size, 8);
}

int heap_deinit(Heap_t *heap)
{
  if (heap == NULL) return -1;

  heap->type = -1;
  heap->cmp = NULL;
  return list_deinit(&heap->list);
}

int heap_add(Heap_t *heap, void *element)
{
  // TODO: Add a value to the heap
  return 0;
}

int heap_rem(Heap_t *heap, void *element)
{
  // TODO: Remove top value (min in minheap, vice versa)
  return 0;
}

static int heap_bubble(Heap_t *heap, int i)
{
  // TODO: Bubble up a value
  return 0;
}

static int heap_sink(Heap_t *heap, int i)
{
  // TODO: Sink down a value
  return 0;
}


#ifdef __cplusplus
}
#endif
