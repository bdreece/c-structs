/*! \file list_demo.c
 *	\brief Demonstration of the List data structure API usage
 */

#include "list.h"

#include <error.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		error(1, 0, "Usage: ./list_demo [VALUES]\n");

	int i;
	List_t list;

	if (list_init(&list, argc - 1, sizeof(char)) < 0)
		error(1, 0, "list_init failed\n");

	printf("Initialized list successfully!\n");

	for (i = 0; i < argc - 2; i++)
	{
		if (list_addlast(&list, (void *)&argv[0][i]) < 0)
			error(1, 0, "list_addlast failed\n");

		printf("Added %c to list at index %d\n", argv[0][i], i);
	}

	const char tmp = 'A';
	if (list_addfirst(&list, (void *)&tmp) < 0)
		error(1, 0, "list_addfirst failed\n");
	printf("List size: %ld\nList capacity: %ld\n", list.size, list.cap);

	if (list_deinit(&list) < 0)
		error(1, 0, "list_deinit failed\n");

	exit(0);
}
