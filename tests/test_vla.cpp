#define BOOST_TEST_MODULE test_vla
#include <boost/test/included/unit_test.hpp>

#include "structs/vla.h"

static vla_t vla;

BOOST_AUTO_TEST_CASE(test_vla_init) {
  int ret = vla_init(&vla, sizeof(int), 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 0);
}

BOOST_AUTO_TEST_CASE(test_vla_push) {
  int val = 1;
  int ret = vla_push(&vla, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 1);
}

BOOST_AUTO_TEST_CASE(test_vla_pop) {
  int val;
  int ret = vla_pop(&vla, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 0);
  BOOST_TEST(val == 1);
}

BOOST_AUTO_TEST_CASE(test_vla_enq) {
  int val = 2;
  int ret = vla_enq(&vla, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 1);
}

BOOST_AUTO_TEST_CASE(test_vla_get) {
  int val;
  int ret = vla_get(&vla, 0, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 1);
  BOOST_TEST(val == 2);
}

BOOST_AUTO_TEST_CASE(test_vla_getp) {
  int *val;
  int ret = vla_getp(&vla, 0, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 1);
  BOOST_TEST(*val == 2);
}

BOOST_AUTO_TEST_CASE(test_vla_set) {
  int val = 3;
  int ret = vla_set(&vla, 0, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 1);
}

BOOST_AUTO_TEST_CASE(test_vla_ins) {
  int val = 2;
  int ret = vla_ins(&vla, 0, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 2);
}

BOOST_AUTO_TEST_CASE(test_vla_del) {
  int ret = vla_del(&vla, 0);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 1);
}

BOOST_AUTO_TEST_CASE(test_vla_clear) {
  int ret = vla_clear(&vla);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 0);
}

BOOST_AUTO_TEST_CASE(test_vla_deinit) {
  int ret = vla_deinit(&vla);

  BOOST_TEST(ret == 0);
  BOOST_TEST(!vla.elements);
  BOOST_TEST(vla.element_size == 0);
  BOOST_TEST(vla.capacity == 0);
  BOOST_TEST(vla.size == 0);
}
