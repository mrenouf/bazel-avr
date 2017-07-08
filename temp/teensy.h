/*
 * teensy.h
 *
 * Macros specifically for the Teensy++ hardware.
 */

#ifndef TEENSY_H_
#define TEENSY_H_

#include "port_macros.h"

#define SS         B,0
#define SCLK       B,1
#define MOSI       B,2
#define MISO       B,3

#define EINT0      D,0
#define EINT1      D,1
#define EINT2      D,2
#define EINT3      D,3

#define SCL        D,0
#define SDA        D,1
#define XCK1       D,5    // On short side, no pin
#define RTS        B,7
#define RXD        D,2
#define TXD        D,3
#define CTS        D,5    // On short side, no pin. Shared with ADC12
#define OC0A       B,7
#define OC0B       D,0
#define OC1C       B,7
#define OC3A       C,6
#define OC4A       C,7
#define _OC4A      C,6    // OC4A, inverted
#define OC4B       B,6
#define _OC4B      B,5    // OC4B, inverted
#define OC4D       D,7
#define _OC4D      D,6    // OC4D, inverted, Shared with ADC9, connected to LED
#define OC3A       C,6
#define OC4A       C,7

#define ADC0       F,0
#define ADC1       F,1
#define ADC4       F,4
#define ADC5       F,5
#define ADC6       F,6
#define ADC7       F,7
#define ADC8       D,4    // On short side, no pin. Shared with ICP1
#define ADC9       D,6    // Shared with _OC4D, Connected to LED
#define ADC10      D,7
#define ADC11      B,4
#define ADC12      B,5
#define ADC13      B,6

#define ICP1       D,4    // On short side, no pin. Shared with ADC8
#define ICP3       C,7

#define LED        D,6    // Thge onboard LED is connected to PORTD6

#define LED_INIT  OUTPUT(LED)
#define LED_ON    SET(LED)
#define LED_OFF   CLEAR(LED)

#endif /* TEENSY_H_ */
