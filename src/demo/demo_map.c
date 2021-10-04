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
  map_t map;
  if (map_init(&map, true, 16 * sizeof(char), sizeof(int), 10, &strncmp) < 0)
    return -1;
  return 0;
}