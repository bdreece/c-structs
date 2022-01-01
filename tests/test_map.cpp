#define BOOST_TEST_MODULE test_map
#include "test_map.hpp"

BOOST_AUTO_TEST_SUITE(invalid_init)

BOOST_AUTO_TEST_CASE(null_pointer) {
  map_t *map = NULL;

  BOOST_TEST(map_init(map, sizeof(char), sizeof(int), false, cmp, 10) ==
             ERR_NULL);
}

BOOST_AUTO_TEST_CASE(empty_key_size) {
  map_t map;

  BOOST_TEST(map_init(&map, 0, sizeof(int), false, cmp, 10) ==
             ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_CASE(empty_val_size) {
  map_t map;

  BOOST_TEST(map_init(&map, sizeof(char), 0, false, cmp, 10) ==
             ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_CASE(null_cmp_function) {
  map_t map;

  BOOST_TEST(map_init(&map, sizeof(char), sizeof(int), false,
                      (int (*)(const void *, const void *, const size_t))NULL,
                      10) == ERR_NULL);
}

BOOST_AUTO_TEST_CASE(empty_capacity) {
  map_t map;

  BOOST_TEST(map_init(&map, sizeof(char), sizeof(int), false, cmp, 0) ==
             ERR_INVALID_ARGUMENT);
}

BOOST_AUTO_TEST_SUITE_END()

static void test_empty_get(map_t *map) {}

static void test_empty_getp(map_t *map) {}

static void test_empty_clear(map_t *map) {}

BOOST_FIXTURE_TEST_SUITE(umap_empty_ops, umap_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_get) { test_empty_get(&map); }

BOOST_AUTO_TEST_CASE(empty_getp) { test_empty_getp(&map); }

BOOST_AUTO_TEST_CASE(empty_clear) { test_empty_clear(&map); }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(omap_empty_ops, omap_empty_fixture)

BOOST_AUTO_TEST_CASE(empty_get) { test_empty_get(&map); }

BOOST_AUTO_TEST_CASE(empty_getp) { test_empty_get(&map); }

BOOST_AUTO_TEST_CASE(empty_clear) { test_empty_clear(&map); }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(addition_ops)

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(subtraction_ops)

BOOST_AUTO_TEST_SUITE_END()
