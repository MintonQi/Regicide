#ifndef UTILITY_H
#define UTILITY_H

#include "struct.h"

void shuffle(void *arr, int size);
void printCard(struct card *cards, int start, int end);
void addCardsToDeck(struct deque *q, struct card *cards, int n);
void hireFromDeck(struct deque *q, struct card *cards, int n, int *playerCardsNum);
void displayPlayerCards(struct card *cards);
#endif