#define BOOST_TEST_MODULE test_map
#include <boost/test/included/unit_test.hpp>

#include "structs/map.h"

static map_t map;

static int cmp(const void *a, const void *b, size_t size) {
  if (*(char *)a < *(char *)b)
    return -1;
  else if (*(char *)a > *(char *)b)
    return 1;
  else
    return 0;
};

BOOST_AUTO_TEST_CASE(test_umap_init) {
  int ret = map_init(&map, sizeof(char), sizeof(int), false, cmp, 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_umap_set) {
  char key = 'a';
  int val = 1;

  int ret = map_set(&map, (const void *)&key, (const void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 1);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_umap_get) {
  char key = 'a';
  int val;

  int ret = map_get(&map, (const void *)&key, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 1);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);

  BOOST_TEST(val == 1);
}

BOOST_AUTO_TEST_CASE(test_umap_getp) {
  char key = 'a';
  int *val;

  int ret = map_getp(&map, (const void *)&key, (void **)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 1);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);

  BOOST_TEST(*val == 1);
}

BOOST_AUTO_TEST_CASE(test_umap_del) {
  char key = 'a';

  int ret = map_del(&map, (const void *)&key);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_umap_clear) {
  int ret = map_clear(&map);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_umap_deinit) {
  int ret = map_deinit(&map);

  BOOST_TEST(ret == 0);
  BOOST_TEST(!map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 0);
  BOOST_TEST(map.key_size == 0);
  BOOST_TEST(map.val_size == 0);
  BOOST_TEST(map.cmp == (int (*)(const void *, const void *, size_t))NULL);
  BOOST_TEST(map.search == (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_omap_init) {
  int ret = map_init(&map, sizeof(char), sizeof(int), true, cmp, 10);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_omap_set) {
  char key = 'a';
  int val = 1;

  int ret = map_set(&map, (const void *)&key, (const void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 1);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_omap_get) {
  char key = 'a';
  int val;

  int ret = map_get(&map, (const void *)&key, (void *)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 1);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);

  BOOST_TEST(val == 1);
}

BOOST_AUTO_TEST_CASE(test_omap_getp) {
  char key = 'a';
  int *val;

  int ret = map_getp(&map, (const void *)&key, (void **)&val);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 1);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);

  BOOST_TEST(*val == 1);
}

BOOST_AUTO_TEST_CASE(test_omap_del) {
  char key = 'a';

  int ret = map_del(&map, (const void *)&key);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_omap_clear) {
  int ret = map_clear(&map);

  BOOST_TEST(ret == 0);
  BOOST_TEST(map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 10);
  BOOST_TEST(map.key_size == sizeof(char));
  BOOST_TEST(map.val_size == sizeof(int));
  BOOST_TEST(map.cmp == cmp);
  BOOST_TEST(map.search != (long (*)(const struct map *, const void *))NULL);
}

BOOST_AUTO_TEST_CASE(test_omap_deinit) {
  int ret = map_deinit(&map);

  BOOST_TEST(ret == 0);
  BOOST_TEST(!map.vla.elements);
  BOOST_TEST(map.vla.size == 0);
  BOOST_TEST(map.vla.capacity == 0);
  BOOST_TEST(map.key_size == 0);
  BOOST_TEST(map.val_size == 0);
  BOOST_TEST(map.cmp == (int (*)(const void *, const void *, size_t))NULL);
  BOOST_TEST(map.search == (long (*)(const struct map *, const void *))NULL);
}
