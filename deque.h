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
void enqueueHead(struct deque *q, struct card e);
#endif