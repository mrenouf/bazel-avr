#include "buffer/ring_buffer_u16.h"

// create a 64-element ringbuffer for unsigned 16bit integers
RB_DECL_U16_7(rb);

int main() {

  while (rb_size_u16(&rb) < rb_capacity_u16(&rb)) {
    rb_add_u16(&rb, 1);
  }
  while (rb_size_u16(&rb) > 0) {
    rb_remove_u16(&rb);
  }
  return 0;
}


