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

typedef struct {
  LinkedList_t *data;
  size_t size;
  size_t len;
  bool circ;
} Queue_t;

int queue_init(Queue_t *queue, size_t size, bool circ);
int queue_deinit(Queue_t *queue);

int queue_peek(Queue_t *queue, void *element);
int queue_enq(Queue_t *queue, void *element);
int queue_deq(Queue_t *queue, void *element);

#ifdef __cplusplus
}
#endif

#endif // QUEUE_H
