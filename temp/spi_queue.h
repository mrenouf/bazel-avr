/*
 * spi_queue.h
 *
 *  Created on: Jun 27, 2015
 *      Author: mrenouf
 */

#ifndef SPI_QUEUE_H_
#define SPI_QUEUE_H_

#include "buffer.h"

#define MAX_QUEUE_LEN 100

typedef struct {
	byte_buffer_t queue; // the queue - a buffer of buffers
	byte_buffer_t free; // a buffer of recyclable buffers
} queue_t;

#endif /* SPI_QUEUE_H_ */
