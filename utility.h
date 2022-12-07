#ifndef UTILITY_H
#define UTILITY_H

#include "struct.h"

void shuffle(void *arr, int size);
void printCard(card *cards, int start, int end);
void castleDeck(card *enemies_cards, enemy *enemies);
void addCardsToDeck(deque *deck, card *cards, int n);
void rearrangeCards(card *cards);
int  min(int a, int b);
int  max(int a, int b);
void hireFromDeck(deque *deck, card *hand, int n, int *handNum);
void healFromDiscard(deque *deck, card *discard, int n, int *discardNum);
void displayHand(card *cards, int handNum);
void displayEnemy(enemy currentEnemy);
int  getValidInput(card *hand, int *handNum, card *buffer, int *bufferNum);
void activateRedSuitPower(card *hand, int *handNum, card *buffer, int bufferNum,enemy currentEnemy,
                          int inputNum, card *discard, int *discardNum, deque *deck);
int  attackEnemy(enemy *currentEnemy, card *buffer, int bufferNum, int inputNum, card *hand);
void killEnemy(card *buffer, int *bufferNum, card *discard, int *discardNum,
               enemy currentEnemy, int *enemyIndex, deque *deck, int status);
int sufferDamage(card *hand, int *handNum, card *buffer,
                     int *bufferNum, enemy currentEnemy);
void useJokerPower(card *hand, int *handNum, card *buffer,
                   int *bufferNum, deque *deck, int *jokerNum);
#endif