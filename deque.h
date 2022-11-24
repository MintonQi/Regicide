#ifndef DEQUE_H
#define DEQUE_H
#include "utility.h"
struct Node {
	struct card  data;
	struct Node *next;
	struct Node *prev;
};

struct deque {
	struct Node *head;
	struct Node *tail;
};
struct deque createDeque();
void         enqueueHead(struct deque *q, struct card e);
void         enqueueTail(struct deque *q, struct card e);
struct card  dequeueHead(struct deque *q);
int          getSize(struct deque *q);
#endif