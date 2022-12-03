#ifndef STRUCT_H
#define STRUCT_H

#define HAND_MAX 8
#define ENEMIES_MAX 12
#define SOLDIERS_MAX 40
#define INPUT_MAX 4

typedef struct {
	char *suit;
	char *vname;
	int   value;
} card;

typedef struct node{
	card data;
	struct node *next;
	struct node *prev;
} node;

typedef struct {
	node *head;
	node *tail;
	int size;
} deque;

typedef struct{
	card enemy_card;
	int health;
	int attack;
} enemy;
#endif