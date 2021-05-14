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

	LinkedList_t list;
	if (linkedlist_init(&list, sizeof(char), false);

}
