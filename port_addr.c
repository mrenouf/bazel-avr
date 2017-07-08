/*
 * Defines runtime constants with MMIO register addresses for
 * ports. Use _SFR_IO8(PORTA_ADDR) instead of just PORTA. The
 * difference is PORTA_ADDRESS is a runtime value (uint8_t) which
 * can be stored and passed, not just compile-time constant.
 */

#define _SFR_ASM_COMPAT 1
#define __SFR_OFFSET 0
#include <avr/io.h>

#ifdef PORTA
const uint8_t PORTA_ADDR = PORTA;
#endif
#ifdef PORTB
const uint8_t PORTB_ADDR = PORTB;
#endif
#ifdef PORTC
const uint8_t PORTC_ADDR = PORTC;
#endif
#ifdef PORTD
const uint8_t PORTD_ADDR = PORTD;
#endif
#ifdef PORTE
const uint8_t PORTE_ADDR = PORTE;
#endif
#ifdef PORTF
const uint8_t PORTF_ADDR = PORTF;
#endif
#ifdef PORTG
const uint8_t PORTG_ADDR = PORTG;
#endif
#ifdef PORTH
const uint8_t PORTH_ADDR = PORTH;
#endif
#ifdef PORTI
const uint8_t PORTI_ADDR = PORTI;
#endif
#ifdef PORTJ
const uint8_t PORTJ_ADDR = PORTJ;
#endif
#ifdef PORTK
const uint8_t PORTK_ADDR = PORTK;
#endif
#ifdef PORTL
const uint8_t PORTL_ADDR = PORTL;
#endif

