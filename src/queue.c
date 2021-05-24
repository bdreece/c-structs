//! \file queue.c

#ifdef __cplusplus
extern "C" {
#endif

#include "queue.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

int queue_init(Queue_t *queue, size_t size, bool circ)
{
	if (queue == NULL || size <= 0) return -1;

	return linkedlist_init(&queue->list, size, circ);
}

int queue_deinit(Queue_t *queue)
{
	if (queue == NULL)
		return -1;

	return linkedlist_deinit(&queue->list);
}

int queue_peek(Queue_t *queue, void *elem)
{
	if (queue == NULL || elem == NULL) return -1;

	return linkedlist_get(&queue->list, queue->list.first, elem);
}

int queue_enq(Queue_t *queue, void *elem)
{
	if (queue == NULL || elem == NULL) return -1;

	Node_t *node = linkedlist_add(&queue->list, elem);
	return (node != NULL) ? 0 : -1;
}

int queue_deq(Queue_t *queue, void *elem)
{
	if (queue == NULL || elem == NULL) return -1;

	return linkedlist_rem(&queue->list, queue->list.first, elem);
}

#ifdef __cplusplus
}
#endif
