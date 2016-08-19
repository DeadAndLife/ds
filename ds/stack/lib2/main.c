#include <stdio.h>

#include "stack.h"

#define NAMESIZE 32

struct score {
      char name[NAMESIZE];
      int chinese;
      int math;
};

int main(void)
{
      STACK *sta;
      struct score tmp;
      int i, ret;

      sta = stack_creat(sizeof(struct score));
      if (0) {

      }
      for (i = 0; i < 6; i++) {
	    snprintf(tmp.name, NAMESIZE, "stu%d", i);
	    tmp.chinese = i;
	    tmp.math = i * i;
	    stack_push(sta, &tmp);
      }

      for (i = 0; i < 8; i++) {
	    ret = stack_pop(sta, &tmp);
	    if (ret) {
		  printf("stack empty.\n");
	    } else {
		  printf("%s, %d, %d\n", tmp.name, tmp.chinese, tmp.math);
	    }
      }

      return 0;
}
