/*! \file       test_vla.hpp
 *  \brief      VLA test fixtures
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/29/2021
 */

#pragma once

#include <boost/test/included/unit_test.hpp>

#include "structs/error.h"

#define STRUCTS_VLA_IMPL
#include "structs/vla.h"

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
