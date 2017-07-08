/*
 * buffer.c
 *
 *  Created on: Jun 13, 2015
 *      Author: mrenouf
 */

#include "byte_buffer.h"

byte_buffer_t *byte_buffer_create(size_t capacity) {
  byte_buffer_t *buffer = malloc(sizeof(byte_buffer_t));
  buffer->start = malloc(capacity);
  buffer->capacity = capacity;
  buffer->position = buffer->start;
  buffer->end = buffer->start + capacity;
  buffer->limit = buffer->end;
  return buffer;
}

size_t byte_buffer_capacity(byte_buffer_t *buffer) {
  return buffer->capacity;
}

void byte_buffer_destroy(byte_buffer_t *buffer) {
  free(buffer->start);
  buffer->start = NULL;
  buffer->position = NULL;
  buffer->limit = NULL;
  buffer->end = NULL;
  buffer->capacity = 0;
  free(buffer);
}

void byte_buffer_put(byte_buffer_t *buffer, uint8_t value) {
  if (buffer->position >= buffer->limit) {
    abort();
  }
  *(buffer->position) = value;
  buffer->position++;
}

void byte_buffer_insert(byte_buffer_t *buffer, uint8_t value, uint8_t position) {
  if (buffer->position >= buffer->limit) {
    abort();
  }
}

uint8_t byte_buffer_get(byte_buffer_t *buffer) {
  if (buffer->position >= buffer->limit) {
    abort();
  }
  uint8_t value = *(buffer->position);
  buffer->position++;
  return value;
}

void byte_buffer_limit(byte_buffer_t *buffer, uint8_t limit) {
  if (limit > buffer->capacity) {
    abort();
  }
  buffer->limit = buffer->start + limit;
  if (buffer->position > buffer->limit) {
    buffer->position = buffer->limit;
  }
}

uint8_t byte_buffer_remaining(byte_buffer_t *buffer) {
  return buffer->limit - buffer->position;
}

uint8_t byte_buffer_position(byte_buffer_t *buffer) {
  return buffer->position - buffer->start;
}

void byte_buffer_flip(byte_buffer_t *buffer) {
  buffer->limit = buffer->position;
  buffer->position = buffer->start;
}

void byte_buffer_reset(byte_buffer_t *buffer) {
  buffer->position = buffer->start;
  buffer->limit = buffer->end;
}
