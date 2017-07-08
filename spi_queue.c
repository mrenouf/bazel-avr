/*
 * spi.c
 *
 *  Created on: Jun 28, 2015
 *      Author: mrenouf
 */

#include <avr/interrupt.h>
#include <avr/delay.h>
#include "spi_queue.h"
#include "port_addr.h"

typedef struct {
	uint8_t ss_port;
	uint8_t ss_mask;
	buffer_t *tx;
	buffer_t *rx;
	spi_receive callback;

} spi_transfer_t;

static spi_transfer_t *spi_transfer_create(buffer_t* send, spi_receive callback);
static void spi_transfer_destroy(spi_transfer_t *transfer);

static queue_t *spi_queue;
static volatile spi_transfer_t *active_transfer;


void spi_queue_init(int queue_size) {
	spi_queue = queue_create(queue_size);
	SPCR |= _BV(SPE) | _BV(SPIE);
}

void spi_queue_add(buffer_t *send, uint8_t ss_port, uint8_t ss_mask, spi_receive callback) {
	if (!send || !buffer_remaining(send)) return;
	spi_transfer_t *created = spi_transfer_create(send, callback);
	cli();
	if (!active_transfer) {
		active_transfer = created;
		start_next();
	} else {
		queue_add(spi_queue, created);
	}
	sei();
}

static spi_transfer_t *spi_transfer_create(buffer_t *send, uint8_t ss_port, uint8_t ss_mask, spi_receive callback) {
	spi_transfer_t *t = malloc(sizeof(spi_transfer_t));
	t->callback = callback;
	t->tx = send;
	t->rx = buffer_create(buffer_remaining(t->tx));
	t->ss_port = ss_port;
	t->ss_mask = ss_mask;
	return t;
}

static void spi_transfer_destroy(spi_transfer_t *t) {
	// receive buffer is owned by spi_queue
	buffer_destroy(active_transfer->rx);
	t->tx = NULL;
	t->callback = NULL;
	free((void *)t);
}

static inline void start_next() {
	_SFR_IO8(active_transfer->ss_port) &= ~_BV(active_transfer->ss_mask);
	_delay_us(1);
	SPDR = buffer_get(active_transfer->tx);
}


ISR (SPI_STC_vect) {
	if (active_transfer) {
		buffer_put(active_transfer->rx, SPDR);
		if (buffer_remaining(active_transfer->tx)) {
			SPDR = buffer_get(active_transfer->tx);
		} else {
			_SFR_IO8(active_transfer->ss_port) |= _BV(active_transfer->ss_mask);
			active_transfer->callback(active_transfer->rx);
			spi_transfer_destroy((spi_transfer_t *) active_transfer);
			active_transfer = NULL;

			if (queue_available(spi_queue)) {
				active_transfer = queue_remove(spi_queue);
				start_next();
			}
		}
	}
}
