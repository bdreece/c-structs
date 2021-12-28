#define BOOST_TEST_MODULE test_hashmap
#include <boost/test/included/unit_test.hpp>

#include "structs/hashmap.h"
#include "util.h"

static hashmap_t map;

BOOST_AUTO_TEST_CASE(test_hashmap_init) {
  int ret = hashmap_init(&map, sizeof(char), sizeof(int), cmp, 3, 10, 0.75);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(vla_size(&map.vla) == 3);
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.load_factor == 0.75);

  const map_t *m;
  const long n = hashmap_size(&map);

  // Check each bucket map has been initialized
  for (int i = 0; i < n; i++) {
    BOOST_TEST(vla_getp(&map.vla, i, (void **)&m) < 0);
    BOOST_TEST(m->vla.elements);
    BOOST_TEST(vla_capacity(&m->vla) == 10);
  }
};

BOOST_AUTO_TEST_CASE(test_hashmap_set) {
  int ret;
  const char keys[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
  const int vals[6] = {1, 2, 3, 4, 5, 6};

  for (int i = 0; i < 6; i++) {
    ret = hashmap_set(&map, (const void *)&keys[i], (const void *)&vals[i]);
    BOOST_TEST(ret == 0);
  }
}
