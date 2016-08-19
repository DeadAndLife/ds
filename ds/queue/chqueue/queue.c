#include <stdio.h>

#include "queue.h"

#define QUEUESIZE 8

static char q[QUEUESIZE];
static int enq;
static int deq;

// 请同学们思考，该算法是否可以优化？
static int _is_full(void)
{   /*
      if (enq == deq - 1) {
	    return 1;
      }
      if (deq == 0 && enq == QUEUESIZE - 1) {
	    return 1;
      }
      */
    if (enq == ((deq + QUEUESIZE) - 1) % QUEUESIZE) {
        return 1;
    }
      return 0;
}

static int _is_empty(void)
{
      if (enq == deq) {
	    return 1;
      }
      return 0;
}

int enqueue(int c)
{
      // 1. 队列是否满
      if (_is_full()) {
	    return -1;
      }
      // 请同学们思考，该算法是否可以优化？
      /*
      q[enq++] = c;

      if (enq >= QUEUESIZE) {
	    enq = 0;
      }
      */

      // 2. 入队
      q[enq] = c;

      // 3. 更新enq值
      enq = (enq + 1) % QUEUESIZE;

      return 0;
}

int dequeue(void)
{
      int ret;
      // 1. 队里是否为空
      if (_is_empty()) {
	    return QUEUEEMPTY;
      }
      /*
      ret = q[deq++];
      if (deq >= QUEUESIZE) {
	    deq = 0;
      }
      */

      // 2. 出队
      ret = q[deq];
      
      // 3. 更新deq值
      deq = (deq + 1) % QUEUESIZE;

      return ret;
}


