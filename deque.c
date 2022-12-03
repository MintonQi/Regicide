#include <stdio.h>
#include <stdlib.h>

#include "deque.h"


deque createDeque()
{
	deque q;
	q.head = q.tail = (node *)malloc(sizeof(node));
	// create dummy head
	q.head->data = (card){ "0", "0", 0 };
	q.head->next = NULL;
	q.tail       = q.head;
    q.size = 0;
	return q;
}

void enqueueHead(deque *q, card e)
{
	node *ptr = (node *)malloc(sizeof(node));
	node *h   = q->head;
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

void enqueueTail(deque *q, card e)
{
	node *ptr = (node *)malloc(sizeof(node));
	ptr->data        = e;
	ptr->prev        = q->tail;
	ptr->next        = NULL;
	q->tail->next    = ptr;
	q->tail          = ptr;
    q->size++;
}

card dequeueHead(deque *q)
{
	if(q->size == 0){
		printf("Empty deque!!! Cannot dequeueHead!");
	}
	node *h = q->head;
	card  e = h->next->data;
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

