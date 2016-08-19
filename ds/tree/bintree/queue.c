#include <stdlib.h>
#include <string.h>

#include "llist.h"
#include "queue.h"

QUEUE *queue_creat(int size)
{
      QUEUE *new;

      new = llist_creat(size);

      return new;
}

void queue_destroy(QUEUE *queue)
{
      llist_destroy(queue);
}

int queue_en(QUEUE *queue, void *data)
{
      return llist_prepend(queue, data);
}

static int _zero(const void *p1, const void *p2)
{
      return 0;
}

int queue_de(QUEUE *queue, void *data)
{
      void *ptr;

      ptr = llist_fetch(queue, NULL, _zero, LLIST_BACKWARD);
      if (ptr == NULL) {
	    return -1;
      }

      memcpy(data, ptr, queue->size);
      free(ptr);
      return 0;
}

int queue_isempty(QUEUE *queue)
{
      void *ptr;

      ptr = llist_find(queue, NULL, _zero, LLIST_FORWARD);
      if (ptr == NULL) {
	    return 1;
      }

      return 0;
}



