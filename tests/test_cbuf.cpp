#define BOOST_TEST_MODULE test_cbuf
#include <boost/test/included/unit_test.hpp>

#include "structs/cbuf.h"

static cbuf_t cbuf;

BOOST_AUTO_TEST_CASE(test_cbuf_init) {
  int ret = cbuf_init(&cbuf, sizeof(int), 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 10);
};

BOOST_AUTO_TEST_CASE(test_cbuf_write) {
  int val = 1;
  int ret = cbuf_write(&cbuf, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.size == 10);

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 1);
}

BOOST_AUTO_TEST_CASE(test_cbuf_read) {
  int val;
  int ret = cbuf_read(&cbuf, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.size == 10);

  BOOST_TEST(cbuf.head == 1);
  BOOST_TEST(cbuf.tail == 1);
  BOOST_TEST(val == 1);
}

BOOST_AUTO_TEST_CASE(test_cbuf_clear) {
  int ret = cbuf_clear(&cbuf);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.size == 10);

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
