#include <stdlib.h>
#include <string.h>

#include "llist.h"
#include "stack.h"

STACK *stack_creat(int size)
{
      STACK *new;

      new = llist_creat(size);

      return new;
}

void stack_destroy(STACK *stack)
{
      llist_destroy(stack);
}

int stack_push(STACK *stack, void *data)
{
      return llist_prepend(stack, data);
}

static int _zero(const void *p1, const void *p2)
{
      return 0;
}

int stack_pop(STACK *stack, void *data)
{
      void *ptr;

      ptr = llist_fetch(stack, NULL, _zero, LLIST_FORWARD);
      if (ptr == NULL) {
	    return -1;
      }

      memcpy(data, ptr, stack->size);
      free(ptr);
      return 0;
}

int stack_peek(STACK *stack, void *data)
{
      void *ptr;

      ptr = llist_find(stack, NULL, _zero, LLIST_FORWARD);
      if (ptr == NULL) {
	    return -1;
      }

      memcpy(data, ptr, stack->size);
      return 0;
}

int stack_isempty(STACK *stack)
{
      void *ptr;

      ptr = llist_find(stack, NULL, _zero, LLIST_FORWARD);
      if (ptr == NULL) {
	    return 1;
      }

      return 0;
}



