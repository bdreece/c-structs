#define BOOST_TEST_MODULE VLA
#include <boost/test/included/unit_test.hpp>

#include "structs/vla.h"

BOOST_AUTO_TEST_CASE(test_vla_init) {
  vla_t vla;

  int ret = vla_init(&vla, sizeof(int), 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 0);

  vla_deinit(&vla);
}
