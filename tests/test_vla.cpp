#define BOOST_TEST_MODULE test_vla
#include <boost/test/included/unit_test.hpp>

#include "test_vla.hpp"

/*! \brief Invalid VLA initialization
 *  \details Ensures VLA construction function returns
 *           error upon receiving invalid arguments.
 */
BOOST_AUTO_TEST_SUITE(invalid_init)

BOOST_AUTO_TEST_CASE(null_pointer) {
  vla_t *v = NULL;

  BOOST_TEST(vla_init(v, sizeof(int), 10) == ERR_NULL);
}

BOOST_AUTO_TEST_CASE(invalid_size) {
  vla_t v;

  BOOST_TEST(vla_init(&v, 0, 10) == ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_CASE(invalid_capacity) {
  vla_t v;

  BOOST_TEST(vla_init(&v, sizeof(int), 0) == ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \brief Operations on empty VLA
 *  \details Performs a series of operations on
 *           an empty VLA, which may or may not
 *           result in error.
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

BOOST_AUTO_TEST_CASE(empty_del) { BOOST_TEST(vla_del(&vla, 0) == ERR_INDEX_OUT_OF_BOUNDS); }

BOOST_AUTO_TEST_CASE(empty_clear) { BOOST_TEST(vla_clear(&vla) == ERR_NONE); }

BOOST_AUTO_TEST_SUITE_END()

/*! \brief VLA addition operations
 *  \details Examples of standard operations that
 *           add elements to the VLA.
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
    BOOST_TEST(vla_push(&vla, (const void *)&values[i]) == ERR_NONE);
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

/*! \brief VLA subtraction operations
 *  \details Examples of standard operations that
 *           remove elements from the VLA.
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
    BOOST_TEST(vla_del(&vla, i) == ERR_NONE);
    BOOST_TEST(vla_size(&vla) == 4 - i);
  }
}

BOOST_FIXTURE_TEST_CASE(clear_five_elements, vla_populated_fixture) {
  BOOST_TEST(vla_clear(&vla) == ERR_NONE);
  BOOST_TEST(vla_size(&vla) == 0);
}

BOOST_AUTO_TEST_SUITE_END()
