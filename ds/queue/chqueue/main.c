#include <stdio.h>

#include "queue.h"

int main(void)
{
      char *src1 = "0123456789";
      char *src2 = "abcde";
      char dest[32];
      char *cur;
      int i, j, k, ret;

      for (k = 0; k < 4; k++) {
        printf("Enqueue:\n");
	    for (i = 0, cur = src1; *cur != '\0'; cur++, i++) {
		  ret = enqueue(*cur);
		  if (ret == -1) {
			printf("full.\n");
			break;
		  }
	    }
        printf("Dequeue:\n");
	    for (j = 0; j < i; j++) {
		  ret = dequeue();
		  if (ret == QUEUEEMPTY) {
              printf("%d\n", QUEUEEMPTY);
			printf("empty.\n");
			break;
		  }
		  dest[j] = ret;
	    }
	    dest[j] = '\0';
        printf("Result:\n");
	    printf("%s\n", dest);

        printf("Enqueue2:\n");
	    for (i = 0, cur = src2; *cur != '\0'; cur++, i++) {
		  ret = enqueue(*cur);
		  if (ret == -1) {
			printf("full.\n");
			break;
		  }
	    }
        printf("Dequeue2:\n");
	    for (j = 0; j < i; j++) {
		  ret = dequeue();
		  if (ret == QUEUEEMPTY) {
			printf("empty.\n");
			break;
		  }
		  dest[j] = ret;
	    }
	    dest[j] = '\0';
        printf("Result2:\n");
	    printf("%s\n", dest);
      }

      return 0;
}
