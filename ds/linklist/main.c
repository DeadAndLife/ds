#include <stdio.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE 32

struct score {
      char name[NAMESIZE];
      int chinese;
      int math;
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
      struct score tmp, *p;
      int i;
      LLIST *list;
//CREAT
      list = llist_creat(sizeof(struct score));

      for(i = 0; i < 6;i++){
	    tmp.chinese = i;
	    tmp.math = i * i;
	    snprintf(tmp.name, NAMESIZE, "stu%d",i);
	    llist_prepend(list, &tmp);
      }

//TRAVEL
      printf("Travel:\n");
      llist_travel(list, print_score);
//FIND
      printf("Find stu3:\n");
      p = llist_find(list, "stu3", name_cmp);
      if(p != NULL){
	    printf("\n%s, %d, %d\n",p->name, p->chinese, p->math);
      }
//DELETE
      printf("\n");
      printf("Delete stu4:\n");
      llist_delete(list, "stu4", name_cmp);
//TRAVEL
      printf("Travel:\n");
      llist_travel(list, print_score);
  
//DESTROY    
      llist_destroy(list);

      return 0;
}



