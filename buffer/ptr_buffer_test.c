#include <stdio.h>
#include "buffer/ptr_buffer.h"

#include "testing/unity/unity_2_4_1/src/unity.h"
#include "testing/unity/unity_2_4_1/extras/fixture/src/unity_fixture.h"

static ptr_buffer_t *b;

 char *test1 = "This is a string.";
 char *test2 = "Here is another.";
 char *test3 = "Yet another string.";
 char *test4 = "And still more strings.";

void setUp() {
  b = ptr_buffer_create(32);
}

void test_ptr_buffer_position() {
  TEST_ASSERT_EQUAL(0, ptr_buffer_position(b));
  
  ptr_buffer_put(b, test1);
  ptr_buffer_put(b, test2);
  ptr_buffer_put(b, test3);
  ptr_buffer_put(b, test4);

  TEST_ASSERT_EQUAL(4, ptr_buffer_position(b));
}

void test_ptr_buffer_remaining() {
  TEST_ASSERT_EQUAL(32, ptr_buffer_remaining(b));

  ptr_buffer_put(b, test1);
  ptr_buffer_put(b, test2);
  ptr_buffer_put(b, test3);
  ptr_buffer_put(b, test4);

  TEST_ASSERT_EQUAL(32 - 4, ptr_buffer_remaining(b));
}

void test_ptr_buffer_flip() {
  ptr_buffer_put(b, test1);
  ptr_buffer_put(b, test2);
  ptr_buffer_put(b, test3);
  ptr_buffer_put(b, test4);

  ptr_buffer_flip(b);

  TEST_ASSERT_EQUAL(4, ptr_buffer_remaining(b));
}

void test_ptr_buffer_get() {
  ptr_buffer_put(b, test1);
  ptr_buffer_put(b, test2);
  ptr_buffer_put(b, test3);
  ptr_buffer_put(b, test4);

  ptr_buffer_reset(b);

  TEST_ASSERT_EQUAL_STRING(test1, (char *) ptr_buffer_get(b));
  TEST_ASSERT_EQUAL_STRING(test2, (char *) ptr_buffer_get(b));
  TEST_ASSERT_EQUAL_STRING(test3, (char *) ptr_buffer_get(b));
  TEST_ASSERT_EQUAL_STRING(test4, (char *) ptr_buffer_get(b));
}

void test_ptr_buffer_limit() {
  ptr_buffer_limit(b, 8);

  ptr_buffer_put(b, test1);
  ptr_buffer_put(b, test2);
  ptr_buffer_put(b, test3);
  ptr_buffer_put(b, test4);

  TEST_ASSERT_EQUAL(4, ptr_buffer_remaining(b));
}

void tearDown() {
  ptr_buffer_destroy(b);
  b = NULL;
}

void oldmain() {
  while (ptr_buffer_remaining(b) > 0) {
    printf("ptr_buffer_get: %p\n", ptr_buffer_get(b));
  }
  ptr_buffer_get(b);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_ptr_buffer_position);
  RUN_TEST(test_ptr_buffer_remaining);
  RUN_TEST(test_ptr_buffer_flip);
  RUN_TEST(test_ptr_buffer_get);
  RUN_TEST(test_ptr_buffer_limit);
  return UNITY_END();
}
