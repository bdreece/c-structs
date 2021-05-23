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

	queue->list = (LinkedList_t *) malloc(sizeof(LinkedList_t));
	if (queue->list == NULL) return -1;

	return linkedlist_init(queue->list, size, circ);
}

int queue_deinit(Queue_t *queue)
{
	if (queue == NULL)
		return -1;

	return linkedlist_deinit(queue->list);
}

#ifdef __cplusplus
}
#endif
