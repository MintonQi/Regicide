#ifndef STRUCT_H
#define STRUCT_H

#define HAND_MAX 8
#define ENEMIES_MAX 12
#define SOLDIERS_MAX 40

struct card {
	char *suit;
	char *vname;
	int   value;
};

struct enemy {
	int atk;
	int hp;
	char *suit;
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