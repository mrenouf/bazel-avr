#include <stdio.h>
#include "buffer/byte_buffer.h"

#include "testing/unity/unity_2_4_1/src/unity.h"
#include "testing/unity/unity_2_4_1/extras/fixture/src/unity_fixture.h"

static byte_buffer_t *b;

void setUp() {
  b = byte_buffer_create(32);
}

void test_byte_buffer_position() {
  TEST_ASSERT_EQUAL(0, byte_buffer_position(b));
  
  byte_buffer_put(b, 1);
  byte_buffer_put(b, 2);
  byte_buffer_put(b, 3);
  byte_buffer_put(b, 4);

  TEST_ASSERT_EQUAL(4, byte_buffer_position(b));
}

void test_byte_buffer_remaining() {
  TEST_ASSERT_EQUAL(32, byte_buffer_remaining(b));

  byte_buffer_put(b, 1);
  byte_buffer_put(b, 2);
  byte_buffer_put(b, 3);
  byte_buffer_put(b, 4);

  TEST_ASSERT_EQUAL(32 - 4, byte_buffer_remaining(b));
}

void test_byte_buffer_flip() {
  byte_buffer_put(b, 1);
  byte_buffer_put(b, 2);
  byte_buffer_put(b, 3);
  byte_buffer_put(b, 4);

  byte_buffer_flip(b);

  TEST_ASSERT_EQUAL(4, byte_buffer_remaining(b));
}

void test_byte_buffer_get() {
  byte_buffer_put(b, 1);
  byte_buffer_put(b, 2);
  byte_buffer_put(b, 3);
  byte_buffer_put(b, 4);

  byte_buffer_reset(b);

  TEST_ASSERT_EQUAL(1, byte_buffer_get(b));
  TEST_ASSERT_EQUAL(2, byte_buffer_get(b));
  TEST_ASSERT_EQUAL(3, byte_buffer_get(b));
  TEST_ASSERT_EQUAL(4, byte_buffer_get(b));
}

void test_byte_buffer_limit() {
  byte_buffer_limit(b, 8);

  byte_buffer_put(b, 1);
  byte_buffer_put(b, 2);
  byte_buffer_put(b, 3);
  byte_buffer_put(b, 4);

  TEST_ASSERT_EQUAL(4, byte_buffer_remaining(b));
}

void tearDown() {
  byte_buffer_destroy(b);
  b = NULL;
}

void oldmain() {
  while (byte_buffer_remaining(b) > 0) {
    printf("byte_buffer_get: %i\n", byte_buffer_get(b));
  }
  byte_buffer_get(b);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_byte_buffer_position);
  RUN_TEST(test_byte_buffer_remaining);
  RUN_TEST(test_byte_buffer_flip);
  RUN_TEST(test_byte_buffer_get);
  RUN_TEST(test_byte_buffer_limit);
  return UNITY_END();
}

