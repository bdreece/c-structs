/*! \brief libstructs demo application
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
  vla_t vla;
  int i;
  if (vla_init(&vla, sizeof(int), 30) < 0)
    return -1;
        
  srand(time(NULL));
  for (i = 0; i < 50; i++)
  {
    int val = rand() % 50;
    vla_push(&vla, &val);
  }
        
  bubble_sort(&vla);

  for (i = 0; i < 50; i++)
  {
    int val;
    vla_pop(&vla, &val);
    printf("%d ", &val);
  } 

  return 0;
}

void bubble_sort(vla_t *vla)
{
  int i, j;

  for (i = 0; i < vla_size(vla); i++)
  {
    for (j = i; j < vla_size(vla); j++)
    {
      int val1, val2;
      vla_get(vla, i, &val1);
      vla_get(vla, j, &val2);
      if (val1 > val2)
      {
        vla_set(vla, i, &val2);
        vla_set(vla, j, &val1);
      }      
    }
  }
}



