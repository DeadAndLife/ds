#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "llist.h"

#if 0
struct llist_node_st {
      void *data
      struct llist_node_st *pre;
      struct llist_node_st *next;
};
typedef struct llist_head {
      int size;
      struct llist_node_st head;
} LLIST;
typedef void LLIST_OP(void *);
#endif

LLIST *llist_creat(int size)
{
      LLIST *new = NULL;

      new = malloc(sizeof(LLIST));
      if(new == NULL){
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

      for(tmp = list->head.next;tmp != &list->head; tmp = save){
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
      if(newnode == NULL){
	    return -1;
      }
      newnode->data = malloc(list->size);
      if(newnode->data == NULL){
	    free(newnode);
	    return -1;
      }
      memcpy(newnode->data, data, list->size);

      newnode->pre = &list->head;
      newnode->next = list->head.next;

      newnode->pre->next = newnode;
      newnode->next->pre = newnode;



      return 0;
}

void llist_travel(LLIST *list, LLIST_OP *op)
{
      struct llist_node_st *tmp;

      for(tmp = list->head.next;tmp != &list->head; tmp = tmp->next){
	    op(tmp->data);
      }
}

static struct llist_node_st *_find(LLIST *list, void *key, LLIST_CMP *cmp)
{
      struct llist_node_st *tmp;

      for(tmp = list->head.next;tmp != &list->head; tmp = tmp->next){
            if(!cmp(tmp->data, key)){
		  break;
	    }
      }
      return tmp;

}

void *llist_find(LLIST *list, void *key, LLIST_CMP *cmp)
{
      return _find(list, key, cmp)->data;
}

void llist_delete(LLIST *list, void *key, LLIST_CMP *cmp)
{
      struct llist_node_st *tmp;
      tmp = _find(list, key, cmp);
      if(tmp != &list->head){
	    tmp->next->pre = tmp->pre;
	    tmp->pre->next = tmp->next;
	    free(tmp->data);
	    free(tmp);
      }
}




