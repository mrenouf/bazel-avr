#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include <stdarg.h>
#include "port_macros.h"
#include "timers.h"
#include "spcr.h"
#include "teensy.h"
#include "profile.h"
//#include "usb_log.h"

#include <string.h>
#include "buffer.h"

#define BAUD 9600
//#define BAUD 115200
#include <util/setbaud.h>

#define TEMP_F(x) (((x) / (0.555555556)) + 32)

void write_char(uint8_t ch);
void start_write_display();


static buffer_t *buf;

// static struct pt pt1, pt2;

static therm_t t;

// Trinket Pro (ATMega328P)
#define UBRRL UBRR0L
#define UBRRH UBRR0H
#define U2X U2X0
#define UCSZ0 UCSZ00
#define UCSZ1 UCSZ01
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define RXEN RXEN0
#define TXEN TXEN0
#define UDR UDR0
#define UDRE UDRE0
//#define USART_UDRE_vect USART_UDRE_vect

// Teensy++ ATMega32U4
/*
#define UBRRL UBRR1L
#define UBRRH UBRR1H
#define U2X U2X1
#define UCSZ0 UCSZ10
#define UCSZ1 UCSZ11
#define UCSRA UCSR1A
#define UCSRB UCSR1B
#define UCSRC UCSR1C
#define RXEN RXEN1
#define TXEN TXEN1
#define UDR UDR1
#define UDRE UDRE1
#define USART_UDRE_vect USART1_UDRE_vect
*/

void init_serial(void) {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    #if USE_2X
    UCSRA |= (1 << U2X);
    #else
    UCSRA &= ~(1 << U2X);
    #endif
    UCSRC = _BV(UCSZ1) | _BV(UCSZ0); // 8-bit data, 1 stop bit, no parity
    UCSRB |= _BV(RXEN) | _BV(TXEN);  // Enable RX and TX
}

void init_spi() {
	OUTPUT(SS);
	OUTPUT(SCLK);
	INPUT(MISO);
	OUTPUT(MOSI);
	SET(SS);
	/* Enable SPI, enable interrupt on SPI complete, SPI clock = F_CPU/8 */
	SPCR = _BV(SPE) | /*_BV(SPIE) | */_BV(MSTR) | SPI_CLK_SCALE_16;
}

void led_clear() {
	write_char(0x76);
}

void led_format(float temp, buffer_t *ser_buf) {
	char s[] = {0, 0, 0, 0, 0, 0}; // 4 digits, decimal + null
	snprintf(s, sizeof(s), "%6.2f", (double) temp);
	buffer_reset(ser_buf);
	//byte_buffer_put(ser_buf, 0x76); // clear
	size_t count = strlen(s);
	uint8_t digits = count;
	if (strrchr(s, '.')) {
		digits--;
	}
	if (count < 4) {
		// left-pad with spaces
		for (int i = 0; i < 4 - count; i++) {
			buffer_put(ser_buf, ' ');
		}
	}
	for (int i = 0; i < count; i++) {
		if (s[i] == '.' && i > 0 && i < 4) {
			buffer_put(ser_buf, 0x77); // decimal point control
			buffer_put(ser_buf, 1 << (i - 1)); // position (1=1.234, 2=12.34, 4=123.4)
		} else {
			buffer_put(ser_buf, s[i]);
			digits++;
		}
	}
}

void serial_debug(float temp, buffer_t *ser_buf) {
//	char s[] = {32, 32, 32, 32, 32, '\n'}; // 4 digits, decimal + newline + null
	char s[] = "     \r\n";
	snprintf(s, sizeof(s), "%6.2f", (double) temp);
	buffer_reset(ser_buf);
	int count = strlen(s);
	for (int i = 0; i < count; i++) {
			buffer_put(ser_buf, s[i]);
	}
	buffer_put(ser_buf, '\r');
	buffer_put(ser_buf, '\n');
}

void decode_31855(buffer_t *buffer, therm_t* therm) {
	int32_t raw =
			((int32_t) buffer_get(buffer)) << 24
			| ((int32_t) buffer_get(buffer)) << 16
			| ((int32_t) buffer_get(buffer)) << 8
			| ((int32_t) buffer_get(buffer));
	therm->jct = ((int16_t) (raw >> 18)) / 4.0;
	therm->ref = (((int16_t) raw) >> 4) / 16.0;
	therm->fault = (raw & 0x10000) != 0;
	therm->scv = (raw & 4) != 0;
	therm->scg = (raw & 2) != 0;
	therm->oc = (raw & 1) != 0;
}

void start_read_temp() {
	buffer_reset(buf);
	CLEAR(SS);
	SPDR = 0;
}

// SPI Transfer complete
ISR (SPI_STC_vect) {
	buffer_put(buf, SPDR);
	if (buffer_position(buf) < 4) {
		SPDR = 0;
	} else {
		SET(SS);
		buffer_flip(buf);
		decode_31855(buf, &t);
		buffer_reset(buf);
		led_format(t.jct, buf);
		buffer_flip(buf);
		start_write_display();
	}
}

void start_write_display() {
	if (buffer_remaining(buf) > 0) {
		//if ((UCSR1A & (1 << UDRE1))) {
			UDR = buffer_get(buf);
		//}
	}
}

// UART Data register empty
ISR(USART_UDRE_vect) {
	if (buffer_remaining(buf) > 0) {
		UDR = buffer_get(buf);
	} else {
		start_read_temp();
	}
}

void write_char(uint8_t ch) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = ch;
}

float avg_temp(float t) {
	static float t1 = 0;
	static float t2 = 0;
	static float t3 = 0;
	static float t4 = 0;

	float r = t + t1 + t2 + t3 + t4;
	r /= 5.0;
	t4 = t3;
	t3 = t2;
	t2 = t1;
	t1 = t;
	return r;
}

void read_31855() {
	CLEAR(SS);
	_delay_us(1);
	while(buffer_position(buf) < 4) {
		SPDR = 0;
		while(!(SPSR & _BV(SPIF)));
		buffer_put(buf, SPDR);
	}
	SET(SS);
}



int main(void) {
	cli();
	buf = buffer_create(64);
	init_spi();
	init_serial();
	//led_clear();
    write_char('H');
    write_char('E');
    write_char('L');
    write_char('L');
    write_char('O');
    write_char('\r');
    write_char('\n');
    for (;;);
	for (;;) {
		buffer_reset(buf);
		read_31855();
		buffer_flip(buf);
		decode_31855(buf, &t);
		buffer_reset(buf);
		//led_format(avg_temp(TEMP_F(t.jct)), buf);
		serial_debug(t.jct, buf);
		buffer_flip(buf);
		while (buffer_remaining(buf) > 0) {
			write_char(buffer_get(buf));
		}
		_delay_ms(250);
	}
}
