#ifndef YM_LLIST_H
#define YM_LLIST_H

struct llist_node_st {
      void *data;
      struct llist_node_st *pre;
      struct llist_node_st *next;
};

typedef struct llist_head {
      int size;
      struct llist_node_st head;
} LLIST;

#define LLIST_FORWARD    0
#define LLIST_BACKWARD   1

typedef void LLIST_OP(void *);
typedef int LLIST_CMP(const void *, const void *);

LLIST *llist_creat(int size);

void llist_destroy(LLIST *);

int llist_prepend(LLIST *, void *);

void llist_travel(LLIST *, LLIST_OP *);

void *llist_find(LLIST *, void *key, LLIST_CMP *, int mode);

void llist_delet(LLIST *, void *key, LLIST_CMP *);

void *llist_fetch(LLIST *, void *key, LLIST_CMP *, int mode);

#endif
