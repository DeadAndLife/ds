#ifndef YM_DARR_H
#define YM_DARR_H

typedef struct darr_node_st {
      int size;
      int num;
      void *arr;
} DARR;

typedef int DARR_CMP(const void *, const void *);
typedef void DARR_OP(void *);

DARR *darr_creat(int size);

void darr_destroy(DARR *);

int darr_append(DARR *, void *);

void *darr_ind(DARR *, int ind);

int darr_insert(DARR *, void *, int ind);

int darr_delet(DARR *, int ind);

int darr_find(DARR *, void *key, DARR_CMP *func);

void darr_travel(DARR *, DARR_OP *func);

#endif
