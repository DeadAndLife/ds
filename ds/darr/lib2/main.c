#include <stdio.h>
#include <string.h>

#include "darr.h"

#define NAMESIZE 32

struct score {
      char name[NAMESIZE];
      int chinese;
      int math;
};

int name_comp(const void *p1, const void *p2)
{
      const struct score *data = p1;
      const char *key = p2;

      return strcmp(data->name, key);
}

void print_score(void *ptr)
{
      struct score *data = ptr;

      printf("%s, %d, %d\n", data->name, data->chinese, data->math);
}

int main(void)
{
      struct score tmp, *p;
      DARR *arr, *new;
      int i, ret;

      arr = darr_creat(sizeof(struct score));
      for (i = 0; i < 6; i++) {
	    tmp.chinese = i;
	    tmp.math = i * i;
	    snprintf(tmp.name, NAMESIZE, "stu%d", i);
	    darr_append(arr, &tmp);
      }
      printf("Travel:\n");
      darr_travel(arr, print_score);
      printf("Write to file<tmp>\n");
      ret = darr_write(arr, "tmp");
      if (ret) {
	    perror("darr_write()");
	    return 1;
      }
      darr_destroy(arr);

      putchar('\n');

      ret = darr_read(&new, "tmp");
      if (ret) {
            perror("darr_read()");
            return 1;
      }
      printf("Read from file<tmp> and travel\n");
      darr_travel(new, print_score);
      darr_destroy(new);

      return 0;
}
