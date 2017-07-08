/*
 * buffer.c
 *
 *  Created on: Jun 13, 2015
 *      Author: mrenouf
 */

#include "buffer.h"

buffer_t *buffer_create(size_t capacity) {
	buffer_t *b = malloc(sizeof(buffer_t));
	uint8_t *data = malloc(capacity);
	b->start = data;
	b->capacity = capacity;
	b->position = b->start;
	b->end = data + capacity;
	b->limit = b->end;
	return b;
}

void buffer_destroy(buffer_t *buffer) {
	free(buffer->start);
	buffer->start = NULL;
	buffer->position = NULL;
	buffer->limit = NULL;
	buffer->end = NULL;
	buffer->capacity = 0;
	free(buffer);
}

void buffer_put(buffer_t *buffer, uint8_t value) {
	if (buffer->position >= buffer->limit) {
		abort();
	}
	*(buffer->position) = value;
	buffer->position++;
}

uint8_t buffer_get(buffer_t *buffer) {
	if (buffer->position >= buffer->limit) {
		abort();
	}
	uint8_t value = *(buffer->position);
	buffer->position++;
	return value;
}

void buffer_limit(buffer_t *buffer, uint8_t limit) {
	if (limit > buffer->capacity) {
		return;
	}
	buffer->limit = buffer->start + limit;
	if (buffer->position > buffer->limit) {
		buffer->position = buffer->limit;
	}
}

uint8_t buffer_remaining(buffer_t *buffer) {
	return buffer->limit - buffer->position;
}

uint8_t buffer_position(buffer_t *buffer) {
	return buffer->position - buffer->start;
}


void buffer_flip(buffer_t *buffer) {
	buffer->limit = buffer->position;
	buffer->position = buffer->start;
}

void buffer_reset(buffer_t *buffer) {
	buffer->position = buffer->start;
	buffer->limit = buffer->end;
}
