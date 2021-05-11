/*! \file linkedlist.h
 *  \brief LinkedList Header File
 *
 *  Header file for the LinkedList data structure
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

/*! \brief Node structure object
 *
 *  Structure for a node in the LinkedList data structure. Nodes contain an
 *  element, and pointers to the previous and next nodes.
 */
typedef struct Node {
  void *element; //!< The element stored in the node
  Node *next;    //!< A pointer to the next node
  Node *prev;    //!< A pointer to the previous node
} Node_t;

/*! \brief LinkedList structure object
 *
 *  Structure for the LinkedList data structure. Contains pointer to the first
 *  and last nodes, as well as the size of the LinkedList.
 */
typedef struct {
  Node_t *first;    //!< The first node in the LinkedList
  Node_t *last;     //!< The last node in the LinkedList
  int size;         //!< The size of the LinkedList
  size_t elem_size; //!< The number of bytes per element
  bool circular;    //!< Whether the list is to be circular
} LinkedList_t;

/*! \brief Initialize a LinkedList instance
 *
 *  Initializes the LinkedList with no nodes and a size of zero
 *
 *  \param list The LinkedList to initialize
 *  \param circular Whether the LinkedList is to be initialized as circular
 *  \return 0 if successful, -1 if malloc fails
 */
int linkedlist_init(LinkedList_t *list, size_t element_size, bool circular);

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
 *  \param element The element of the new node
 *  \return The newly created node, or NULL if malloc failed
 */
Node_t *linkedlist_insert_after(LinkedList_t *list, Node_t *node, void *element);

/*! \brief Insert a new node after a specified node in the LinkedList
 *
 *  Adds a new node after the specified node in the LinkedList. Node memory
 *  is dynamically allocated at runtime.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node after which the new node is to be inserted
 *  \param element The element of the new node
 *  \return The newly created node, or NULL if malloc fails
 */
Node_t *linkedlist_insert_before(LinkedList_t *list, Node_t *node, void *element);

/*! \brief Add a new node to a LinkedList
 *
 *  Adds a new node to the end of a LinkedList instance. Node memory is
 *  dynamically allocated at runtime.
 *
 *  \param list The relevant LinkedList instance
 *  \param element The element of the new node to be added to the LinkedList
 *  \return The newly created node, or NULL if malloc fails
 */
Node_t *linkedlist_add(LinkedList_t *list, void *element);

/*! \brief Removes a node from a LinkedList
 *
 *  Removes a given node from a LinkedList instance. Returns the element of the
 *  node being removed.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node to be removed
 *  \param out The pointer to the output of the element of the node being removed
 *  \return 0 if successful, -1 if uninitialized parameters
 */
int linkedlist_remove(LinkedList_t *list, Node_t *node, void *out);

/*! \brief Sets the value of a node in a LinkedList
 *
 *  Sets the value of a given node. Use of this function is to ensure proper
 *  memory copying of the element data.
 *
 *  \param list The relevant LinkedList instance
 *  \param node The node whose element is to be set
 *  \param val The new element of the node
 *  \param out The pointer to the output of the previous element of the node
 *  \return 0 if successful, -1 if uninitialized parameters
 */
int linkedlist_set(LinkedList_t *list, Node_t *node, void *val, void *out);

static Node_t *linkedlist_create_node(LinkedList_t *list, void *val);

#endif
