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
void addCardsToDeck(struct deque *deck, struct card *cards, int n)
{
	for (int i = 0; i < n; i++) {
		enqueueTail(deck, cards[i]);
	}
}

int min(int a, int b){
	if(a < b) 
		return a;
	else 
		return b;
}

void hireFromDeck(struct deque *deck, struct card *hand, int n, int *handNum)
{
	// n为试图插入的手牌数，现缩小为能够插入的手牌数
	n = min(n, deck->size);// 如果deck牌数不足，缩小n至deck剩余牌数
	n = min(n, HAND_MAX - *handNum); // 如果手牌空间不足，缩小n至手牌剩余空间
	for (int i = 0; i < n; i++) // 插入n张牌
		hand[i + *handNum] = dequeueHead(deck);
	*handNum += n; // 手牌数加n
}

void displayHand(struct card *cards){
	int cnt = 0;
	printf("Hand Cards:  ");
	for (int i = 0; i < HAND_MAX; i++){
		if(cards[i].value == 0)
			break;
		printf("%7s%2s  ", cards[i].suit, cards[i].vname);
		cnt++;
	}
	printf("\nHand No.     ");
	for(int j = 0; j < cnt; j++){
		printf("%9d  ", j + 1);
	}
}

struct card *getValidInput(struct card *hand){
	printf("Choose the card numbers you want to play.\n");
	printf("(Without spaces between card numbers, and press enter to play.\n");
	char str[4];
	struct card *validInput[4];
	scanf("%4[^\n]s", str);

}


struct card *playCards(){
	
}
