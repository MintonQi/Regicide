#ifndef DEQUE_H
#define DEQUE_H

#include "struct.h"

struct deque createDeque();
void         enqueueHead(struct deque *q, struct card e);
void         enqueueTail(struct deque *q, struct card e);
struct card  dequeueHead(struct deque *q);
#endif