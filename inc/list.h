/*! \file list.h
 *  \brief List Header File
 *
 *  Header file for the List data structure.
 */

#ifndef List_H
#define List_H

#include <stddef.h>

/*! \brief List object structure
 *
 *  This is where all the relevant pointers and parameters for an instance of
 *  the List will be stored.
 */
typedef struct
{
  void *first, *last; //!< Pointer to the first and last elements of the List.
  size_t size; 				//!< The number of bytes per element
	size_t len;         //!< The number of elements in the List.
	size_t cap;     		//!< The current capacity of the data array.
  void **data;      	//!< Dynamically allocated data array of pointers.
} List_t;

/*! \brief Initialize List
 *
 *  Allocates heap memory for data array, initializes capacity, and defines
 *  first and last element pointers.
 *
 *  \param list The List instance to initialize
 *  \param size The number of bytes per element
 *	\param cap The initial capacity of the data array
 *  \return 0 if successful, -1 if malloc fails or list points to NULL.
 */
int list_init(List_t *list, size_t size, size_t cap);

/*! \brief Deinitialize List
 *
 *  Frees all heap memory associated with List instance
 *
 *  \param list The List instance to deinitialize
 *  \return 0 if successful, -1 if data array is uninitialized
 */
int list_deinit(List_t *list);

/*! \brief Add an element in an List instance
 *
 *  Adds a value at a given index of the List. If there is a value at
 *  the specified index, this value and its successors will be shifted right by
 *  one index. If capacity is to be exceeded, the data array will be resized.
 *
 *  \param list The List instance in which the element will be added.
 *  \param i The index at which the element will be added.
 *  \param elem The element to be added.
 *  \return 0 if successful, -1 if list is uninitialized.
 */
int list_add(List_t *list, int i, void *elem);

/*! \brief Add an element to the beginning of a List instance
 *
 *	Adds a value at the beginning of the List. If there exists a value in the
 *	List, all values will be shifted right by one index. If capacity is to be
 *	exceeded, the data array will be resized.
 *
 *	\param list The List instance in which the element will be added
 *	\param elem The element to be added
 *	\return 0 if successful, -1 if list is uninitialized
 */
int list_addfirst(List_t *list, void *elem);

/*! \brief Add an element to the end of a List instance
 *
 *	Adds a value at the end of the List. If capacity is to be	exceeded, the
 *  data array will be resized.
 *
 *	\param list The List instance in which the element will be added
 *	\param elem The element to be added
 *	\return 0 if successful, -1 if list is uninitialized
 */
int list_addlast(List_t *list, void *elem);

/*! \brief Remove an element from an List instance
 *
 *  Removes a value at a given index of the List. If there is no element
 *  at the specified index, the function will return NULL. Otherwise, the
 *  removed element will be returned.
 *
 *  \param list The List instance from which the element will be removed
 *  \param i The index of the element to be removed
 *  \param elem The element that has been removed
 *  \return 0 if successful, -1 if pointers uninitialized or i out of bounds
 */
int list_remove(List_t *list, int i, void *elem);

/*!	\brief Remove an element from the beginning of a List instance
 *
 *	Removes a value from the beginning of the List. If there exists no elements
 *	in the list, the function will return NULL. Otherwise, the removed element
 *	will be returned.
 *
 *	\param list The List instance from which the element will be removed
 *	\param elem The element that has been removed
 *	\return 0 if successful, -1 if pointers uninitialized or i out of bounds
 */
int list_removefirst(List_t *list, void *elem);

/*!	\brief Remove an element from the end of a List instance
 *
 *	Removes a value from the end of the List. If there exists no elements
 *	in the list, the function will return NULL. Otherwise, the removed element
 *	will be returned.
 *
 *	\param list The List instance from which the element will be removed
 *	\param elem The element that has been removed
 *	\return 0 if successful, -1 if pointers uninitialized or i out of bounds
 */
int list_removelast(List_t *list, void *elem);

/*! \brief Sets the value of a given element in the List instance
 *
 *  Sets the value of an element at the specified index in the List. If
 *  there is no element at the specified index, the function will return NULL.
 *  If capacity is to be exceeded, the data array will be resized.
 *
 *  \param list The List instance in which the element will be set
 *  \param i The index of the element whose value will be set
 *  \param elem The new value for the given element
 *  \return 0 if successful, -1 if pointers uninitialized or i out of bounds
 */
int list_set(List_t *list, int i, void *elem);

/*!	\brief Gets the value of a given element in the List instance
 *
 *	Gets the value of an element at the specified index in the List. If there
 *	is no element at the specified index, the function will return NULL in the
 *	pointer to elem.
 *
 *	\param list The list instance from which the element will be returned
 *	\param i The index of the element whose value will be returned
 *	\param elem A pointer to the element being returned
 *	\return 0 if successful, -1 if pointers uninitialized or i out of bounds
 */
int list_get(List_t *list, int i, void *elem);

#endif
