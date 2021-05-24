/*! \file linkedlist.h
 *  \brief LinkedList Header File
 *
 *  Header file for the LinkedList data structure implementation.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Node Node_t;
typedef struct linkedlist LinkedList_t;

/*! \brief Node structure object
 *
 *  Structure for a node in the LinkedList data structure. Nodes contain an
 *  element, and pointers to the previous and next nodes.
 */
struct Node {
  void *elem; 	//!< The element stored in the node
  Node_t *next; //!< A pointer to the next node
  Node_t *prev; //!< A pointer to the previous node
};

/*! \brief LinkedList structure object
 *
 *  Structure for the LinkedList data structure. Contains pointer to the first
 *  and last nodes, as well as the size of the LinkedList.
 */
struct linkedlist {
  Node_t *first, *last; //!< The first and last nodes in the LinkedList
  size_t size;					//!< The number of bytes per element
	size_t len;     			//!< The length of the LinkedList
  bool circ;      			//!< Whether the list is to be circular
};

/*! \brief Initialize a LinkedList instance
 *
 *  Initializes the LinkedList with no nodes and a size of zero
 *
 *  \param list The LinkedList to initialize
 *	\param size The number of bytes per element
 *  \param circ Whether the LinkedList is to be initialized as circular
 *  \return 0 if successful, -1 if malloc fails
 */
int linkedlist_init(LinkedList_t *list, size_t size, bool circ);

/*! \brief Deinitialize a LinkedList instance
 *
 *  Deinitializes the LinkedList, freeing the node memory and resetting struct
 *  member values.
 *
 *  \param list The LinkedList to deinitialize
 *  \return 0 if successful, -1 if list is uninitialized
 */
int linkedlist_deinit(LinkedList_t *list);

/*! \brief Insert a new node after a specified node in the LinkedList
 *
 *  Adds a new node after the specified node in the LinkedList. Node memory
 *  is dynamically allocated at runtime.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node after which the new node is to be inserted
 *  \param elem The element of the new node
 *  \return The newly created node, or NULL if malloc failed
 */
Node_t *linkedlist_insert_after(LinkedList_t *list, Node_t *node, void *elem);

/*! \brief Insert a new node after a specified node in the LinkedList
 *
 *  Adds a new node after the specified node in the LinkedList. Node memory
 *  is dynamically allocated at runtime.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node after which the new node is to be inserted
 *  \param elem The element of the new node
 *  \return The newly created node, or NULL if malloc fails
 */
Node_t *linkedlist_insert_before(LinkedList_t *list, Node_t *node, void *elem);

/*! \brief Add a new node to a LinkedList
 *
 *  Adds a new node to the end of a LinkedList instance. Node memory is
 *  dynamically allocated at runtime.
 *
 *  \param list The relevant LinkedList instance
 *  \param elem The element of the new node to be added to the LinkedList
 *  \return The newly created node, or NULL if malloc fails
 */
Node_t *linkedlist_add(LinkedList_t *list, void *elem);

/*! \brief Removes a node from a LinkedList
 *
 *  Removes a given node from a LinkedList instance. Returns the element of the
 *  node being removed.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node to be removed
 *  \param elem The pointer to the output of the element of the node being removed
 *  \return 0 if successful, -1 if uninitialized parameters
 */
int linkedlist_rem(LinkedList_t *list, Node_t *node, void *elem);

/*! \brief Sets the value of a node in a LinkedList
 *
 *  Sets the value of a given node. Use of this function is to ensure proper
 *  memory copying of the element data.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node whose element is to be set
 *  \param elem The new element of the node
 *  \return 0 if successful, -1 if uninitialized parameters
 */
int linkedlist_set(LinkedList_t *list, Node_t *node, void *elem);

/*! \brief Gets the value of a node in a LinkedList
 *
 *	Gets the value of a given node. Use of this function is to ensure proper
 *	memory copying of the element data.
 *
 *	\param list The relevant LinkedList instance
 *	\param node The node whose element is to be returned
 *	\param elem The pointer to the element being returned
 *	\return 0 if successful, -1 if uninitialized parameters
 */
int linkedlist_get(LinkedList_t *list, Node_t *node, void *elem);

#endif
