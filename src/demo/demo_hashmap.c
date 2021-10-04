/*! \brief libstructs hashmap demo application
 *  \author Brian Reece
 *  \date 10/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs/hashmap.h"

int main(void)
{
  int i;
  hashmap_t map;

  if (hashmap_init(&map, sizeof(char), sizeof(int), 30, 0.75))
    return -1;

  srand(time(NULL)); 

  for (i = 0; i < 50; i++)
  {
    char key = (char)(i + 65);
    int val = rand() % 100;
    printf("Key: %c, Val: %3d\n", key, val);
    hashmap_set(&map, (void *)&key, (void *)&val);
  }

  char A = 'A', B = 'B', c = 'c', d = 'd';
  int vA, vB, vc, vd;
  hashmap_get(&map, (void *)&A, (void *)&vA);
  hashmap_get(&map, (void *)&B, (void *)&vB);
  hashmap_get(&map, (void *)&c, (void *)&vc);
  hashmap_get(&map, (void *)&d, (void *)&vd);

  printf("A = %d\nB = %d\nc = %d\nd = %d\n", vA, vB, vc, vd); 

  if (hashmap_deinit(&map))
    return -1;

  return 0;
}
