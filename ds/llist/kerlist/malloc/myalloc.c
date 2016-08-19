#include "list.h"
#include "myalloc.h"

#define MAXSIZE 8192
#define REVERSE (sizeof(void *) + 32)
struct ym_mem_st {
      struct list_head head;
      void *end;
      char buf[0];
};

static char _mem[MAXSIZE];
static int _is_init = 0;
static struct ym_mem_st *_head;

static size_t _get_size(struct ym_mem_st *node)
{
      return (char *)node->end - (char *)node;
}

static void _init(void)
{
      struct ym_mem_st *new;
      _head = (struct ym_mem_st *)_mem;

      INIT_LIST_HEAD(&_head->head);
      _head->end = _head + 1;

      new = _head + 1;
      INIT_LIST_HEAD(&new->head);
      new->end = _mem + MAXSIZE;
      list_add(&new->head, &_head->head);
      _is_init = 1;
}

static struct ym_mem_st *_find(size_t size)
{
      struct ym_mem_st *pos;
      struct list_head *tmp;

      list_for_each(tmp, &_head->head) {
	    pos = container_of(tmp, struct ym_mem_st, head);
	    if (_get_size(pos) >= size + sizeof(void *)) {
		  return pos;
	    }
      }

      return NULL;
}

static void *_get_mem(struct ym_mem_st *node, size_t size)
{
      void **ret;

      if (_get_size(node) >= size + REVERSE) {
	    ret = node->end - (size + sizeof(void *));
	    *ret = node->end;
	    node->end = ret;
      } else {
	    __list_del(node->head.prev, node->head.next);
	    ret = (void **)node;
	    *ret = node->end;
      }

      return ret + 1;
}

void *myalloc(size_t size)
{
      struct ym_mem_st *min;

      if (!_is_init) {
	    _init();
      }

      min = _find(size);
      return _get_mem(min, size);
}

void myfree(void *ptr)
{
      struct ym_mem_st *pos;
      struct list_head *tmp;
      void **p = ptr;

      p--;
      list_for_each(tmp, &_head->head) {
	    pos = container_of(tmp, struct ym_mem_st, head);
	    if (pos->end == (void *)p) {
		  pos->end = *p;
		  return;
	    }
      }

      p = ptr;
      p--;
      pos = (struct ym_mem_st *)p;
      //pos = ptr;
      //p = ptr;
      pos->end = *p;
      INIT_LIST_HEAD(&pos->head);
      list_add(&pos->head, &_head->head);
}


