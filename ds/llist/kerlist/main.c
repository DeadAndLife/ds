#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

#define NAMESIZE 32

struct score {
      char name[NAMESIZE];
      int chinese;
      int math;
      struct list_head node;
};

int name_cmp(const void *p1, const void *p2)
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
      struct score *tmp;
      int i, ret;
      struct list_head head, *p;

      INIT_LIST_HEAD(&head);

      for (i = 0; i < 6; i++) {
	    tmp = malloc(sizeof(struct score));
	    tmp->chinese = i;
	    tmp->math = i * i;
	    snprintf(tmp->name, NAMESIZE, "stu%d", i);
	    list_add(&tmp->node, &head);
      }

      list_for_each(p, &head) {
	    tmp = container_of(p, struct score, node);
	    printf("%s, %d, %d\n", tmp->name, tmp->chinese, tmp->math);
      }

      return 0;
}
