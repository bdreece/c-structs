#define BOOST_TEST_MODULE CBUF
#include <boost/test/included/unit_test.hpp>

#include "structs/cbuf.h"

BOOST_AUTO_TEST_CASE(test_cbuf_init) {
  cbuf_t cbuf;

  int ret = cbuf_init(&cbuf, sizeof(int), 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(cbuf.elements);
  BOOST_TEST(cbuf.element_size == sizeof(int));
  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 10);

  cbuf_deinit(&cbuf);
};
