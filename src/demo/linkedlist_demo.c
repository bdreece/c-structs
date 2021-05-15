/*! \file linkedlist_demo.c
 *	\brief Demonstration of the LinkedList data structure API usage
 */

#include "linkedlist.h"

#include <error.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		error(1, 0, "Usage: ./linkedlist_demo [VALUES]");

	int i;
	LinkedList_t list;
	if (linkedlist_init(&list, 8 * sizeof(char), false) < 0)
		error(1, 0, "linkedlist_init failed\n");

	printf("Initialized LinkedList successfully!\n");

	for (i = 1; i < argc - 1; i++)
	{
		if (linkedlist_add(&list, (void *)argv[i]) < 0)
			error(1, 0, "linkedlist_add failed\n");

		printf("Added %s to LinkedList!\n", argv[i]);
	}

	if (linkedlist_insert_before(&list, list.first, "ABC") < 0)
		error(1, 0, "linkedlist_insert_before failed\n");

	printf("Inserted %s at the beginning of the LinkedList!\n");

	if (linkedlist_deinit(&list) < 0)
		error(1, 0, "linkedlist_deinit failed\n");

	printf("Deinitialized LinkedList successfully!\n");

	exit(0);
}
