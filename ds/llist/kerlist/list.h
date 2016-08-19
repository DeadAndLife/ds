#ifndef YM_KERLIST_H
#define YM_KERLIST_H

struct list_head {
      struct list_head *next, *prev;
};

#define INIT_LIST_HEAD(list) ({			\
		  (list)->next = (list);	\
		  (list)->prev = (list); })

#define __list_add(new, prenode, nextnode) ({		\
		  (nextnode)->prev = new;		\
		  new->next = (nextnode);		\
		  new->prev = (prenode);		\
		  (prenode)->next = new; })

#define list_add(new, head) ({	\
		  __list_add((new), (head), (head)->next); })	\

#define __list_del(prenode, nextnode) ({		\
		  (nextnode)->prev = (prenode);		\
		  (prenode)->next = (nextnode); })

#define list_del_init(entry) ({				\
		  __list_del((entry)->prev, (entry)->next);	\
		  INIT_LIST_HEAD((entry)); })

#define list_for_each(pos, head)				\
      for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)

#define container_of(ptr, type, member) ({				\
		  const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
		  (type *)( (char *)__mptr - offsetof(type,member) );})

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif
