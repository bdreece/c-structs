/*! \brief libstructs tree demo application
 *  \author Brian Reece
 *  \date 10/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs/tree.h"

int main(void)
{
  tree_t tree;
  if (tree_init(&tree, sizeof(int)))
    return -1;

  if (tree_deinit(&tree))
    return -1;

  return 0;
}
