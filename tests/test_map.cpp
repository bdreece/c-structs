#define BOOST_TEST_MODULE MAP
#include <boost/test/included/unit_test.hpp>

#include "structs/map.h"

int cmp(const void *a, const void *b, size_t size) {
  if (*(char *)a < *(char *)b)
    return -1;
  else if (*(char *)a > *(char *)b)
    return 1;
  else
    return 0;
};

BOOST_AUTO_TEST_CASE(test_map_init) {
  umap_t map;

  int ret = umap_init(&map, sizeof(char), sizeof(int), &cmp, 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.vla.capacity == 10);

  umap_deinit(&map);
}
