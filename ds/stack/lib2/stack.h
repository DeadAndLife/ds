#ifndef YM_STACK_H
#define YM_STACK_H

#include "llist.h"

typedef LLIST STACK;

STACK *stack_creat(int size);

void stack_destroy(STACK *);

int stack_push(STACK *, void *);

int stack_pop(STACK *, void *);

int stack_peek(STACK *, void *);

int stack_isempty(STACK *);

#endif
