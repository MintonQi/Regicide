#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utility.h"
#include "deque.h"

char *vnames[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
char *suits[]  = { "Spade", "Club", "Heart", "Diamond" };

//洗牌  1. 敌人队列  2. 弃牌堆
void shuffle(void *arr, int size)
{
	struct card *cards = (struct card *)arr;

	for (int i = 0; i < size; i++) {
		int         j    = rand() % size;
		struct card temp = cards[j];
		cards[j]         = cards[i];
		cards[i]         = temp;
	}
}

void printCard(struct card *cards, int start, int end)
{
	int count = 0;
	for (int i = start; i <= end; i++) {
		for (int j = 0; j < 4; j++) {
			cards[count].suit  = suits[j];
			cards[count].value = i;
			cards[count].vname = vnames[i - 1];
			count++;
		}
	}
}

//从牌堆底部加入
// 1. 初始化牌堆  2.从弃牌堆heal
void addCardsToDeck(struct deque *q, struct card *cards, int n)
{
	for (int i = 0; i < n; i++) {
		enqueueTail(q, cards[i]);
	}
}

void hireFromDeck(struct deque *q, struct card *cards, int n, int *playerCardsNum)
{
	//n为可以插入的手牌数量
	if (PLAYER_MAX - *playerCardsNum < n) {
		n = PLAYER_MAX - *playerCardsNum;
	}
	for (int i = 0; i < PLAYER_MAX; i++) {
		if (cards[i].value == 0) {
			cards[i] = dequeueHead(q);
			(*playerCardsNum)++;
			n--;
			if(n == 0) break;
		}
	}
}

void displayPlayerCards(struct card *cards){
	for (int i = 0; i < PLAYER_MAX; i++)
		if(cards[i].value != 0) {
			printf("%s %s\n", cards[i].suit, cards[i].vname);
		}
}
