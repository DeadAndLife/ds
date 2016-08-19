#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darr.h"

struct darr_node_st {
      int size;
      int num;
      void *arr;
};

DARR *darr_creat(int size)
{
      struct darr_node_st *new;

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
      struct darr_node_st *p = ptr;

      free(p->arr);
      free(p);
}

int darr_append(DARR *ptr, void *data)
{
      void *tmp;
      struct darr_node_st *p = ptr;

      tmp = realloc(p->arr, p->num * p->size + p->size);
      if (tmp == NULL) {
	    return -1;
      }

      p->arr = tmp;
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

      tmp = realloc(p->arr, p->num * p->size + p->size);
      if (tmp == NULL) {
	    return -1;
      }

      p->arr = tmp;
      memmove((char *)p->arr + p->size * (ind + 1), (char *)p->arr + p->size * ind, (p->num - ind) * p->size);
      memcpy((char *)p->arr + p->size * ind, data, p->size);
      p->num++;

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

int darr_read(DARR **ptr, const char *path)
{
      FILE *fp;
      int ret, num, size;
      struct darr_node_st *p;

      fp = fopen(path, "r");
      if (fp == NULL) {
	    return -1;
      }

      *ptr = malloc(sizeof(struct darr_node_st));
      if (*ptr == NULL) {
	    fclose(fp);
	    return -1;
      }
      p = *ptr;

      ret = fread(p, sizeof(struct darr_node_st), 1, fp);
      if (ret == 0) {
	    free(p);
	    *ptr = NULL;
	    fclose(fp);
	    return -1;
      }

      size = p->size;
      num = p->num;
      p->arr = malloc(size * num);
      if (p->arr == NULL) {
	    if (num == 0) {
		  fclose(fp);
		  return 0;
	    }
	    free(p);
	    *ptr = NULL;
	    fclose(fp);
	    return -1;
      }

      do {
	    ret = fread((char *)p->arr + size * (p->num - num), size, num, fp);
	    if ((ret < num) && ferror(fp)) {
		  free(p->arr);
		  free(p);
		  *ptr = NULL;
		  fclose(fp);
		  return -1;
	    }
      } while (num -= ret);

      fclose(fp);
      return 0;
}

int darr_write(const DARR *ptr, const char *path)
{
      FILE *fp;
      int ret, num;
      const struct darr_node_st *p = ptr;

      fp = fopen(path, "w");
      if (fp == NULL) {
	    return -1;
      }

      ret = fwrite(p, sizeof(struct darr_node_st), 1, fp);
      if (ret == 0) {
	    fclose(fp);
	    return -1;
      }

      num = p->num;
      do {
	    ret = fwrite((char *)p->arr + p->size * (p->num - num), p->size, num, fp);
	    if ((ret < num) && ferror(fp)) {
		  fclose(fp);
		  return -1;
	    }
      } while (num -= ret);

      fclose(fp);
      return 0;
}


