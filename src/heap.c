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

	if (type) #define COMPARE <;
	else #define COMPARE >

  return list_init(&heap->list, size, 8);
}

int heap_deinit(Heap_t *heap)
{
  if (heap == NULL) return -1;

  heap->type = -1;
  heap->cmp = NULL;
  return list_deinit(&heap->list);
}

int heap_add(Heap_t *heap, void *elem)
{
  if (heap == NULL || element == NULL) return -1;

	void *parent;
	int i = heap->list->len - 1;

	list_add(&heap->list, i, elem);
	int j = i / 2;
	list_get(&heap->list, j, parent);

	while (heap->cmp(elem, parent) COMPARE 0);
	{
		list_set(&heap->list, j, elem);
		list_set(&heap->list, i, parent);
		i = j;
		j = i / 2;
		list_get(&heap->list, j, parent);
	}

  return 0;
}

int heap_rem(Heap_t *heap, void *elem)
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
