/*
 * buffer.c
 *
 *  Created on: Jun 13, 2015
 *      Author: mrenouf
 */

#include "ptr_buffer.h"

ptr_buffer_t *ptr_buffer_create(size_t capacity) {
  ptr_buffer_t *b = malloc(sizeof(ptr_buffer_t));
  void *data = malloc(capacity * sizeof(void *));
  b->start = data;
  b->capacity = capacity;
  b->position = data;
  b->end = data + (capacity * sizeof(void *));
  b->limit = b->end;
  return b;
}

void ptr_buffer_destroy(ptr_buffer_t *buffer) {
  free(buffer->start);
  buffer->start = NULL;
  buffer->position = NULL;
  buffer->limit = NULL;
  buffer->end = NULL;
  buffer->capacity = 0;
  free(buffer);
}

void ptr_buffer_put(ptr_buffer_t *buffer, void *value) {
  if (buffer->position >= buffer->limit) {
    abort();
  }
  *(buffer->position) = value;
  buffer->position++;
}

void *ptr_buffer_get(ptr_buffer_t *buffer) {
  //if (buffer->position >= buffer->limit) {
  //  abort();
  //}
  void *value = *(buffer->position);
  buffer->position++;
  return value;
}

void ptr_buffer_limit(ptr_buffer_t *buffer, uint8_t limit) {
  if (limit > buffer->capacity) {
    return;
  }
  buffer->limit = buffer->start + limit;
  if (buffer->position > buffer->limit) {
    buffer->position = buffer->limit;
  }
}

uint8_t ptr_buffer_remaining(ptr_buffer_t *buffer) {
  return buffer->limit - buffer->position;
}

uint8_t ptr_buffer_position(ptr_buffer_t *buffer) {
  return buffer->position - buffer->start;
}

void ptr_buffer_flip(ptr_buffer_t *buffer) {
  buffer->limit = buffer->position;
  buffer->position = buffer->start;
}

void ptr_buffer_reset(ptr_buffer_t *buffer) {
  buffer->position = buffer->start;
  buffer->limit = buffer->end;
}
