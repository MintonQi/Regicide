#include <stdio.h>
#include <stdlib.h>

#include "deque.h"


struct deque createDeque()
{
	struct deque q;
	q.head = q.tail = (struct Node *)malloc(sizeof(struct Node));
	// create dummy head
	q.head->data = (struct card){ "0", "0", 0 };
	q.head->next = NULL;
	q.tail       = q.head;
    q.size = 0;
	return q;
}

void enqueueHead(struct deque *q, struct card e)
{
	struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
	struct Node *h   = q->head;
	ptr->data        = e;
	ptr->prev        = h;
	ptr->next        = h->next;
	if (h->next) {
		h->next->prev = ptr;

	} else {
		q->tail = ptr;
	}
	h->next = ptr;
    q->size++;
}

void enqueueTail(struct deque *q, struct card e)
{
	struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
	ptr->data        = e;
	ptr->prev        = q->tail;
	ptr->next        = NULL;
	q->tail->next    = ptr;
	q->tail          = ptr;
    q->size++;
}

struct card dequeueHead(struct deque *q)
{
	if(q->size == 0){
		printf("Empty deque!!! Cannot dequeueHead!");
	}
	struct Node *h = q->head;
	struct card  e = h->next->data;
	if (h->next->next) {
		h->next->next->prev = h;
		h->next             = h->next->next;
	} else {
		h->next = NULL;
		q->tail = h;
	}
    q->size--;
	return e;
}


