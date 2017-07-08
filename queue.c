/*
 * buffer.c
 *
 *  Created on: Jun 13, 2015
 *      Author: mrenouf
 */

#include "queue.h"

queue_t *queue_create(size_t capacity) {
	queue_t *q = malloc(sizeof(queue_t));
	void *data = malloc((capacity + 1) * sizeof(void *));
	q->start = data;
	q->head = q->start;
	q->end = q->head + capacity + 1;
	q->tail = q->head;
	return q;
}

void queue_destroy(queue_t  *queue) {
	free(queue->start);
	queue->start = NULL;
	queue->head= NULL;
	queue->tail = NULL;
	free(queue);
}

void queue_add(queue_t *queue, void *value) {
	*(queue->head) = value;
	queue->head++;
	if (queue->head == queue->end) {
		queue->head = queue->start;
	}
	if (queue->head == queue->tail) {
		queue->tail++;
		if (queue->tail == queue->end) {
			queue->tail = queue->start;
		}
	}
}

void *queue_remove(queue_t *queue) {
	if (queue->head == queue->tail) {
		abort();
	}
	void *p = *(queue->tail);
	queue->tail++;
	if (queue->tail == queue->end) {
		queue->tail = queue->start;
	}
	return p;
}

void queue_clear(queue_t *queue) {
	queue->head = queue->tail;
}

size_t queue_available(queue_t *queue) {
	if (queue->head >= queue->tail) {
		return queue->head - queue->tail;
	}
	return (((void **) queue->end) - queue->tail)
				+ (queue->head - ((void **) queue->start));
}
