#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

int main(void)
{
      int (*op)(int, int);
      int (*sym)(void);
      void *handle;

      handle = dlopen("./add.plugin", RTLD_LAZY);
      if (handle == NULL) {
	    printf("dlopen error.\n");
	    exit(1);
      }

      op = dlsym(handle, "add");
      if (op == NULL) {
	    printf("dlsym error.\n");
	    dlclose(op);
        exit(1);
      }

      sym = dlsym(handle, "sym"); 
      if (sym == NULL) {
        printf("dlsym error.\n");
        dlclose(op);
        exit(1);
      }

      printf("3 %c 4 = %d\n", sym(), op(3, 4));
      dlclose(handle);
      return 0;
}
