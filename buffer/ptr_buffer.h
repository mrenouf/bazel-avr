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
void **start;
    size_t capacity;
    void **position;
    void **limit;
    void **end;
} ptr_buffer_t;

ptr_buffer_t *ptr_buffer_create(size_t capacity);
void ptr_buffer_destroy(ptr_buffer_t *buffer);

void ptr_buffer_put(ptr_buffer_t *buffer, void *value);
void *ptr_buffer_get(ptr_buffer_t *buffer);

void ptr_buffer_limit(ptr_buffer_t *buffer, uint8_t limit);

uint8_t ptr_buffer_position(ptr_buffer_t *buffer);
uint8_t ptr_buffer_remaining(ptr_buffer_t *buffer);

void ptr_buffer_flip(ptr_buffer_t *buffer);

void ptr_buffer_reset(ptr_buffer_t *buffer);

#endif /* BUFFER_H_ */
