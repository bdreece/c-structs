/*! \file example_arraylist.c
 *  \brief ArrayList Example Program
 *  An example program to demonstrate the usage of the ArrayList data structure.
 */

#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  ArrayList_t list;

  int i;

  if (arraylist_init(&list, 5, sizeof(int)) < 0)
  {
    printf("ArrayList init failed\n");
    exit(1);
  } else {
    printf("ArrayList initialized\n");
  }
  fflush(stdout);

  for (i = 0; i < 6; i++)
  {
    printf("ArrayList size = %d\n", list.size);
    printf("ArrayList capacity = %d\n\n", list.capacity);
    fflush(stdout);

    if (arraylist_add(&list, (void *)(&i)) < 0)
    {
      printf("ArrayList add failed\n");
      exit(1);
    } else
    {
      printf("ArrayList added element %d at index %d\n\n", list.data[i], i);
    }
    fflush(stdout);
  }

  i = 6;

  if (arraylist_insert(&list, 3, (void *)(&i)) < 0)
  {
    printf("ArrayList insert failed\n");
    exit(1);
  } else
  {
    printf("ArrayList inserted element %d at index %d\n\n");
  }
  fflush(stdout);

  int dump;
  i = 20;

  if (arraylist_set(&list, 4, (void *)&i, (void *)&dump) < 0)
  {
    printf("ArrayList set failed\n");
    exit(1);
  } else
  {
    printf("ArrayList set element %d at index &d to %d\n\n", dump, 4, i);
  }
  fflush(stdout);

  for (i = 0; i < 7; i++)
  {
    printf("ArrayList size = %d\n", list.size);
    printf("ArrayList capacity = %d\n\n", list.capacity);
    fflush(stdout);

    if (arraylist_remove(&list, i, (void *)&dump) < 0)
    {
      printf("ArrayList remove failed\n");
      exit(1);
    } else
    {
      printf("ArrayList removed %d from index %d\n\n", dump, i);
    }
    fflush(stdout);
  }

  if (arraylist_deinit(&list) < 0)
  {
    printf("ArrayList deinit failed\n");
    exit(1);
  } else
  {
    printf("ArrayList deinitialized\n");
  }
  fflush(stdout);

  return 0;
}
