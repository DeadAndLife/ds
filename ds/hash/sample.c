#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024
#define NAMESIZE 32

struct score {
      int id;
      char name[NAMESIZE];
      int chinese;
      int math;
};

struct score buf[BUFSIZE] = {};

int hash(int key)
{
      return key;
}

int main(void)
{
      struct score tmp;
      int i;

      for (i = 0; i < 10; i++) {
	    tmp.id = i;
	    tmp.chinese = i * i;
	    tmp.math = (i + 10) * i;
	    snprintf(tmp.name, NAMESIZE, "stu%d", i + 1);
	    buf[hash(tmp.id) % BUFSIZE] = tmp;
      }

      for (i = 0; i < 10; i++) {
	    tmp = buf[hash(i) % BUFSIZE];
	    printf("id: %d, name: %s, chinese: %d, math: %d\n", \
		   tmp.id, tmp.name, tmp.chinese, tmp.math);
      }

      return 0;
}
