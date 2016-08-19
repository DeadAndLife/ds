#include "llist.h"

STACK *stack_creat(int size)
{
      STACK *new;

      new = malloc(sizeof(STACK));
      if (new == NULL) {
	    return NULL;
      }

      new->size = size;
      new->list = llist_creat(size);
      if (new->list == NULL) {
	    free(new);
	    return NULL;
      }

      return new;
}

void stack_destroy(STACK *stack)
{
      llist_destroy(stack->list);
      free(stack);
}

int stack_push(STACK *stack, void *data)
{
      return llist_prepend(stack->list, data);
}

static int _zero(const void *p1, const void *p2)
{
      return 0;
}

int stack_pop(STACK *stack, void *data)
{
      void *ptr;

      ptr = llist_fetch(stack->list, NULL, _zero, LLIST_FORWARD);
      if (ptr == NULL) {
	    return -1;
      }

      memcpy(data, ptr, stack->size);
      free(ptr);
      return 0;
}



