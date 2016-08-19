#ifndef YM_STACK_H
#define YM_STACK_H

typedef struct {
      int size;
      LLIST *list;
} STACK;

STACK *stack_creat(int size);

void stack_destroy(STACK *);

int stack_push(STACK *, void *);

int stack_pop(STACK *, void *);

#endif
