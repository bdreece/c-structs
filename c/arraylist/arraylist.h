/*! \file arraylist.h
 *  \brief ArrayList Header File
 *
 *  Header file for the ArrayList data structure.
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

/*! \brief ArrayList object structure
 *
 *  This is where all the relevant pointers and parameters for an instance of
 *  the ArrayList will be stored.
 */
typedef struct
{
  void *first;  //!< Pointer to the first element of the ArrayList.
  void *last;   //!< Ponter to the last element of the ArrayList.
  int size;     //!< The number of elements in the ArrayList.
  int capacity; //!< The current capacity of the data array.
  void **data;   //!< Dynamically allocated data array of pointers.
} ArrayList_t;

/*! \brief Initialize ArrayList
 *
 *  Allocates heap memory for data array, initializes capacity, and defines
 *  first and last element pointers.
 *
 *  \param list The ArrayList instance to initialize.
 *  \param length The initial capacity of the ArrayList instance.
 *  \return 0 if successful, -1 if malloc fails or list points to NULL.
 */
int arraylist_init(ArrayList_t *list, int length);

/*! \brief Deinitialize ArrayList
 *
 *  Frees all heap memory associated with ArrayList instance
 *
 *  \param list The ArrayList instance to deinitialize.
 *  \return 0 if successful, -1 if data array is uninitialized.
 */
int arraylist_deinit(ArrayList_t *list);

/*! \brief Add an element to an ArrayList instance
 *
 *  Adds an element to the end of the ArrayList. If capacity is to be exceeded,
 *  the data array will be resized.
 *
 *  \param list The ArrayList instance in which the element will be added
 *  \param val The value to add to the ArrayList
 *  \return 0 if successful, -1 if list is uninitialized.
 */
int arraylist_add(ArrayList_t *list, void *val);

/*! \brief Insert an element in an ArrayList instance
 *
 *  Inserts a value at a given index of the ArrayList. If there is a value at
 *  the specified index, this value and its successors will be shifted right by
 *  one index. If capacity is to be exceeded, the data array will be resized.
 *
 *  \param list The ArrayList instance in which the element will be inserted.
 *  \param i The index at which the element will be inserted.
 *  \param val The value to be inserted.
 *  \return 0 if successful, -1 if list is uninitialized.
 */
int arraylist_insert(ArrayList_t *list, int i, void *val);

/*! \brief Remove an element from an ArrayList instance
 *
 *  Removes a value at a given index of the ArrayList. If there is no element
 *  at the specified index, the function will return NULL. Otherwise, the
 *  removed element will be returned.
 *
 *  \param list The ArrayList instance from which the element will be removed.
 *  \param i The index of the element to be removed.
 *  \return The removed element, or NULL if no element is present.
 */
void *arraylist_remove(ArrayList_t *list, int i);

/*! \brief Sets the value of a given element in the ArrayList instance
 *
 *  Sets the value of an element at the specified index in the ArrayList. If
 *  there is no element at the specified index, the function will return NULL.
 *  If capacity is to be exceeded, the data array will be resized.
 *
 *  \param list The ArrayList instance in which the element will be set.
 *  \param i The index of the element whose value will be set
 *  \param val The new value for the given element.
 *  \return The replaced element, or NULL if no element is present.
 */
void *arraylist_set(ArrayList_t *list, int i, void *val);

/*! \brief Resize the data array
 *
 *  Static helper function to double the capacity of the ArrayList data array.
 *  Should not be invoked directly.
 *
 *  \param list The ArrayList instance to be resized.
 *  \return The new capacity of the ArrayList.
 */
static int arraylist_resize(ArrayList_t *list);

#endif
