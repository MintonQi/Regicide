#ifndef STRUCT_H
#define STRUCT_H

struct card {
	char *suit;
	char *vname;
	int   value;
};

struct Node {
	struct card  data;
	struct Node *next;
	struct Node *prev;
};

struct deque {
	struct Node *head;
	struct Node *tail;
	int size;
};

#endif