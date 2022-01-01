#define BOOST_TEST_MODULE test_cbuf
#include "test_cbuf.hpp"

/*! \brief      Circular buffer invalid initialization test suite
 *  \details    Asserts proper behavior in error throwing upon
 *              invalid initializations
 */
BOOST_AUTO_TEST_SUITE(invalid_init)

BOOST_AUTO_TEST_CASE(null_pointer) {
  cbuf_t *cbuf = NULL;

  BOOST_TEST(cbuf_init(cbuf, sizeof(int), 10) == ERR_NULL);
}

BOOST_AUTO_TEST_CASE(empty_element_size) {
  cbuf_t cbuf;

  BOOST_TEST(cbuf_init(&cbuf, 0, 10) == ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_CASE(empty_size) {
  cbuf_t cbuf;

  BOOST_TEST(cbuf_init(&cbuf, sizeof(int), 0) == ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \brief      Circular buffer empty operations test suite
 *  \details    Asserts proper behavior in error throwing upon
 *              reads from empty circular buffer
 */
BOOST_FIXTURE_TEST_SUITE(empty_ops, cbuf_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_read) {
  int value;

  BOOST_TEST(cbuf_read(&cbuf, (void *)&value) == ERR_EMPTY);
}

BOOST_AUTO_TEST_CASE(empty_get) {
  int value;

  BOOST_TEST(cbuf_get(&cbuf, (void *)&value) == ERR_EMPTY);
}

BOOST_AUTO_TEST_CASE(empty_getp) {
  int *value;

  BOOST_TEST(cbuf_getp(&cbuf, (void **)&value) == ERR_EMPTY);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \brief      Circular buffer addition operations testing suite
 *  \details    Asserts proper behavior in execution of write
 *              operations.
 */
BOOST_AUTO_TEST_SUITE(addition_ops)

BOOST_FIXTURE_TEST_CASE(write_five_elements, cbuf_empty_fixture) {
  const int values[5] = {1, 2, 3, 4, 5};

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(cbuf_write(&cbuf, (const void *)&values[i]) == ERR_NONE);
    BOOST_TEST(*((int *)cbuf.elements + i) == i + 1);
    BOOST_TEST(cbuf.size == i + 1);
  }

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \brief      Circular buffer subtraction operations testing suite
 *  \details    Asserts proper behavior in execution of read, clear,
 *              and get operations.
 */
BOOST_AUTO_TEST_SUITE(subtraction_ops)

BOOST_FIXTURE_TEST_CASE(read_five_elements, cbuf_populated_fixture) {
  int values[5];

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(cbuf_read(&cbuf, (void *)&values[i]) == ERR_NONE);
    BOOST_TEST(values[i] == i + 1);
  }

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 0);
}

BOOST_FIXTURE_TEST_CASE(get_five_elements, cbuf_populated_fixture) {
  int values[5];

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(cbuf_get(&cbuf, (void *)&values[i]) == ERR_NONE);
    BOOST_TEST(values[i] == 1);
  }

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 5);
}

BOOST_FIXTURE_TEST_CASE(getp_five_elements, cbuf_populated_fixture) {
  int *values[5];

  for (long i = 0; i < 5; i++) {
    BOOST_TEST(cbuf_getp(&cbuf, (void **)&values[i]) == ERR_NONE);
    BOOST_TEST(*values[i] == 1);
  }

  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 5);
}

BOOST_FIXTURE_TEST_CASE(clear_five_elements, cbuf_populated_fixture) {
  BOOST_TEST(cbuf_clear(&cbuf) == ERR_NONE);
  BOOST_TEST(cbuf.head == 0);
  BOOST_TEST(cbuf.tail == 0);
  BOOST_TEST(cbuf.size == 0);
}

BOOST_AUTO_TEST_SUITE_END()
