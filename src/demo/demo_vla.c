/*! \brief libstructs vla demo application
 *  \author Brian Reece
 *  \date 10/03/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs/vla.h"

static void bubble_sort(vla_t *vla);

int main(void)
{
  vla_t list;
  int i;
  if (vla_init(&list, sizeof(int), 30) < 0)
    return -1;
        
  srand(time(NULL));
  for (i = 0; i < 50; i++)
  {
    int val = rand() % 50;
    printf("Pushing: %d\n", val);
    vla_push(&list, &val);
  }

  printf("\nSorting VLA with Bubble Sort\n\n");
  bubble_sort(&list);

  for (i = 0; i < 50; i++)
  {
    int val;
    vla_pop(&list, &val);
    printf("Popped: %d\n", val);
  } 

  vla_deinit(&list);
  return 0;
}

void bubble_sort(vla_t *list)
{
  int i, j;

  for (i = 0; i < vla_size(list); i++)
  {
    for (j = i; j < vla_size(list); j++)
    {
      int val1, val2;
      vla_get(list, i, &val1);
      vla_get(list, j, &val2);
      if (val1 > val2)
      {
        vla_set(list, i, &val2);
        vla_set(list, j, &val1);
      }      
    }
  }
}



