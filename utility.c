#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "utility.h"
#include "deque.h"

char *vnames[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
char *suits[]  = { "Spade", "Club", "Heart", "Diamond" };

//洗牌  1. 敌人队列  2. 弃牌堆
void shuffle(void *arr, int size)
{
	card *cards = (card *)arr;

	for (int i = 0; i < size; i++) {
		int  j    = rand() % size;
		card temp = cards[j];
		cards[j]  = cards[i];
		cards[i]  = temp;
	}
}

void printCard(card *cards, int start, int end)
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

void castleDeck(card *enemies_cards, enemy *enemies)
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
void addCardsToDeck(deque *deck, card *cards, int n)
{
	for (int i = 0; i < n; i++) {
		enqueueTail(deck, cards[i]);
	}
}

void rearrangeCards(card *cards)
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
	for (int i = slow; i < fast; i++) {
		cards[i].value = 0;
	}
}

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void hireFromDeck(deque *deck, card *hand, int n, int *handNum)
{
	// n为试图插入的手牌数，现缩小为能够插入的手牌数
	n = min(n, deck->size);          // 如果deck牌数不足，缩小n至deck剩余牌数
	n = min(n, HAND_MAX - *handNum); // 如果手牌空间不足，缩小n至手牌剩余空间
	for (int i = 0; i < n; i++)      // 插入n张牌
		hand[i + *handNum] = dequeueHead(deck);
	*handNum += n; // 手牌数加n
}

void healFromDiscard(deque *deck, card *discard, int n, int *discardNum)
{
	shuffle(discard, *discardNum); // 洗弃牌堆
	n = min(n, *discardNum);       // n为能heal的牌数

	for (int i = 0; i < n; i++) { // 将牌插入牌堆底部 之后被设为0
		enqueueTail(deck, discard[i]);
		discard[i].value = 0;
		(*discardNum)--;
	}
	printf("%d\n", *discardNum);
	rearrangeCards(discard);
}

void displayHand(card *cards, int handNum)
{
	printf("Hand Cards:   ");
	for (int i = 0; i < handNum; i++) // print hand cards
		printf("%7s%2s  ", cards[i].suit, cards[i].vname);
	printf("\nHand No.      ");
	for (int j = 0; j < handNum; j++) // print hand number
		printf("%9d  ", j + 1);
	printf("\n");
}

void displayEnemy(enemy currentEnemy)
{
	printf("Current Enemy:%7s%2s\n", currentEnemy.enemy_card.suit,
	       currentEnemy.enemy_card.vname);
	printf("Attack: %d\n", currentEnemy.attack);
	printf("Health: %d\n", currentEnemy.health);
}

// 可以单张牌 可以combo但是不超过10 可以一张宠物牌+一张手牌 最多2222 四张牌
int getValidInput(card *hand, int *validInput)
{
	// initialize/reset validInput.
	for (int i = 0; i < INPUT_MAX; i++) {
		validInput[i] = 0;
	}
	printf("Choose the hand numbers you want to play:\n");
	printf("(No spaces between hand numbers, and press enter to play)\n");
	char inputNumbers[INPUT_MAX];

	while (1) {
		int isValid = 1, cnt = 0; // isValid为1 代表valid
		// 输入的index是否valid
		while (1) { // 加上'\n'最多5个字符
			char c = getchar();
			if (c == '\n') {  //  接收到回车后break
				if (cnt == 0) // 没有输入直接回车的是invalid
					isValid = 0;
				break;
			}
			if (cnt >= 5) { //  超出数量限制
				isValid = 0;
				continue;
			}
			if (c < '1' || c > '8') { // invalid input
				isValid = 0;          // 但是不能立刻break 因为要等待回车
			} else
				inputNumbers[cnt] = c;
			cnt++;
		}

		// 判断输入index是否重复
		if (isValid == 1) {
			for (int i = 0; i < cnt; i++) {
				for (int j = i + 1; j < cnt; j++) {
					if (inputNumbers[i] == inputNumbers[j]) {
						isValid = 0;
						i       = cnt; // 跳出外层循环
						break;         // 跳出内层循环
					}
				}
			}
		}

		// 判断combo是否valid 1. 连招 2. 宠物牌
		if (isValid == 1) {
			int isSame = 1, petNum = 0; // isSame==1 代表数值相同
			int comboCardValues[4];     // 最多出四张牌
			for (int i = 0; i < cnt; i++) {
				comboCardValues[i] = hand[inputNumbers[i] - '0' - 1].value;
			}
			for (int i = 0; i < cnt; i++) {
				if (comboCardValues[i] == 1) // 有宠物
					petNum++;
				for (int j = i + 1; j < cnt; j++) { // 数值是否相同
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
				if ((cnt != 2) || (petNum != 1)) {
					isValid = 0;
				}
			}
		}

		// valid input
		if (isValid == 1) {
			for (int i = 0; i < cnt; i++) {
				validInput[i] = inputNumbers[i] - '0' - 1;
			}
			return cnt;
		} else {
			printf("Invalid input! Please enter a valid combo: \n");
		}
	}
	return -1;
}

void activateRedSuitPower(card *hand, int *handNum, int *validInput, int inputNum,
                          card *discard, int *discardNum, deque *deck)
{
	int valueSum = 0, hasHeart = 0, hasDiamond = 0; // value is 1 means input has heart/diamond
	for (int i = 0; i < inputNum; i++) {            // record heart/diamond and get sum of value
		if (strcmp(hand[validInput[i]].suit, "Heart") == 0) {
			hasHeart = 1;
		} else if (strcmp(hand[validInput[i]].suit, "Diamond") == 0) {
			hasDiamond = 1;
		}
		valueSum += hand[validInput[i]].value;
	}
	if (hasHeart + hasDiamond == 0)
		return;

	// move cards
	if (hasHeart)
		healFromDiscard(deck, discard, valueSum, discardNum);
	if (hasDiamond)
		hireFromDeck(deck, hand, valueSum, handNum);
}

// return 0 if enemy is alive, 1 if overkilled, 2 if damage equal to hp
int attackEnemy(enemy *currentEnemy, int *validInput, int inputNum, card *hand)
{
	int valueSum = 0, hasClub = 0, hasSpade = 0; // value is 1 means input has heart/diamond
	for (int i = 0; i < inputNum; i++) {         // record club/spade and get sum of value
		if (strcmp(hand[validInput[i]].suit, "Heart") == 0) {
			hasClub = 1;
		} else if (strcmp(hand[validInput[i]].suit, "Diamond") == 0) {
			hasSpade = 1;
		}
		valueSum += hand[validInput[i]].value;
	}

	// deal damage and reduce atk
	if (hasClub) 
		valueSum *= 2;
	int hp = currentEnemy->health;
	if (valueSum > hp)
		return 1;
	else if (valueSum == hp)
		return 2;
	else
		currentEnemy->health -= valueSum;
	if (hasSpade)
		currentEnemy->attack = max(currentEnemy->attack - valueSum, 0);
	return 0;
}