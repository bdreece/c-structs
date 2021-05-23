/*! \file queue.h
 *  \brief Header file for the Queue data structure
 */

#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "linkedlist.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct queue Queue_t;

struct queue
{
  LinkedList_t *list;
	int (*enq)(Queue_t *, void *);
	int (*deq)(Queue_t *, void *);
	int (*peek)(Queue_t *, void *);
};

int queue_init(Queue_t *queue, size_t size, bool circ);
int queue_deinit(Queue_t *queue);

int queue_peek(Queue_t *queue, void *elem);
int queue_enq(Queue_t *queue, void *elem);
int queue_deq(Queue_t *queue, void *elem);

#ifdef __cplusplus
}
#endif

#endif // QUEUE_H
