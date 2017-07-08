/*
 * buffer.h
 *
 *  Created on: Jun 13, 2015
 *      Author: mrenouf
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
	void *start;
	void *end;
	void **head;
	void **tail;
} queue_t;

queue_t *queue_create(size_t capacity);
void queue_dump(queue_t *buffer);
void queue_destroy(queue_t *buffer);
void queue_dump(queue_t *queue);
void queue_add(queue_t *buffer, void *value);
void *queue_remove(queue_t *buffer);
void queue_clear(queue_t *buffer);
size_t queue_available(queue_t *buffer);

#endif /* QUEUE_H_ */
