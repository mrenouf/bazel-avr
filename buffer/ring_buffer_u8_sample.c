#include "buffer/ring_buffer_u8.h"

RB_DECL_U8_15(rb);

int main() {
  while (rb_size_u8(&rb) < 15) {
    rb_add_u8(&rb, 1);
  }
  while (rb_size_u8(&rb) > 0) {
    rb_remove_u8(&rb);
  }
  return 0;
}


