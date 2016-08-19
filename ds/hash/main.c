#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 16
#define NAMESIZE 32

struct score {
      int id;
      char name[NAMESIZE];
      int chinese;
      int math;
};

struct hash_list {
      struct score data;
      struct hash_list *next;
};

struct hash_list *buf[BUFSIZE] = {};

int hash(const char *key)
{
      int ret = 0;
      const char *p;

      for (p = key; *p != '\0'; p++) {
	    ret = (ret << 2) ^ *p;
      }

      return ret;
}

int insert(int ind, struct score *data)
{
      struct hash_list *new;

      new = malloc(sizeof(struct hash_list));
      if (0) {

      }

      new->data = *data;
      new->next = buf[ind];
      buf[ind] = new;
}

int getdata(const char *key, struct score *data)
{
      int ind;
      struct hash_list *node;

      ind = hash(key) % BUFSIZE;
      for (node = buf[ind]; node != NULL; node = node->next) {
	    if (!strcmp(node->data.name, key)) {
		  *data = node->data;
		  return ind;
	    }
      }

      return -1;
}

int main(void)
{
      struct score tmp;
      int i, ind;
      char s[NAMESIZE];

      for (i = 0; i < 10; i++) {
	    tmp.id = i;
	    tmp.chinese = i * i;
	    tmp.math = (i + 10) * i;
	    snprintf(tmp.name, NAMESIZE, "stu%d", i + 1);

	    insert(hash(tmp.name) % BUFSIZE, &tmp);
      }

      for (i = 0; i < 10; i++) {
	    snprintf(s, NAMESIZE, "stu%d", i + 1);
	    ind = getdata(s, &tmp);
	    printf("index: %d\n", ind);
	    printf("id: %d, name: %s, chinese: %d, math: %d\n", \
		   tmp.id, tmp.name, tmp.chinese, tmp.math);
      }

      return 0;
}
