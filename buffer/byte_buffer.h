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
} byte_buffer_t;

byte_buffer_t  *byte_buffer_create(size_t capacity);
void byte_buffer_destroy(byte_buffer_t *buffer);

void byte_buffer_put(byte_buffer_t *buffer, uint8_t value);
uint8_t byte_buffer_get(byte_buffer_t *buffer);

void byte_buffer_limit(byte_buffer_t *buffer, uint8_t limit);

uint8_t byte_buffer_position(byte_buffer_t *buffer);
uint8_t byte_buffer_remaining(byte_buffer_t *buffer);

void byte_buffer_flip(byte_buffer_t *buffer);

void byte_buffer_reset(byte_buffer_t *buffer);

#endif /* BUFFER_H_ */
