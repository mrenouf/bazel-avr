#include <avr/io.h>
#include <util/delay.h>
#include "common/port_macros.h"

#define LED B,1

int main() {
  OUTPUT(LED);
  for(;;) {
    TOGGLE(LED);
    _delay_ms(1000);
  }
}
