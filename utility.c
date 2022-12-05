#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "utility.h"
#include "deque.h"

char *vnames[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
char *suits[]  = { "Spade", "Club", "Heart", "Diamond" };

//ϴ��  1. ���˶���  2. ���ƶ�
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

//���ƶѵײ�����
// 1. ��ʼ���ƶ�  2.�����ƶ�heal
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
	// nΪ��ͼ�����������������СΪ�ܹ������������
	n = min(n, deck->size);          // ���deck�������㣬��Сn��deckʣ������
	n = min(n, HAND_MAX - *handNum); // ������ƿռ䲻�㣬��Сn������ʣ��ռ�
	for (int i = 0; i < n; i++)      // ����n����
		hand[i + *handNum] = dequeueHead(deck);
	*handNum += n; // ��������n
}

void healFromDiscard(deque *deck, card *discard, int n, int *discardNum)
{
	shuffle(discard, *discardNum); // ϴ���ƶ�
	n = min(n, *discardNum);       // nΪ��heal������

	for (int i = 0; i < n; i++) { // ���Ʋ����ƶѵײ� ֮����Ϊ0
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

// �׶�1����ȡ�����Ҫ����Ĵ���Ŀ��Ʋ�����buffer ���ش����������
// ���Ե����� ����combo���ǲ�����10 ����һ�ų�����+һ������ ���2222 ������
int getValidInput(card *hand, int *handNum, card *buffer, int *bufferNum)
{
	printf("Choose the hand numbers you want to play:\n");
	printf("(No spaces between hand numbers, and press enter to play)\n");
	char inputNumbers[INPUT_MAX];

	while (1) {
		int isValid = 1, cnt = 0; // isValidΪ1 ����valid
		// �����index�Ƿ�valid
		while (1) { // ����'\n'���5���ַ�
			char c = getchar();
			if (c == '\n') {  //  ���յ��س���break
				if (cnt == 0) // û������ֱ�ӻس�����invalid
					isValid = 0;
				break;
			}
			if (cnt >= 5) { //  ������������
				isValid = 0;
				continue;
			}
			if (c < '1' || c > '8') { // invalid input
				isValid = 0;          // ���ǲ�������break ��ΪҪ�ȴ��س�
			} else
				inputNumbers[cnt] = c;
			cnt++;
		}

		// �ж�����index�Ƿ��ظ�
		if (isValid == 1) {
			for (int i = 0; i < cnt; i++) {
				for (int j = i + 1; j < cnt; j++) {
					if (inputNumbers[i] == inputNumbers[j]) {
						isValid = 0;
						i       = cnt; // �������ѭ��
						break;         // �����ڲ�ѭ��
					}
				}
			}
		}

		// �ж�combo�Ƿ�valid 1. ���� 2. ������
		if (isValid == 1) {
			int isSame = 1, petNum = 0; // isSame==1 ������ֵ��ͬ
			int comboCardValues[4];     // ����������
			for (int i = 0; i < cnt; i++) {
				comboCardValues[i] = hand[inputNumbers[i] - '0' - 1].value;
			}
			for (int i = 0; i < cnt; i++) {
				if (comboCardValues[i] == 1) // �г���
					petNum++;
				for (int j = i + 1; j < cnt; j++) { // ��ֵ�Ƿ���ͬ
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
			for (int i = 0; i < cnt; i++){ // hand -->> buffer
				int handIndex = inputNumbers[i] - '0' - 1;
				buffer[*bufferNum + i] = hand[handIndex];
				hand[handIndex].value = 0;
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

// �׶ζ� �����ɫ�Ƽ���
// ���Ƽ���
void activateRedSuitPower(card *hand, int *handNum, card *buffer, int bufferNum, int inputNum,
                          card *discard, int *discardNum, deque *deck)
{
	int valueSum = 0, hasHeart = 0, hasDiamond = 0;
	for (int i = bufferNum - inputNum; i < bufferNum; i++) { // ����û�к�ɫ�� ����¼����ֵ
		if (strcmp(buffer[i].suit, "Heart") == 0) {
			hasHeart = 1;
		} else if (strcmp(buffer[i].suit, "Diamond") == 0) {
			hasDiamond = 1;
		}
		valueSum += buffer[i].value;
	}
	if (hasHeart + hasDiamond == 0)
		return;

	// ���Ƽ��ܽ���
	if (hasHeart)
		healFromDiscard(deck, discard, valueSum, discardNum);
	if (hasDiamond)
		hireFromDeck(deck, hand, valueSum, handNum);
}

// �׶��� �������Ƿ񱻻���
// ���Ƽ���
// enemy������ return 0�� overkill return 1�� �黯 return 2
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

	// ���Ƽ��ܽ���
	// �ݻ����˺�����
	if (hasClub)
		valueSum *= 2;
	int hp = currentEnemy->health;
	if (valueSum > hp) // overkill
		return 1;
	else if (valueSum == hp) // �黯
		return 2;
	else
		currentEnemy->health -= valueSum; // ��Ѫ��
	// ���Ҽ��˺�
	if (hasSpade)
		currentEnemy->attack = max(currentEnemy->attack - valueSum, 0);
	return 0;
}


void overkill(card *buffer, int *bufferNum, card *discard,
              int *discardNum, int *enemyIndex)
{
	(*enemyIndex)++; // ������ǰenemy
	for (int i = 0; i < *bufferNum; i++) {
		discard[*discardNum + i] = buffer[i]; // ��buffer->���ƶ�
	}
	*discardNum += *bufferNum; // �������ƶ�����
	*bufferNum = 0;            //���buffer
}

void adopt(card *buffer, int *bufferNum, card *discard, int *discardNum,
           enemy currentEnemy, int *enemyIndex, deque *deck)
{
	// currentEnemy.enemy_card
	//enqueueHead(deck, );

}