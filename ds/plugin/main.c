#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

int main(void)
{
      int (*op1)(int, int);
      int (*op2)(int, int);
      int (*sym1)(void);
      int (*sym2)(void);
      void *handle1, *handle2;
      int i, j;
      int num;
      char *plugin[] = {"./add.plugin", "./sub.plugin", \
			"./mul.plugin", "./div.plugin"};

      num = sizeof(plugin) / sizeof(char *);
      for (i = 0; i < num; i++) {
	    handle1 = dlopen(plugin[i], RTLD_LAZY);
	    if (handle1 == NULL) {
		  printf("dlopen error.\n");
		  exit(1);
	    }
	    op1 = dlsym(handle1, "op");
	    if (op1 == NULL) {
		  printf("dlsym error.\n");
		  dlclose(handle1);
		  exit(1);
	    }
	    sym1 = dlsym(handle1, "sym");
	    if (sym1 == NULL) {
                  printf("dlsym error.\n");
                  dlclose(handle1);
                  exit(1);
            }
	    for (j = 0; j < num; j++) {
		  handle2 = dlopen(plugin[j], RTLD_LAZY);
		  if (handle2 == NULL) {
			printf("dlopen error.\n");
			exit(1);
		  }
		  op2 = dlsym(handle2, "op");
		  if (op2 == NULL) {
			printf("dlsym error.\n");
			dlclose(handle2);
			exit(1);
		  }
		  sym2 = dlsym(handle2, "sym");
		  if (sym2 == NULL) {
			printf("dlsym error.\n");
			dlclose(handle2);
			exit(1);
		  }
	      
          printf("2 %c 2 %c 3 = %d\n", sym1(), sym2(), op2(op1(2, 2), 3));

	    }
      }

      dlclose(handle2);
      dlclose(handle1);
      return 0;

#if 0


      printf("%d\n", p(3, 4));
#endif
}
