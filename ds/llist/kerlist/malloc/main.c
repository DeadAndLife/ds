#include <stdio.h>

#include "myalloc.h"

int main(void)
{
      void *tmp1, *tmp2, *tmp3;
      tmp1 = myalloc(32);
      printf("tmp1 = %p\n", tmp1);
      //myfree(tmp1);
      //tmp1 = NULL;
      tmp2 = myalloc(64);
      printf("tmp2 = %p\n", tmp2);
      myfree(tmp1);
      printf("test.\n");
      tmp1 = NULL;
      tmp1 = myalloc(64);
      printf("tmp1 = %p\n", tmp1);
      myfree(tmp2);
      tmp3 = myalloc(16);
      printf("tmp3 = %p\n", tmp3);

      return 0;
}
