/** \file       test_map.hpp
 *  \brief      Map data structure testing suite fixtures
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       01/01/2022
 */

#include <boost/test/included/unit_test.hpp>

#include "structs/error.h"
#include "structs/map.h"
#include "util.hpp"

struct umap_empty_fixture {
  umap_empty_fixture() {
    BOOST_TEST_REQUIRE(
        map_init(&map, sizeof(char), sizeof(int), false, cmp, 10) == ERR_NONE);
    BOOST_TEST(map.vla.elements);
    BOOST_TEST(map.key_size == sizeof(char));
    BOOST_TEST(map.val_size == sizeof(int));
    BOOST_TEST(map.cmp == cmp);
  }

  ~umap_empty_fixture() { BOOST_TEST_REQUIRE(map_deinit(&map) == ERR_NONE); }

  map_t map;
};

struct omap_empty_fixture {
  omap_empty_fixture() {
    BOOST_TEST_REQUIRE(
        map_init(&map, sizeof(char), sizeof(int), true, cmp, 10) == ERR_NONE);
    BOOST_TEST(map.vla.elements);
    BOOST_TEST(map.key_size == sizeof(char));
    BOOST_TEST(map.val_size == sizeof(int));
    BOOST_TEST(map.cmp == cmp);
  }

  ~omap_empty_fixture() { BOOST_TEST_REQUIRE(map_deinit(&map) == ERR_NONE); }

  map_t map;
};

struct umap_populated_fixture {
  umap_populated_fixture() {
    BOOST_TEST_REQUIRE(
        map_init(&map, sizeof(char), sizeof(int), false, cmp, 10) == ERR_NONE);

    for (int i = 0; i < 5; i++) {
      BOOST_TEST_REQUIRE(map_set(&map, (const void *)&keys[i],
                                 (const void *)&vals[i]) == ERR_NONE);
    }
  }

  ~umap_populated_fixture() {
    BOOST_TEST_REQUIRE(map_deinit(&map) == ERR_NONE);
  }

  char keys[5] = {'a', 'b', 'c', 'd', 'e'};
  int vals[5] = {1, 2, 3, 4, 5};
  map_t map;
};

struct omap_populated_fixture {
  omap_populated_fixture() {
    BOOST_TEST_REQUIRE(
        map_init(&map, sizeof(char), sizeof(int), true, cmp, 10) == ERR_NONE);

    for (int i = 0; i < 5; i++) {
      BOOST_TEST_REQUIRE(map_set(&map, (const void *)&keys[i],
                                 (const void *)&vals[i]) == ERR_NONE);
    }
  }

  ~omap_populated_fixture() {
    BOOST_TEST_REQUIRE(map_deinit(&map) == ERR_NONE);
  }

  char keys[5] = {'a', 'b', 'c', 'd', 'e'};
  int vals[5] = {1, 2, 3, 4, 5};
  map_t map;
};
