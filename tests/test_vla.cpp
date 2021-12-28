#define BOOST_TEST_MODULE test_vla
#include <boost/test/included/unit_test.hpp>

#include "structs/vla.h"

static vla_t vla;

BOOST_AUTO_TEST_CASE(test_vla_init) {
  int ret = vla_init(&vla, sizeof(int), 5);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 5);
  BOOST_TEST(vla.size == 0);
}

// Push 1..10
BOOST_AUTO_TEST_CASE(test_vla_push) {
  int ret;
  int vals[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (const auto val : vals) {
    ret = vla_push(&vla, (void *)&val);
    BOOST_TEST(ret == 0);
  }

  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 10);
}

// Pop 10
BOOST_AUTO_TEST_CASE(test_vla_pop) {
  int val;
  int ret = vla_pop(&vla, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 10);
  BOOST_TEST(vla.size == 9);
  BOOST_TEST(val == 10);
}

// Enqueue 2..3
BOOST_AUTO_TEST_CASE(test_vla_enq) {
  int vals[2] = {2, 3};
  int ret;
  
  for (const auto val : vals) {
    ret = vla_enq(&vla, (void *)&vals);
    BOOST_TEST(ret == 0);
  }

  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
  BOOST_TEST(vla.size == 11);
}

// Get element 1 (8)
BOOST_AUTO_TEST_CASE(test_vla_get) {
  int val;
  int ret = vla_get(&vla, 1, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
  BOOST_TEST(vla.size == 11);
  BOOST_TEST(val == 8);
}

// Get pointer to element 0 (9)
BOOST_AUTO_TEST_CASE(test_vla_getp) {
  int *val;
  int ret = vla_getp(&vla, 0, (void **)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
  BOOST_TEST(vla.size == 11);
  BOOST_TEST(*val == 9);
}

// Set element 0 to 3
BOOST_AUTO_TEST_CASE(test_vla_set) {
  int val = 3;
  int ret = vla_set(&vla, 0, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
  BOOST_TEST(vla.size == 11);
}

// Insert 2 at index 2
BOOST_AUTO_TEST_CASE(test_vla_ins) {
  int val = 2;
  int ret = vla_ins(&vla, 2, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
  BOOST_TEST(vla.size == 12);
}

// Delete element 0 (3)
BOOST_AUTO_TEST_CASE(test_vla_del) {
  int ret = vla_del(&vla, 0);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
  BOOST_TEST(vla.size == 11);
}

BOOST_AUTO_TEST_CASE(test_vla_clear) {
  int ret = vla_clear(&vla);

  BOOST_TEST(ret == 0);
  BOOST_TEST(vla.elements);
  BOOST_TEST(vla.element_size == sizeof(int));
  BOOST_TEST(vla.capacity == 20);
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
