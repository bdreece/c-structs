/*! \file example_arraylist.c
 *  \brief ArrayList Example Program
 *  An example program to demonstrate the usage of the ArrayList data structure.
 */

#include "arraylist.h"

int main(void)
{
  ArrayList_t list;

  int a[] = {1, 2, 3, 4, 5, 6, 7};
  int i;

  if (arraylist_init(&list, 5, sizeof(int)) < 0)
  {
    printf("ArrayList init failed\n");
    exit(1);
  } else
    printf("ArrayList initialized\n");

  for (i = 0; i < 6; i++)
  {
    printf("ArrayList size = %d\n", list->size);
    printf("ArrayList capacity = %d\n\n", list->capacity);

    if (arraylist_add(&list, (void *)a[i]) < 0)
      printf("ArrayList add failed\n");
    else
      printf("ArrayList added element %d at index %d\n\n", list.data[i], i);
  }

  if (arraylist_insert(&list, 3, (void *)a[6]) < 0)
    printf("ArrayList insert failed\n");
  else
    printf("ArrayList inserted element %d at index %d\n\n");

  int dump;
  int b = 20;

  if (arraylist_set(&list, 4, (void *)&b, (void *)&dump) < 0)
    printf("ArrayList set failed\n");
  else
    printf("ArrayList set element %d at index &d to %d\n\n", dump, 4, b);

  for (i = 0; i < 7; i++)
  {
    printf("ArrayList size = %d\n", list->size);
    printf("ArrayList capacity = %d\n\n", list->capacity);

    if (arraylist_remove(list, &i, (void *)&dump) < 0)
      printf("ArrayList remove failed\n");
    else
      printf("ArrayList removed %d from index %d\n\n", dump, i);
  }

  if (arraylist_deinit(&list) < 0)
    printf("ArrayList deinit failed\n");
  else
    printf("ArrayList deinitialized\n");

  return 0;
}
