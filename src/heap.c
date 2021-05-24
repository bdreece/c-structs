//! \file heap.c

#ifdef __cplusplus
extern "C" {
#endif

#include "heap.h"
#include "list.h"
#include <string.h>

static int heap_bubble(Heap_t *heap, int i);
static int heap_sink(Heap_t *heap, int i);

int heap_init(Heap_t *heap, size_t size, HeapType_t type, int (*cmp)(void *, void *))
{
  // TODO: Initialize heap
  return 0;
}

int heap_deinit(Heap_t *heap)
{
  // TODO: Deinitialize heap
  return 0;
}

int heap_add(Heap_t *heap)
{
  // TODO: Add a value to the heap
  return 0;
}

int heap_rem(Heap_t *heap)
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
