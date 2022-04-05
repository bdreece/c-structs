/*! \file       test_ringbuf.cpp
 *  \brief      Circular buffer data structure testing suite
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       01/01/2022
 */

#define BOOST_TEST_MODULE test_ringbuf

#include <string.h>

#include <boost/test/included/unit_test.hpp>

extern "C" {
#define restrict    /** nothing **/
#define STRUCTS_DEF /** nothing **/
#include "structs/error.h"
#include "structs/ringbuf.h"
}

struct ringbuf_empty_fixture {
    ringbuf_empty_fixture() {
        ringbuf = ringbuf_init(sizeof(int), 5);
        BOOST_TEST(ringbuf.elements);
        BOOST_TEST(ringbuf.head == 0);
        BOOST_TEST(ringbuf.tail == 0);
        BOOST_TEST(ringbuf.length == 0);
        BOOST_TEST(ringbuf.size == sizeof(int));
        BOOST_TEST(ringbuf.capacity == 5);
    }

    ~ringbuf_empty_fixture() {
        BOOST_TEST_REQUIRE(ringbuf_deinit(&ringbuf) == ERR_NONE);
    }

    ringbuf_t ringbuf;
};

struct ringbuf_populated_fixture {
    ringbuf_populated_fixture() {
        ringbuf = ringbuf_init(sizeof(int), 5);
        for (int i = 0; i < 5; i++) {
            BOOST_TEST_REQUIRE(memcpy((int *)ringbuf.elements + i,
                                      (const void *)&i,
                                      sizeof(int)) != (void *)NULL);
        }

        ringbuf.size = 5;
    }

    ~ringbuf_populated_fixture() {
        BOOST_TEST_REQUIRE(ringbuf_deinit(&ringbuf) == ERR_NONE);
    }

    ringbuf_t ringbuf;
};

/*! \test       test_ringbuf/empty_ops
 *  \brief      Circular buffer empty operations test suite
 *  \details    Asserts proper behavior in error throwing upon
 *              reads from empty circular buffer
 */
BOOST_FIXTURE_TEST_SUITE(empty_ops, ringbuf_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_read) {
    int value;

    BOOST_TEST(ringbuf_read(&ringbuf, (void *)&value) == ERR_EMPTY);
}

BOOST_AUTO_TEST_CASE(empty_get) {
    int value;

    BOOST_TEST(ringbuf_get(&ringbuf, (void *)&value) == ERR_EMPTY);
}

BOOST_AUTO_TEST_CASE(empty_getp) {
    int *value;

    BOOST_TEST(ringbuf_getp(&ringbuf, (void **)&value) == ERR_EMPTY);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_ringbuf/addition_ops
 *  \brief      Circular buffer addition operations testing suite
 *  \details    Asserts proper behavior in execution of write
 *              operations.
 */
BOOST_AUTO_TEST_SUITE(addition_ops)

BOOST_FIXTURE_TEST_CASE(write_five_elements, ringbuf_empty_fixture) {
    const int values[5] = {1, 2, 3, 4, 5};

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(ringbuf_write(&ringbuf, (const void *)&values[i]) ==
                   ERR_NONE);
        BOOST_TEST(*((int *)ringbuf.elements + i) == i + 1);
        BOOST_TEST(ringbuf.size == i + 1);
    }

    BOOST_TEST(ringbuf.head == 0);
    BOOST_TEST(ringbuf.tail == 0);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_ringbuf/subtraction_ops
 *  \brief      Circular buffer subtraction operations testing suite
 *  \details    Asserts proper behavior in execution of read, clear,
 *              and get operations.
 */
BOOST_AUTO_TEST_SUITE(subtraction_ops)

BOOST_FIXTURE_TEST_CASE(read_five_elements, ringbuf_populated_fixture) {
    int values[5];

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(ringbuf_read(&ringbuf, (void *)&values[i]) == ERR_NONE);
        BOOST_TEST(values[i] == i);
    }

    BOOST_TEST(ringbuf.head == 0);
    BOOST_TEST(ringbuf.tail == 0);
    BOOST_TEST(ringbuf.size == 0);
}

BOOST_FIXTURE_TEST_CASE(get_five_elements, ringbuf_populated_fixture) {
    int values[5];

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(ringbuf_get(&ringbuf, (void *)&values[i]) == ERR_NONE);
        BOOST_TEST(values[i] == 0);
    }

    BOOST_TEST(ringbuf.head == 0);
    BOOST_TEST(ringbuf.tail == 0);
    BOOST_TEST(ringbuf.size == 5);
}

BOOST_FIXTURE_TEST_CASE(getp_five_elements, ringbuf_populated_fixture) {
    int *values[5];

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(ringbuf_getp(&ringbuf, (void **)&values[i]) == ERR_NONE);
        BOOST_TEST(*values[i] == 0);
    }

    BOOST_TEST(ringbuf.head == 0);
    BOOST_TEST(ringbuf.tail == 0);
    BOOST_TEST(ringbuf.size == 5);
}

BOOST_FIXTURE_TEST_CASE(clear_five_elements, ringbuf_populated_fixture) {
    BOOST_TEST(ringbuf_clear(&ringbuf) == ERR_NONE);
    BOOST_TEST(ringbuf.head == 0);
    BOOST_TEST(ringbuf.tail == 0);
    BOOST_TEST(ringbuf.size == 0);
}

BOOST_AUTO_TEST_SUITE_END()
