#include <stdlib.h>
#include <string.h>

#include "darr.h"

#if 0
typedef struct darr_node_st {
      int size;
      int num;
      void *arr;
} DARR;
#endif

DARR *darr_creat(int size)
{
      DARR *new = NULL;

      new = malloc(sizeof(struct darr_node_st));
      if (new == NULL) {
	    return NULL;
      }

      new->size = size;
      new->num = 0;
      new->arr = NULL;

      return new;
}

void darr_destroy(DARR *ptr)
{
      free(ptr->arr);
      free(ptr);
}

int darr_append(DARR *ptr, void *data)
{
      void *tmp;

      tmp = realloc(ptr->arr, ptr->num * ptr->size + ptr->size);
      if (tmp == NULL) {
	    return -1;
      }

      ptr->arr = tmp;
      memcpy((char *)ptr->arr + ptr->size * ptr->num, data, ptr->size);
      ptr->num++;

      return 0;
}

void *darr_ind(DARR *ptr, int ind)
{
      return (char *)ptr->arr + ptr->size * ind;
}

int darr_insert(DARR *ptr, void *data, int ind)
{
      void *tmp;

      tmp = realloc(ptr->arr, ptr->num * ptr->size + ptr->size);
      if (tmp == NULL) {
	    return -1;
      }

      ptr->arr = tmp;
      memmove((char *)ptr->arr + ptr->size * (ind + 1), (char *)ptr->arr + ptr->size * ind, (ptr->num - ind) * ptr->size);
      memcpy((char *)ptr->arr + ptr->size * ind, data, ptr->size);
      ptr->num++;

      return 0;
}

int darr_delet(DARR *, int ind);

int darr_find(DARR *ptr, void *key, DARR_CMP *func)
{
      int i;

      for (i = 0; i < ptr->num; i++) {
	    if (!func(darr_ind(ptr, i), key)) {
		  return i;
	    }
      }

      return -1;
}

void darr_travel(DARR *ptr, DARR_OP *func)
{
      int i;

      for (i = 0; i < ptr->num; i++) {
	    func(darr_ind(ptr, i));
      }
}



