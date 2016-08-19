#include <stdlib.h>
#include <string.h>

#include "../include/llist.h"

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

int llist_append(LLIST *list, void *data)
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

      newnode->pre = list->head.pre;
      newnode->next = &list->head;

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

static struct llist_node_st *_find(LLIST *list, void *key, LLIST_CMP *cmp)
{
      struct llist_node_st *tmp;

      for (tmp = list->head.next; tmp != &list->head; tmp = tmp->next) {
	    if (!cmp(tmp->data, key)) {
		  break;
	    }
      }

      return tmp;
}

void *llist_find(LLIST *list, void *key, LLIST_CMP *cmp)
{
      return _find(list, key, cmp)->data;
}

void llist_delet(LLIST *list, void *key, LLIST_CMP *cmp)
{
      struct llist_node_st *tmp;

      tmp = _find(list, key, cmp);
      if (tmp != &list->head) {
	    tmp->next->pre = tmp->pre;
	    tmp->pre->next = tmp->next;
	    free(tmp->data);
	    free(tmp);
      }
}

static int _get_num(LLIST *list)
{
      int i;
      struct llist_node_st *pos;

      for (i = 0, pos = list->head.next; pos != &list->head; pos = pos->next, i++)
	    ;

      return i;
}

void llist_save(LLIST *list, FILE *fp)
{
      struct llist_node_st *tmp;
      int num = _get_num(list);
      int size = list->size;

      fwrite(&num, sizeof(num), 1, fp);
      fwrite(&size, sizeof(size), 1, fp);

      for (tmp = list->head.next; tmp != &list->head; tmp = tmp->next) {
	    fwrite(tmp->data, list->size, 1, fp);
      }
}

LLIST *llist_load(FILE *fp)
{
      int num, size;
      LLIST *new;
      void *data;
      int i;

      fread(&num, sizeof(num), 1, fp);
      fread(&size, sizeof(size), 1, fp);

      data = malloc(size);
      new = llist_creat(size);
      for (i = 0; i < num; i++) {
	    fread(data, size, 1, fp);
	    llist_append(new, data);
      }

      return new;
}


