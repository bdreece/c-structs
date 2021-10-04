/*! \file tree.h
 *  \brief Tree data structure header file
 *  \author Brian Reece
 *  \date 10/04/2021
 */

#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "structs/vla.h"

typedef struct node
{
  void *element;
  struct node *parent;
  vla_t children;
} node_t;

typedef struct tree
{
  node_t *root;
  size_t element_size;
} tree_t;

int tree_init(tree_t *tree, size_t element_size);
int tree_deinit(tree_t *tree);

int tree_add_child(tree_t *tree, node_t *parent, void *child_element);

int tree_get_root(tree_t *tree, void *root_element);
int tree_get_child(tree_t *tree, node_t *parent, int i, node_t *child);
int tree_get_children(tree_t *tree, node_t *parent, vla_t *children);
int tree_get_parent(tree_t *tree, node_t *child, node_t *parent);

int tree_set_root(tree_t *tree, void *root_element);
int tree_set_child(tree_t *tree, node_t *parent, int i, void *child_element);
int tree_set_parent(tree_t *tree, node_t *child, void *parent_element);

int tree_ins_child(tree_t *tree, node_t *parent, int i, void *child_element);

int tree_del_child(tree_t *tree, node_t *parent, int i);
int tree_del_branch(tree_t *tree, node_t *branch_root);

#ifdef __cplusplus
}
#endif

#endif // TREE_H
