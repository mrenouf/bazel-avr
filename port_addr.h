/*
 * Defines runtime constants with MMIO register addresses for
 * ports. Use these when a dynamic reference is needed.
 *
 * A trivial example:
 *
 * #include <avr/io.h>
 * #include "port_addr.h"
 *
 * uint8_t read_port(uint8_t port) {
 *     return _SFR_IO8(port);
 * }
 *
 * void main() {
 *     read_port(PORTC_ADDR);
 * }
 *
 */

#ifndef PORT_ADDR_H_
#define PORT_ADDR_H_

#include <avr/io.h>

#ifdef PORTA
extern const uint8_t PORTA_ADDR;
#endif
#ifdef PORTB
extern const uint8_t PORTB_ADDR;
#endif
#ifdef PORTC
extern const uint8_t PORTC_ADDR;
#endif
#ifdef PORTD
extern const uint8_t PORTD_ADDR;
#endif
#ifdef PORTE
extern const uint8_t PORTE_ADDR;
#endif
#ifdef PORTF
extern const uint8_t PORTF_ADDR;
#endif
#ifdef PORTG
extern const uint8_t PORTG_ADDR;
#endif
#ifdef PORTH
extern const uint8_t PORTH_ADDR;
#endif
#ifdef PORTI
extern const uint8_t PORTI_ADDR;
#endif
#ifdef PORTJ
extern const uint8_t PORTJ_ADDR;
#endif
#ifdef PORTK
extern const uint8_t PORTK_ADDR;
#endif
#ifdef PORTL
extern const uint8_t PORTL_ADDR;
#endif


#endif /* PORT_ADDR_H_ */
