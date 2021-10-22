/*! \brief libstructs map demo application
 *  \author Brian Reece
 *  \date 10/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs/map.h"

int main(void)
{
  int i;
  map_t map;
  if (map_init(&map, false, 16 * sizeof(char), sizeof(int), 10, &strncmp) < 0)
    return -1;

  const char *key[4] = {
    "dog",
    "cat",
    "mouse",
    "snake"
  };

  for (i = 0; i < 4; i++)
  {
    if (map_set(&map, (void *)key[i], (void *)&i) < 0)
      return -1;

    printf("Added ['%s', '%d'] to the map\n", key[i], i);
  }

  int j;
  for (i = 0; i < 4; i++)
  {
    if (map_get(&map, (void *)key[i], (void *)&j) < 0)
      return -1;

    printf("Retrieved ['%s', '%d'] from the map\n", key[i], j);
  }

  if (map_deinit(&map) < 0)
    return -1;
  return 0;
}
