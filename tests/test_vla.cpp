/*! \file       test_vla.cpp
 *  \brief      Variable-length array data structure testing suite
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       01/01/2022
 */

#define BOOST_TEST_MODULE test_vla
#include <boost/test/included/unit_test.hpp>

extern "C" {
#define restrict __restrict__
#define STRUCTS_DEF /** nothing **/
#include "structs/error.h"
#include "structs/vla.h"
}

/*! \brief      BOOST.Test VLA Empty Fixture
 *  \details    Fixture object orchestrates construction
 *              and destruction of empty VLAs.
 */
struct vla_empty_fixture {
  vla_empty_fixture() {
    BOOST_TEST_REQUIRE(vla_init(&vla, sizeof(int), 10) == ERR_NONE);
    BOOST_TEST(vla.elements);
    BOOST_TEST(vla.element_size == sizeof(int));
    BOOST_TEST(vla.size == 0);
    BOOST_TEST(vla.capacity == 10);
  }

  ~vla_empty_fixture() {
    BOOST_TEST_REQUIRE(vla_deinit(&vla) == ERR_NONE);
    BOOST_TEST(!vla.elements);
    BOOST_TEST(vla.element_size == 0);
    BOOST_TEST(vla.size == 0);
    BOOST_TEST(vla.capacity == 0);
  }

  vla_t vla;
};

struct vla_populated_fixture {
  vla_populated_fixture() {
    int vals[5] = {1, 2, 3, 4, 5};
    BOOST_TEST_REQUIRE(vla_init(&vla, sizeof(int), 10) == ERR_NONE);
    for (long i = 0; i < 5; i++)
      BOOST_TEST(vla_enq(&vla, (const void *)&vals[i]) == ERR_NONE);
  }

  ~vla_populated_fixture() { BOOST_TEST_REQUIRE(vla_deinit(&vla) == ERR_NONE); }

  vla_t vla;
};

BOOST_AUTO_TEST_SUITE(invalid_init)

/*! \test       test_vla/invalid_init/null_pointer
 *  \brief      VLA null pointer argument
 *  \details    Ensures VLA construction function returns
 *              error upon receiving invalid VLA argument.
 */
BOOST_AUTO_TEST_CASE(null_pointer) {
  vla_t *v = NULL;

  BOOST_TEST(vla_init(v, sizeof(int), 10) == ERR_NULL);
}

/*! \test       test_vla/invalid_init/invalid_size
 *  \brief      VLA invalid size argument
 *  \details    Ensures VLA construction function returns
 *              error upon receiving invalid size argument.
 */
BOOST_AUTO_TEST_CASE(invalid_size) {
  vla_t v;

  BOOST_TEST(vla_init(&v, 0, 10) == ERR_INVALID_ARGUMENT);
}

/*! \test       test_vla/invalid_init/invalid_capacity
 *  \brief      VLA invalid capacity argument
 *  \details    Ensures VLA construction function returns
 *              error upon receiving invalid capacity argument.
 */
BOOST_AUTO_TEST_CASE(invalid_capacity) {
  vla_t v;

  BOOST_TEST(vla_init(&v, sizeof(int), 0) == ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_vla/empty_ops
 *  \brief      Operations on empty VLA
 *  \details    Performs a series of operations on
 *              an empty VLA, which may or may not
 *              result in error.
 */
BOOST_FIXTURE_TEST_SUITE(empty_ops, vla_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_pop) {
  int element;

  BOOST_TEST(vla_pop(&vla, (void *)&element) == ERR_EMPTY);
}

BOOST_AUTO_TEST_CASE(empty_get) {
  int element;

  BOOST_TEST(vla_get(&vla, 0, (void *)&element) == ERR_INDEX_OUT_OF_BOUNDS);
}

BOOST_AUTO_TEST_CASE(empty_getp) {
  int *element;

  BOOST_TEST(vla_getp(&vla, 0, (void **)&element) == ERR_INDEX_OUT_OF_BOUNDS);
}

BOOST_AUTO_TEST_CASE(empty_del) {
  BOOST_TEST(vla_del(&vla, 0) == ERR_INDEX_OUT_OF_BOUNDS);
}

BOOST_AUTO_TEST_CASE(empty_clear) { BOOST_TEST(vla_clear(&vla) == ERR_NONE); }

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_vla/addition_ops
 *  \brief      VLA addition operations
 *  \details    Examples of standard operations that
 *              add elements to the VLA.
 */
BOOST_AUTO_TEST_SUITE(addition_ops)

BOOST_FIXTURE_TEST_CASE(push_five_elements, vla_empty_fixture) {
  int values[5] = {0, 1, 2, 3, 4};

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_push(&vla, (const void *)&values[i]) == ERR_NONE);
    BOOST_TEST(*(int *)vla.elements == values[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(enq_five_elements, vla_empty_fixture) {
  int values[5] = {0, 1, 2, 3, 4};

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_enq(&vla, (const void *)&values[i]) == ERR_NONE);
    BOOST_TEST(*((int *)vla.elements + i) == values[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(set_five_elements, vla_empty_fixture) {
  int values[5] = {0, 1, 2, 3, 4};

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_set(&vla, i, (const void *)&values[i]) == ERR_NONE);
    BOOST_TEST(*((int *)vla.elements + i) == values[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(ins_five_elements, vla_empty_fixture) {
  int values[5] = {0, 1, 2, 3, 4};

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_ins(&vla, 0, (const void *)&values[i]) == ERR_NONE);
    BOOST_TEST(*((int *)vla.elements) == values[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_vla/subtraction_ops
 *  \brief      VLA subtraction operations
 *  \details    Examples of standard operations that
 *              remove elements from the VLA.
 */
BOOST_AUTO_TEST_SUITE(subtraction_ops)

BOOST_FIXTURE_TEST_CASE(pop_five_elements, vla_populated_fixture) {
  int values[5];

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_pop(&vla, (void *)&values[i]) == ERR_NONE);
    BOOST_TEST(values[i] == i + 1);
  }

  BOOST_TEST(vla_size(&vla) == 0);
}

BOOST_FIXTURE_TEST_CASE(get_five_elements, vla_populated_fixture) {
  int values[5];
  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_get(&vla, i, (void *)&values[i]) == ERR_NONE);
    BOOST_TEST(values[i] == i + 1);
  }

  BOOST_TEST(vla_size(&vla) == 5);
}

BOOST_FIXTURE_TEST_CASE(getp_five_elements, vla_populated_fixture) {
  int *values[5];

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_getp(&vla, i, (void **)&values[i]) == ERR_NONE);
    BOOST_TEST(*values[i] == i + 1);
  }

  BOOST_TEST(vla_size(&vla) == 5);
}

BOOST_FIXTURE_TEST_CASE(del_five_elements, vla_populated_fixture) {
  for (long i = 0; i < 5; i++) {
    BOOST_TEST(vla_del(&vla, 0) == ERR_NONE);
    BOOST_TEST(vla_size(&vla) == 4 - i);
  }
}

BOOST_FIXTURE_TEST_CASE(clear_five_elements, vla_populated_fixture) {
  BOOST_TEST(vla_clear(&vla) == ERR_NONE);
  BOOST_TEST(vla_size(&vla) == 0);
}

BOOST_AUTO_TEST_SUITE_END()
