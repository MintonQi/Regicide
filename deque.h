#ifndef DEQUE_H
#define DEQUE_H

#include "struct.h"

deque createDeque();
void         enqueueHead(deque *q, card e);
void         enqueueTail(deque *q, card e);
card  dequeueHead(deque *q);
#endif