/*! \file       test_vla.cpp
 *  \brief      Variable-length array data structure testing suite
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       01/01/2022
 */

#include <cstring>
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
        vla = vla_init(sizeof(int), 10);
        BOOST_TEST(vla.elements);
        BOOST_TEST(vla.size == sizeof(int));
        BOOST_TEST(vla.length == 0);
        BOOST_TEST(vla.capacity == 10);
    }

    ~vla_empty_fixture() {
        BOOST_TEST_REQUIRE(vla_deinit(&vla) == ERR_NONE);
        BOOST_TEST(!vla.elements);
        BOOST_TEST(vla.size == 0);
        BOOST_TEST(vla.length == 0);
        BOOST_TEST(vla.capacity == 0);
    }

    vla_t vla;
};

struct vla_populated_fixture {
    vla_populated_fixture() {
        int vals[5] = {1, 2, 3, 4, 5};
        vla = vla_init(sizeof(int), 10);
        for (int i = 0; i < 5; i++) {
            BOOST_TEST_REQUIRE(vla_enq(&vla, (void *)&vals[i]) == ERR_NONE);
        }
    }

    ~vla_populated_fixture() {
        BOOST_TEST_REQUIRE(vla_deinit(&vla) == ERR_NONE);
    }

    vla_t vla;
};

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

BOOST_AUTO_TEST_CASE(empty_extend) {
    vla_t other = vla_init(sizeof(int), 1);
    BOOST_TEST(vla_extend(&vla, &other) == ERR_NONE);
}

BOOST_AUTO_TEST_CASE(empty_shrink) {
    BOOST_TEST(vla_shrink(&vla) == ERR_EMPTY);
}

BOOST_AUTO_TEST_CASE(empty_trunc) {
    BOOST_TEST(vla_trunc(&vla, 0) == ERR_EMPTY);
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
        BOOST_TEST(vla_set(&vla, 0, (const void *)&values[i]) == ERR_NONE);
        BOOST_TEST(*(int *)vla.elements == values[i]);
    }
}

BOOST_FIXTURE_TEST_CASE(ins_five_elements, vla_empty_fixture) {
    int values[5] = {0, 1, 2, 3, 4};

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(vla_ins(&vla, 0, (const void *)&values[i]) == ERR_NONE);
        BOOST_TEST(*(int *)vla.elements == values[i]);
    }
}

BOOST_FIXTURE_TEST_CASE(extend_five_elements, vla_empty_fixture) {
    vla_t other = vla_init(sizeof(int), 5);
    for (int i = 0; i < 5; i++) {
        vla_enq(&other, (void *)&i);
    }

    BOOST_TEST(vla_extend(&vla, &other) == ERR_NONE);
    for (int i = 0; i < 5; i++) {
        BOOST_TEST(*(int *)vla.elements + i == i);
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
    int values[5] = {0, 0, 0, 0, 0};

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(vla_pop(&vla, (void *)&values[i]) == ERR_NONE);
        BOOST_TEST(values[i] == i + 1);
    }

    BOOST_TEST(vla_length(&vla) == 0);
}

BOOST_FIXTURE_TEST_CASE(get_five_elements, vla_populated_fixture) {
    int values[5];
    for (long i = 0; i < 5; i++) {
        BOOST_TEST(vla_get(&vla, i, (void *)&values[i]) == ERR_NONE);
        BOOST_TEST(values[i] == i + 1);
    }

    BOOST_TEST(vla_length(&vla) == 5);
}

BOOST_FIXTURE_TEST_CASE(getp_five_elements, vla_populated_fixture) {
    int *values[5];

    for (long i = 0; i < 5; i++) {
        BOOST_TEST(vla_getp(&vla, i, (void **)&values[i]) == ERR_NONE);
        BOOST_TEST(*values[i] == i + 1);
    }

    BOOST_TEST(vla_length(&vla) == 5);
}

BOOST_FIXTURE_TEST_CASE(del_five_elements, vla_populated_fixture) {
    for (long i = 0; i < 5; i++) {
        BOOST_TEST(vla_del(&vla, 0) == ERR_NONE);
        BOOST_TEST(vla_length(&vla) == 4 - i);
    }
}

BOOST_FIXTURE_TEST_CASE(clear_five_elements, vla_populated_fixture) {
    BOOST_TEST(vla_clear(&vla) == ERR_NONE);
    BOOST_TEST(vla_length(&vla) == 0);
}

BOOST_FIXTURE_TEST_CASE(shrink_five_elements, vla_populated_fixture) {
    BOOST_TEST(vla_shrink(&vla) == ERR_NONE);
    BOOST_TEST(vla_capacity(&vla) == 5);
    BOOST_TEST(vla_length(&vla) == 5);
}

BOOST_FIXTURE_TEST_CASE(trunc_five_elements, vla_populated_fixture) {
    int val = 6;
    vla_enq(&vla, (void *)&val);
    BOOST_TEST(vla_trunc(&vla, 5) == ERR_NONE);
    BOOST_TEST(vla_length(&vla) == 5);
    BOOST_TEST(vla_capacity(&vla) == 5);
}

BOOST_AUTO_TEST_SUITE_END()
