#ifndef UTILITY_H
#define UTILITY_H

#include "struct.h"

void shuffle(void *arr, int size);
void printCard(struct card *cards, int start, int end);
void castleDeck(struct card *enemies_cards, struct enemy *enemies);
void addCardsToDeck(struct deque *deck, struct card *cards, int n);
void rearrangeCards(struct card *cards);
int min(int a, int b);
void hireFromDeck(struct deque *deck, struct card *hand, int n, int *handNum);
void healFromDiscard(struct deque *deck, struct card *discard, int n, int *discardNum);
void displayHand(struct card *cards, int handNum);
void displayEnemy(struct enemy currentEnemy);
int getValidInput(struct card *hand, int *validInput);

#endif