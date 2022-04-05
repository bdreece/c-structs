/*! \file       test_map.cpp
 *  \brief      Map data structure testing suite
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       01/01/2022
 */

#include <cstddef>
#define BOOST_TEST_MODULE test_map
#include <boost/test/included/unit_test.hpp>

extern "C" {
#define restrict    /** nothing **/
#define STRUCTS_DEF /** nothing **/
#include "structs/error.h"
#include "structs/map.h"
}


int cmp(const void *a, const void *b) {
  if (*(char *)a < *(char *)b)
    return -1;
  else if (*(char *)a > *(char *)b)
    return 1;
  else
    return 0;
}

struct umap_empty_fixture {
  umap_empty_fixture() {
    map = map_init(sizeof(char), sizeof(int), false, cmp, 10);
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
    map = map_init(sizeof(char), sizeof(int), true, cmp, 10);
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
    map = map_init(sizeof(char), sizeof(int), false, cmp, 10);

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
    map = map_init(sizeof(char), sizeof(int), true, cmp, 10);

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

static void test_empty_get(map_t *map) {
  char key = 'a';
  int val;

  BOOST_TEST(map_get(map, (const void *)&key, (void *)&val) == ERR_EMPTY);
}

static void test_empty_getp(map_t *map) {
  char key = 'a';
  int *val;

  BOOST_TEST(map_getp(map, (const void *)&key, (void **)&val) == ERR_EMPTY);
}

static void test_empty_clear(map_t *map) {
  BOOST_TEST(map_clear(map) == ERR_NONE);
}

/*! \test       test_map/umap_empty_ops
 *  \brief      Unordered map empty operations testing suite
 *  \details    Asserts proper behavior in error throwing upon
 *              get operations on an empty unordered map.
 */
BOOST_FIXTURE_TEST_SUITE(umap_empty_ops, umap_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_get) { test_empty_get(&map); }

BOOST_AUTO_TEST_CASE(empty_getp) { test_empty_getp(&map); }

BOOST_AUTO_TEST_CASE(empty_clear) { test_empty_clear(&map); }

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_map/omap_empty_ops
 *  \brief      Ordered map empty operations testing suite
 *  \details    Asserts proper behavior in error throwing upon
 *              get operations on an empty ordered map
 */
BOOST_FIXTURE_TEST_SUITE(omap_empty_ops, omap_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_get) { test_empty_get(&map); }

BOOST_AUTO_TEST_CASE(empty_getp) { test_empty_get(&map); }

BOOST_AUTO_TEST_CASE(empty_clear) { test_empty_clear(&map); }

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_map/addition_ops
 *  \brief      Map addition operations testing suite
 *  \details    Asserts proper behavior in executing
 *              set operations.
 */
BOOST_AUTO_TEST_SUITE(addition_ops)

static void test_set_five_elements(map_t *map) {
  char keys[5] = {'a', 'b', 'c', 'd', 'e'};
  int vals[5] = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; i++) {
    BOOST_TEST(map_set(map, (const void *)&keys[i], (const void *)&vals[i]) ==
               ERR_NONE);
  }

  BOOST_TEST(map_length(map) == 5);
}

BOOST_FIXTURE_TEST_CASE(umap_set_five_elements, umap_empty_fixture) {
  test_set_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(omap_set_five_elements, omap_empty_fixture) {
  test_set_five_elements(&map);
}

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_map/subtraction_ops
 *  \brief      Map subtraction operations testing suite
 *  \details    Asserts proper behavior in executing get,
 *              delete, and clear operations.
 */
BOOST_AUTO_TEST_SUITE(subtraction_ops)

static void test_get_five_elements(map_t *map) {
  char keys[5] = {'a', 'b', 'c', 'd', 'e'};
  int vals[5];

  for (int i = 0; i < 5; i++) {
    BOOST_TEST(map_get(map, (const void *)&keys[i], (void *)&vals[i]) ==
               ERR_NONE);
    BOOST_TEST(vals[i] == i + 1);
  }
}

static void test_getp_five_elements(map_t *map) {
  char keys[5] = {'a', 'b', 'c', 'd', 'e'};
  int *vals[5];

  for (int i = 0; i < 5; i++) {
    BOOST_TEST(map_getp(map, (const void *)&keys[i], (void **)&vals[i]) ==
               ERR_NONE);
    BOOST_TEST(*vals[i] == i + 1);
  }
}

static void test_del_five_elements(map_t *map) {
  char keys[5] = {'a', 'b', 'c', 'd', 'e'};

  for (int i = 0; i < 5; i++) {
    BOOST_TEST(map_del(map, (const void *)&keys[i]) == ERR_NONE);
    BOOST_TEST(map_length(map) == 4 - i);
  }
}

static void test_clear_five_elements(map_t *map) {
  BOOST_TEST(map_clear(map) == ERR_NONE);
  BOOST_TEST(map_length(map) == 0);
}

BOOST_FIXTURE_TEST_CASE(umap_get_five_elements, umap_populated_fixture) {
  test_get_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(umap_getp_five_elements, umap_populated_fixture) {
  test_getp_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(umap_del_five_elements, umap_populated_fixture) {
  test_del_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(umap_clear_five_elements, umap_populated_fixture) {
  test_clear_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(omap_get_five_elements, omap_populated_fixture) {
  test_get_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(omap_getp_five_elements, omap_populated_fixture) {
  test_getp_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(omap_del_five_elements, omap_populated_fixture) {
  test_del_five_elements(&map);
}

BOOST_FIXTURE_TEST_CASE(omap_clear_five_elements, omap_populated_fixture) {
  test_clear_five_elements(&map);
}

BOOST_AUTO_TEST_SUITE_END()

static void test_keys_five_elements(map_t *map) {
  char keys[5] = {'a', 'b', 'c', 'd', 'e'};

  vla_t vla = vla_init(sizeof(char), 5);
  BOOST_TEST(map_keys(map, &vla) == ERR_NONE);

  for (int i = 0; i < 5; i++) {
    char *key;
    BOOST_TEST(vla_getp(&vla, i, (void **)&key) == ERR_NONE);
    BOOST_TEST(*key == keys[i]);
  }
}

static void test_vals_five_elements(map_t *map) {
  int vals[5] = {1, 2, 3, 4, 5};

  vla_t vla = vla_init(sizeof(int), 5);
  BOOST_TEST(map_vals(map, &vla) == ERR_NONE);

  for (int i = 0; i < 5; i++) {
    int *val;
    BOOST_TEST(vla_getp(&vla, i, (void **)&val) == ERR_NONE);
    BOOST_TEST(*val == vals[i]);
  }
}

static void test_pairs_five_elements(map_t *map) {
  map_pair_t pairs[5];
  char keys[5] = {'a', 'b', 'c', 'd', 'e'};
  int vals[5] = {1, 2, 3, 4, 5};

  vla_t vla = vla_init(sizeof(map_pair_t), 5);
  BOOST_TEST(map_pairs(map, &vla) == ERR_NONE);

  for (int i = 0; i < 5; i++) {
    map_pair_t *pair;
    BOOST_TEST(vla_getp(&vla, i, (void **)&pair) == ERR_NONE);
    BOOST_TEST(*(char *)pair->key == keys[i]);
    BOOST_TEST(*(int *)pair->val == vals[i]);
  }
}

/*! \test       test_map/umap_aggregation_ops
 *  \brief      Unordered map aggregation operations testing suite
 *  \details    Asserts proper behavior in executing keys, vals, and
 *              pairs aggregations on unordered map.
 */
BOOST_FIXTURE_TEST_SUITE(umap_aggregation_ops, umap_populated_fixture)

BOOST_AUTO_TEST_CASE(keys_five_elements) { test_keys_five_elements(&map); }

BOOST_AUTO_TEST_CASE(vals_five_elements) { test_vals_five_elements(&map); }

BOOST_AUTO_TEST_CASE(pairs_five_elements) { test_pairs_five_elements(&map); }

BOOST_AUTO_TEST_SUITE_END()

/*! \test       test_map/omap_aggregation_ops
 *  \brief      Ordered map aggregation operations testing suite
 *  \details    Asserts proper behavior in executing keys, vals, and
 *              pairs aggregations on ordered map.
 */

BOOST_FIXTURE_TEST_SUITE(omap_aggregation_ops, omap_populated_fixture)

BOOST_AUTO_TEST_CASE(keys_five_elements) { test_keys_five_elements(&map); }

BOOST_AUTO_TEST_CASE(vals_five_elements) { test_vals_five_elements(&map); }

BOOST_AUTO_TEST_CASE(pairs_five_elements) { test_pairs_five_elements(&map); }

BOOST_AUTO_TEST_SUITE_END()
