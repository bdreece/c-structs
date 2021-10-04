/*! \file tree.c
 *  \author Brian Reece
 *  \date 10/04/2021
 */

#include <stdlib.h>
#include <string.h>
#include "structs/error.h"
#include "structs/tree.h"

static node_t *tree_create_node(tree_t *tree, node_t *parent, void *element)
{
  if (!tree || !element)
    return NULL;

  node_t *node = (node_t *) malloc(sizeof(struct node));
  node->parent = parent;

  node->element = malloc(tree->element_size);
  if (!memcpy(node->element, element, tree->element_size))
    return NULL;

  if (vla_init(&node->children, tree->element_size, 2))
    return NULL;

  return node;
}

int tree_init(tree_t *tree, size_t element_size)
{
  if (!tree)
    return ERR_NULL;

  if (element_size <= 0)
    return ERR_INVALID_ARGUMENT;

  tree->root = NULL;
  tree->element_size = element_size;

  return ERR_NONE;
}

int tree_deinit(tree_t *tree)
{
  return 0;
}

int tree_add_child(tree_t *tree, node_t *parent, void *child_element)
{
  return 0;
}

int tree_get_root(tree_t *tree, void *root_element)
{
  return 0;
}

int tree_get_child(tree_t *tree, node_t *parent, int i, node_t *child)
{
  return 0;
}

int tree_get_children(tree_t *tree, node_t *parent, vla_t *children)
{
  return 0;
}

int tree_get_parent(tree_t *tree, node_t *child, node_t *parent)
{
  return 0;
}

int tree_set_root(tree_t *tree, void *root_element)
{
  return 0;
}

int tree_set_child(tree_t *tree, node_t *parent, int i, void *child_element)
{
  return 0;
}

int tree_set_parent(tree_t *tree, node_t *child, void *parent_element)
{
  return 0;
}

int tree_ins_child(tree_t *tree, node_t *parent, int i, void *child_element)
{
  return 0;
}

int tree_del_child(tree_t *tree, node_t *parent, int i)
{
  return 0;
}

int tree_del_branch(tree_t *tree, node_t *branch_root)
{
  return 0;
}
