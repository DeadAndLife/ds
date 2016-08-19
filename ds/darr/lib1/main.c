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
      DARR *arr;
      int i, ret;

      arr = darr_creat(sizeof(struct score));
      for (i = 0; i < 6; i++) {
	    tmp.chinese = i;
	    tmp.math = i * i;
	    snprintf(tmp.name, NAMESIZE, "stu%d", i);
	    darr_append(arr, &tmp);
      }

      tmp.chinese = i;
      tmp.math = i * i;
      snprintf(tmp.name, NAMESIZE, "stu%d", i);
      darr_insert(arr, &tmp, 3);

      printf("Travel:\n");
      darr_travel(arr, print_score);

      printf("Find:\n");
      ret = darr_find(arr, "stu6", name_comp);
      if (ret == -1) {
	    printf("no finded.\n");
      } else {
	    p = darr_ind(arr, ret);
	    printf("%s, %d, %d\n", p->name, p->chinese, p->math);
      }

      darr_destroy(arr);
      return 0;
}
