#ifndef SPI_H_
#define SPI_H_

#include "queue.h"
#include "buffer.h"

/**
 * Defines a function pointer type which receives a buffer containing
 * the received bytes of an SPI transfer.
 */
typedef void (*spi_receive)(buffer_t *buffer);

/**
 * Initializes the spi_queue system. Must be called before global interrupts
 * are enabled.
 *
 * @param queue_size the maximum size of the
 *        transfer queue
 */
void spi_queue_init();

/**
 * Adds a buffer to the SPI queue. The contents of 'send' will be
 * transmitted. After all bytes are sent, the received bytes will
 * be passed to 'callback'. Callers retain ownership of both buffers.
 */
void spi_queue_add(buffer_t *send, spi_receive callback);


#endif /* SPI_H_ */
