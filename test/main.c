#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

const char hello_message_flash[] PROGMEM = "This is a string held completely in flash (data).";
const char hello_message_eeprom[] EEMEM = "This is a string held completely in ROM (eeprom).";
const char hello_message_ram[] = "This is a string loaded into RAM (code).";

int main (void) {

   DDRB |= (1 << PB5);

   while(1) {
       PORTB ^= (1 << PB5);
       _delay_ms(500);
   }

   return 0;
}
