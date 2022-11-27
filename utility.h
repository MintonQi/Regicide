#ifndef UTILITY_H
#define UTILITY_H

#include "struct.h"

void shuffle(void *arr, int size);
void printCard(struct card *cards, int start, int end);
void addCardsToDeck(struct deque *deck, struct card *cards, int n);
int min(int a, int b);
void hireFromDeck(struct deque *deck, struct card *cards, int n, int *handNum);
void displayHand(struct card *cards, int handNum);
struct card *getValidInput(struct card *hand, struct card *validInput);
struct card *playCards();
#endif