#include <stdio.h>
#include "buffer/ring_buffer_u8.h"

#include "testing/unity/unity_2_4_1/src/unity.h"

RB_DECL_U8_63(rb);

void setUp() {
  rb_clear_u8(&rb);
}

void test_capacity() {
  TEST_ASSERT_EQUAL(63, rb_capacity_u8(&rb));
}

void test_size() {
  TEST_ASSERT_EQUAL(0, rb_size_u8(&rb));
}

void test_add_remove() {
  rb_add_u8(&rb, 1);
  rb_add_u8(&rb, 2);
  TEST_ASSERT_EQUAL(1, rb_remove_u8(&rb));
  rb_add_u8(&rb, 3);
  rb_add_u8(&rb, 4);
  TEST_ASSERT_EQUAL(2, rb_remove_u8(&rb));
  TEST_ASSERT_EQUAL(3, rb_remove_u8(&rb));
}

void test_wraparound() {
  int i;
  // fill with 1's
  while (rb_size_u8(&rb) < 63) {
    rb_add_u8(&rb, 1);
  }

  // add an arbitrary number more so head is now < tail
  rb_add_u8(&rb, 1);
  rb_add_u8(&rb, 1);
  rb_add_u8(&rb, 1);
  TEST_ASSERT(rb.head < rb.tail);

  TEST_ASSERT_EQUAL(63, rb_size_u8(&rb));

  // Add 100 at head
  // size should still equal capacity (tail item removed)
  rb_add_u8(&rb, 100);
  TEST_ASSERT_EQUAL(63, rb_size_u8(&rb));

  // Remove all items up to (n-1)
  for (i = 0; i < 62; i++) {
    TEST_ASSERT_EQUAL(1, rb_remove_u8(&rb));
  }

  // Last should be 100
  TEST_ASSERT_EQUAL(100, rb_remove_u8(&rb));
}

void test_peek() {
  rb_add_u8(&rb, 1);
  rb_add_u8(&rb, 2);
  TEST_ASSERT_EQUAL(2, rb_size_u8(&rb));
  TEST_ASSERT_EQUAL(1, rb_peek_u8(&rb));
  TEST_ASSERT_EQUAL(1, rb_remove_u8(&rb));
  TEST_ASSERT_EQUAL(2, rb_peek_u8(&rb));
  TEST_ASSERT_EQUAL(2, rb_remove_u8(&rb));
  TEST_ASSERT_EQUAL(0, rb_peek_u8(&rb));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_capacity);
  RUN_TEST(test_size);
  RUN_TEST(test_add_remove);
  RUN_TEST(test_peek);
  RUN_TEST(test_wraparound);
  return UNITY_END();
}

