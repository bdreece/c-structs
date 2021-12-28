#define BOOST_TEST_MODULE test_cbuf
#include <boost/test/included/unit_test.hpp>

#include "structs/cbuf.h"

static cbuf_t cbuf;

BOOST_AUTO_TEST_CASE(test_cbuf_init) {
  int ret = cbuf_init(&cbuf, sizeof(int), 5);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 5);
};

// Write 9 integers
BOOST_AUTO_TEST_CASE(test_cbuf_write) {
  int ret, vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (int i = 0; i < 9; i++) {
    ret = cbuf_write(&cbuf, (void *)&vals[i]);
    BOOST_TEST(ret == 0);
    BOOST_TEST(cbuf.tail == (i + 1) % 5);
  }

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.size == 5);
}

// Read 3 integers
BOOST_AUTO_TEST_CASE(test_cbuf_read) {
  int ret, vals[3];
  for (int i = 0; i < 3; i++) {
    ret = cbuf_read(&cbuf, (void *)&vals[i]);
    BOOST_TEST(ret == 0);
    BOOST_TEST(vals[i] == i + 6);
    BOOST_TEST(cbuf.head == i + 1);
  }
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.size == 5);

  BOOST_TEST(cbuf.tail == 4);
}

BOOST_AUTO_TEST_CASE(test_cbuf_clear) {
  int ret = cbuf_clear(&cbuf);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.size == 5);

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
}

BOOST_AUTO_TEST_CASE(test_cbuf_deinit) {
  int ret = cbuf_deinit(&cbuf);

  BOOST_TEST(ret == 0);
  BOOST_TEST(!cbuf.elements);
  BOOST_TEST(cbuf.element_size == 0);
  BOOST_TEST(cbuf.size == 0);

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
}
