#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "deque.h"


struct deque createDeque()
{
	struct deque q;
	q.head = q.tail = (struct Node *)malloc(sizeof(struct Node));
	q.head->data    = (struct card){ "0", "0", 0 };
	q.head->next    = NULL;
	q.tail->next    = NULL;
    return q;
}

void enqueueHead(struct deque *q, struct card e){
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = e;
    ptr->prev = q->head;
    ptr->next = q->head->next;
    q->head->next->prev = ptr;
    q->head->next = ptr;
}

void enqueueTail(struct deque *q, struct card e){
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
}
