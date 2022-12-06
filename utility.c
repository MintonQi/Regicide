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

// 组建城堡牌堆 即JQK 并给它们赋予特定的value
void castleDeck(card *enemies_cards, enemy *enemies)
{
	printCard(enemies_cards, 11, 13);
	shuffle(enemies_cards, 4);
	shuffle(enemies_cards + 4, 4);
	shuffle(enemies_cards + 8, 4);

	int defaultHealth = 20;
	int defaultAttack = 10;
	for (int i = 0; i < ENEMIES_MAX; i++) {
		enemies_cards[i].value = defaultAttack; //方便归化后计算
		enemies[i].enemy_card  = enemies_cards[i];
		enemies[i].health      = defaultHealth;
		enemies[i].attack      = defaultAttack;

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

// 阶段1：获取玩家想要打出的卡牌并移入buffer 返回打出的手牌数
// 可以单张牌 可以combo但是不超过10 可以一张宠物牌+一张手牌 最多2222 四张牌
int getValidInput(card *hand, int *handNum, card *buffer, int *bufferNum)
{
	printf("Choose the hand numbers you want to play:\n");
	printf("(No spaces between hand numbers, and press enter to play)\n");
	char inputNumbers[INPUT_MAX];

	while (1) {
		int isValid = 1, cnt = 0; // isValid为1 代表valid cnt是输入的数量
		// 输入的index是否valid
		while (1) {
			char c = getchar();
			if (c == '\n') {  //  接收到回车后break
				if (cnt == 0) // 没有输入直接回车的是invalid
					isValid = 0;
				break;
			}
			if (cnt >= 5 || cnt > *handNum) { //  // 加上'\n'最多5个字符 超出数量限制or手牌数
				isValid = 0;
				continue;
			}
			if (c < '1' || c > ((*handNum) + '0')) { // invalid input
				isValid = 0;                         // 但是不能立刻break 因为要等待回车
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
			for (int i = 0; i < cnt; i++) { // hand -> buffer
				int handIndex          = inputNumbers[i] - '0' - 1;
				buffer[*bufferNum + i] = hand[handIndex];
				hand[handIndex].value  = 0;
			}
			*bufferNum += cnt;
			*handNum -= cnt;
			rearrangeCards(hand);
			return cnt;
		} else {
			printf("Invalid input! Please enter a valid combo: \n");
		}
	}
	return -1;
}

// 阶段二 激活技能
// 红牌技能
void activateRedSuitPower(card *hand, int *handNum, card *buffer, int bufferNum,
                          int inputNum, card *discard, int *discardNum, deque *deck)
{
	int valueSum = 0, hasHeart = 0, hasDiamond = 0;
	// 看有没有红色牌 并记录总数值 遍历当前buffer里刚打出去的牌
	for (int i = bufferNum - inputNum; i < bufferNum; i++) {
		if (strcmp(buffer[i].suit, "Heart") == 0) {
			hasHeart = 1;
		} else if (strcmp(buffer[i].suit, "Diamond") == 0) {
			hasDiamond = 1;
		}
		valueSum += buffer[i].value;
	}
	if (hasHeart + hasDiamond == 0)
		return;

	// 红牌技能结算
	if (hasHeart)
		healFromDiscard(deck, discard, valueSum, discardNum);
	if (hasDiamond)
		hireFromDeck(deck, hand, valueSum, handNum);
}

// 阶段三 造成伤害 检查敌人是否被击败
// 黑牌技能
// enemy还活着 return 0， overkill return 1， 归化 return 2
int attackEnemy(enemy *currentEnemy, card *buffer, int bufferNum, int inputNum, card *hand)
{
	int valueSum = 0, hasClub = 0, hasSpade = 0;
	for (int i = bufferNum - inputNum; i < bufferNum; i++) {
		if (strcmp(buffer[i].suit, "Club") == 0) {
			hasClub = 1;
		} else if (strcmp(buffer[i].suit, "Spade") == 0) {
			hasSpade = 1;
		}
		valueSum += buffer[i].value;
	}

	// 黑牌技能结算
	// 草花让伤害翻倍
	if (hasClub)
		valueSum *= 2;
	int hp = currentEnemy->health;
	if (valueSum > hp) // overkill
		return 1;
	else if (valueSum == hp) // 归化
		return 2;
	else
		currentEnemy->health -= valueSum; // 减血量
	// 黑桃减伤害
	if (hasSpade)
		currentEnemy->attack = max(currentEnemy->attack - valueSum, 0);
	return 0;
}

void overkill(card *buffer, int *bufferNum, card *discard,
              int *discardNum, int *enemyIndex)
{
	(*enemyIndex)++; // 弃掉当前enemy
	for (int i = 0; i < *bufferNum; i++) {
		discard[*discardNum + i] = buffer[i]; // 从buffer->弃牌堆
	}
	*discardNum += *bufferNum; // 增加弃牌堆数量
	*bufferNum = 0;            //清空buffer
}

void adopt(card *buffer, int *bufferNum, card *discard, int *discardNum,
           enemy currentEnemy, int *enemyIndex, deque *deck)
{
	// 归化 进入牌堆顶部
	enqueueHead(deck, currentEnemy.enemy_card);
	// 其他的都和overkill的步骤一样
	overkill(buffer, bufferNum, discard, discardNum, enemyIndex);
}

// 被攻击 弃牌， 若没有足够牌游戏结束返回-1 否则返回0
int sufferDamage(card *hand, int *handNum, card *buffer,
                    int *bufferNum, enemy currentEnemy)
{
	printf("You are attacked, please discard hand cards with a total of not less than %d points.\n", currentEnemy.attack);
	int valueSum = 0;
	for (int i = 0; i < *handNum; i++) {
		valueSum += hand[i].value;
	}
	if (valueSum < currentEnemy.attack) { // 牌不够 游戏结束
		printf("You don't have enough cards. You die.\n");
		return -1;
	}
	// 有足够的牌可以弃
	printf("Choose the hand numbers you want to play:\n");
	printf("(No spaces between hand numbers, and press enter to play)\n");
	char inputNumbers[INPUT_MAX];
	while (1) {
		int isValid = 1, cnt = 0; // isValid为1 代表valid cnt是输入的数量
		// 输入的index是否valid
		while (1) {
			char c = getchar();
			if (c == '\n') {  //  接收到回车后break
				if (cnt == 0) // 没有输入直接回车的是invalid
					isValid = 0;
				break;
			}
			if (cnt > (*handNum) + 1) { //  超出手牌数  '\n'也要占一个
				isValid = 0;
				continue;
			}
			if (c < '1' || c > ((*handNum) + '0')) { // 超出index范围
				isValid = 0;                         // 但是不能立刻break 因为要等待回车
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
		
		// 判断数值总和是否大于attack
		if (isValid == 1) {
			valueSum = 0;
			for (int i = 0; i < cnt; i++) {
				valueSum += hand[inputNumbers[i] - '0' - 1].value;
			}
			if (valueSum < currentEnemy.attack)
				isValid = 0;
		}
		

		// valid input
		if (isValid == 1) {
			for (int i = 0; i < cnt; i++) { // hand -->> buffer
				int handIndex          = inputNumbers[i] - '0' - 1;
				// 我已经测到这里啦 前面都没有bug 就这个函数有问题
				printf("%d\n",handIndex);
				buffer[*bufferNum + i] = hand[handIndex];
				hand[handIndex].value  = 0;
			}
			*bufferNum += cnt;
			*handNum -= cnt;
			rearrangeCards(hand);
			return 0;
		} else {
			printf("Invalid input! Please choose again: \n");
			return -1;
		}
	}
	return 1;
}