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

void castleDeck(struct card *enemies_cards, struct enemy *enemies)
{
	printCard(enemies_cards, 11, 13);
	shuffle(enemies_cards, 4);
	shuffle(enemies_cards + 4, 4);
	shuffle(enemies_cards + 8, 4);

	int defaultHealth = 20;
	int defaultAttack = 10;
	for (int i = 0; i < ENEMIES_MAX; i++) {
		enemies[i].enemy_card = enemies_cards[i];
		enemies[i].health     = defaultHealth;
		enemies[i].attack     = defaultAttack;
		if ((i + 1) % 4 == 0) {
			defaultHealth += 10;
			defaultAttack += 5;
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

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void hireFromDeck(struct deque *deck, struct card *hand, int n, int *handNum)
{
	// n为试图插入的手牌数，现缩小为能够插入的手牌数
	n = min(n, deck->size);          // 如果deck牌数不足，缩小n至deck剩余牌数
	n = min(n, HAND_MAX - *handNum); // 如果手牌空间不足，缩小n至手牌剩余空间
	for (int i = 0; i < n; i++)      // 插入n张牌
		hand[i + *handNum] = dequeueHead(deck);
	*handNum += n; // 手牌数加n
}

void displayHand(struct card *cards, int handNum)
{
	printf("Hand Cards:  ");
	for (int i = 0; i < handNum; i++) // print hand cards
		printf("%7s%2s  ", cards[i].suit, cards[i].vname);
	printf("\nHand No.     ");
	for (int j = 0; j < handNum; j++) // print hand number
		printf("%9d  ", j + 1);
	printf("\n");
}

void rearrangeCards(struct card *cards)
{
	int slow = 0;
	int fast = 0;
	for (int i = 0; i < HAND_MAX; i++) {
		if (cards[i].value != 0) {
			cards[slow] = cards[i];
			slow++;
		}
		fast++;
	}
	printf("%d %d\n", slow, fast);
	for (int i = slow; i < fast; i++) {
		cards[i].value = 0;
	}
}

int *getValidInput(struct card *hand, int *validInput)
{
	printf("Choose the hand numbers you want to play:\n");
	printf("(No spaces between hand numbers, and press enter to play)\n");
	char inputNumbers[4];

	// scanf("%4[^\n]s", str); // get at most 4 characters ended by '\n'
	int cnt, isValid = 1; // isValid == 1 means input is valid
	while (1) {
		for (cnt = 0; cnt < 5; cnt++) { // Get at most 5 chars
			char c = getchar();
			if (c == '\n') {
				if (cnt == 0)
					isValid = 0;
				break;
			}
			if (cnt == 4 && c != '\n') { // The 5th char is not '\n'
				isValid = 0;
				break;
			}
			if (c < '1' || c > '8') { // invalid input
				isValid = 0;
			} else
				inputNumbers[cnt] = c;
		}

		if (isValid == 1) {
			// Check if there are repetitive numbers
			for (int i = 0; i < cnt; i++) {
				for (int j = i + 1; j < cnt; j++) {
					if (inputNumbers[i] == inputNumbers[j]) {
						isValid = 0;
						i       = cnt; // end outer loop
						break;
					}
				}
			}
		}

		if (isValid == 1) {
			// Check if the cards combo is valid
			int comboCardValues[4];
			int isSame = 1, petNum = 0; // isSame==1 means all the same
			for (int i = 0; i < cnt; i++) {
				comboCardValues[i] = hand[inputNumbers[i] - '0' - 1].value;
			}
			for (int i = 0; i < cnt; i++) {  // check if cards values are all the same
				if (comboCardValues[i] == 1) // count the number of 'A'
					petNum++;
				for (int j = i + 1; j < cnt; j++) {
					if (comboCardValues[i] != comboCardValues[j]) {
						isSame = 0;
					}
				}
			}
			if (isSame == 1) {
				if (comboCardValues[0] * cnt > 10)
					isValid = 0;
			}
			if (isSame == 0) {
				if (petNum < cnt - 1) { // if pet is not enough
					isValid = 0;
				}
			}
		}

		// The input is valid!
		if (isValid == 1) {
			for (int i = 0; i < cnt; i++) {
				validInput[i] = inputNumbers[i] - '0';
			}
			return;
		}
		if (isValid == 0) {
			printf("Invalid input! Please enter a valid combo: \n");
		}
		isValid = 1;
	}
	return validInput;
}