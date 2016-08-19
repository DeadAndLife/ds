#include <stdlib.h>
#include <string.h>

#include "llist.h"

LLIST *llist_creat(int size)
{
      LLIST *new;

      new = malloc(sizeof(LLIST));
      if (new == NULL) {
	    return NULL;
      }

      new->size = size;
      new->head.data = NULL;
      new->head.pre = &new->head;
      new->head.next = &new->head;

      return new;
}

void llist_destroy(LLIST *list)
{
      struct llist_node_st *tmp, *save;

      for (tmp = list->head.next; tmp != &list->head; tmp = save) {
	    save = tmp->next;
	    free(tmp->data);
	    free(tmp);
      }
      free(list);
}

int llist_prepend(LLIST *list, void *data)
{
      struct llist_node_st *newnode;

      newnode = malloc(sizeof(struct llist_node_st));
      if (newnode == NULL) {
	    return -1;
      }
      newnode->data = malloc(list->size);
      if (newnode->data == NULL) {
	    free(newnode);
	    return -1;
      }
      memcpy(newnode->data, data, list->size);

      newnode->next = list->head.next;
      newnode->pre = &list->head;

      newnode->pre->next = newnode;
      newnode->next->pre = newnode;

      return 0;
}

void llist_travel(LLIST *list, LLIST_OP *op)
{
      struct llist_node_st *tmp;

      for (tmp = list->head.next; tmp != &list->head; tmp = tmp->next) {
	    op(tmp->data);
      }
}

static struct llist_node_st *_find(LLIST *list, void *key, LLIST_CMP *cmp, int mode)
{
      struct llist_node_st *tmp;

      if (mode == LLIST_FORWARD) {
	    for (tmp = list->head.next; tmp != &list->head; tmp = tmp->next) {
		  if (!cmp(tmp->data, key)) {
			break;
		  }
	    }
      } else {
	    for (tmp = list->head.pre; tmp != &list->head; tmp = tmp->pre) {
		  if (!cmp(tmp->data, key)) {
			break;
		  }
	    }
      }

      return tmp;
}

void *llist_find(LLIST *list, void *key, LLIST_CMP *cmp, int mode)
{
      return _find(list, key, cmp, mode)->data;
}

void llist_delet(LLIST *list, void *key, LLIST_CMP *cmp)
{
      struct llist_node_st *tmp;

      tmp = _find(list, key, cmp, LLIST_FORWARD);
      if (tmp != &list->head) {
	    tmp->next->pre = tmp->pre;
	    tmp->pre->next = tmp->next;
	    free(tmp->data);
	    free(tmp);
      }
}

void *llist_fetch(LLIST *list, void *key, LLIST_CMP *cmp, int mode)
{
      struct llist_node_st *tmp;
      void *ret = NULL;

      tmp = _find(list, key, cmp, mode);
      if (tmp != &list->head) {
	    tmp->next->pre = tmp->pre;
	    tmp->pre->next = tmp->next;
	    ret = tmp->data;
	    free(tmp);
      }

      return ret;
}


