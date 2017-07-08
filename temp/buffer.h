/*
 * buffer.h
 *
 *  Created on: Jun 13, 2015
 *      Author: mrenouf
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
	uint8_t *start;
	size_t capacity;
	uint8_t *position;
	uint8_t *limit;
	uint8_t *end;
} buffer_t;

extern buffer_t *buffer_create(size_t capacity);
extern void buffer_destroy(buffer_t *buffer);

void buffer_put(buffer_t *buffer, uint8_t value);
uint8_t buffer_get(buffer_t *buffer);

void buffer_limit(buffer_t *buffer, uint8_t limit);

uint8_t buffer_position(buffer_t *buffer);
uint8_t buffer_remaining(buffer_t *buffer);

void buffer_flip(buffer_t *buffer);

void buffer_reset(buffer_t *buffer);

#endif /* BUFFER_H_ */
