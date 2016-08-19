#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "darr.h"
#include "debug.h"

#define DARR_REALLOC_NUM 10

struct darr_node_st {
      int size;
      int num;
      int max;
      void *arr;
};

DARR *darr_creat(int size)
{
      struct darr_node_st *new;

      myprintf1("in darr_creat(), debug1.\n");

      myprintf3("in darr_creat(), debug3.\n");

      new = malloc(sizeof(struct darr_node_st));
      if (new == NULL) {
	    return NULL;
      }

      new->size = size;
      new->num = 0;
      new->max = 0;
      new->arr = NULL;

      return new;
}

void darr_destroy(DARR *ptr)
{
      struct darr_node_st *p = ptr;

      free(p->arr);
      free(p);
}

int darr_append(DARR *ptr, void *data)
{
      void *tmp;
      struct darr_node_st *p = ptr;

      if (p->num == p->max) {
	    tmp = realloc(p->arr, (p->num + DARR_REALLOC_NUM) * p->size);
	    if (tmp == NULL) {
		  return -1;
	    }
	    p->arr = tmp;
	    p->max += DARR_REALLOC_NUM;
      }

      memcpy((char *)p->arr + p->size * p->num, data, p->size);
      p->num++;
      

      return 0;
}

void *darr_ind(DARR *ptr, int ind)
{
      struct darr_node_st *p = ptr;

      return (char *)p->arr + p->size * ind;
}

int darr_insert(DARR *ptr, void *data, int ind)
{
      void *tmp;
      struct darr_node_st *p = ptr;

      if (p->num == p->max) {
	    tmp = realloc(p->arr, (p->num + DARR_REALLOC_NUM) * p->size);
	    if (tmp == NULL) {
		  return -1;
	    }
	    p->arr = tmp;
      }

      memmove((char *)p->arr + p->size * (ind + 1), (char *)p->arr + p->size * ind, (p->num - ind) * p->size);
      memcpy((char *)p->arr + p->size * ind, data, p->size);
      p->num++;
      p->max += DARR_REALLOC_NUM;
      return 0;
}

int darr_delet(DARR *, int ind);

int darr_find(DARR *ptr, void *key, DARR_CMP *func)
{
      int i;
      struct darr_node_st *p = ptr;

      for (i = 0; i < p->num; i++) {
	    if (!func(darr_ind(p, i), key)) {
		  return i;
	    }
      }

      return -1;
}

void darr_travel(DARR *ptr, DARR_OP *func)
{
      int i;
      struct darr_node_st *p = ptr;

      for (i = 0; i < p->num; i++) {
	    func(darr_ind(p, i));
      }
}



