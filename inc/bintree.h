/*! \file bintree.h
 *	\brief Header file for the Binary Tree data structure implementation.
 */

#ifndef BINTREE_H
#define BINTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>

typedef struct binary_tree BinaryTree_t;
typedef struct tree_node TreeNode_t;

struct tree_node
{
	void *elem;
	int i;
	TreeNode_t *parent, *left_child, *right_child;
	bool is_root;
};

struct binary_tree
{
	TreeNode_t *root;
	size_t size;
	size_t len;
};

int bintree_init(BinaryTree_t *tree, size_t size);
int bintree_deinit(BinaryTree_t *tree);

int bintree_add_root(BinaryTree_t *tree, void *elem);

int bintree_set(BinaryTree_t *tree, TreeNode_t *node, void *elem);
int bintree_set_right(BinaryTree_t *tree, TreeNode_t *parent, void *elem);
int bintree_set_left(BinaryTree_t *tree, TreeNode_t *parent, void *elem);

int bintree_rem(BinaryTree_t *tree, TreeNode_t *node, void *elem);
int bintree_get(BinaryTree_t *tree, TreeNode_t *node, void *elem);

#ifdef __cplusplus
}
#endif

#endif // BINTREE_H
