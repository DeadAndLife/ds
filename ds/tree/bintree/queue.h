#ifndef YM_QUEUE_H
#define YM_QUEUE_H

#include "llist.h"

typedef LLIST QUEUE;

QUEUE *queue_creat(int size);

void queue_destroy(QUEUE *);

int queue_en(QUEUE *, void *);

int queue_de(QUEUE *, void *);

int queue_isempty(QUEUE *);

#endif
