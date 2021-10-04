/*! \brief libstructs cbuf demo application
 *  \author Brian Reece
 *  \date 10/03/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs/cbuf.h"

int main(void)
{
  int i;
  cbuf_t buf;

  if (cbuf_init(&buf, sizeof(int), 30) < 0)
    return -1;

 srand(time(NULL));
  for (i = 0; i < 25; i++)
  {
    int val = rand() % 30;
    printf("Writing %d\n", val);
    cbuf_write(&buf, &val);
  }

  printf("\n");

  for (i = 0; i < 10; i++)
  {
    int val;
    cbuf_read(&buf, &val);
    printf("Reading %d\n", val);
    printf("Writing %d\n\n", val);
    cbuf_write(&buf, &val);
  }

  int val;
  while (cbuf_read(&buf, &val) == 0)
    printf("Reading %d\n", val);

  cbuf_clear(&buf);
  cbuf_deinit(&buf);
  return 0;
}
