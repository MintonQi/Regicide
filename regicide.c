#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"
#include "deque.h"

int main()
{
	card  enemies_cards[ENEMIES_MAX];
	enemy enemies[ENEMIES_MAX];
	card  soldiers[SOLDIERS_MAX];
	card  hand[HAND_MAX]        = { 0 };
	card  buffer[SOLDIERS_MAX]  = { 0 };
	card  discard[SOLDIERS_MAX] = { 0 };
	int   handNum = 0, enemyIndex = 0, discardNum = 0, bufferNum = 0, jokerNum = 2; // 一开始有两张joker

	srand((unsigned int)time(NULL));

	//准备城堡牌堆
	castleDeck(enemies_cards, enemies);

	//手牌队列
	printCard(soldiers, 1, 10);
	shuffle(soldiers, SOLDIERS_MAX);

	// //print enemies
	// for (int i = 0; i < ENEMIES_MAX; i++)
	// 	printf("%s %s %d %d\n", enemies[i].enemy_card.suit, enemies[i].enemy_card.vname,
	// 	       enemies[i].attack, enemies[i].health);

	// // print soldiers
	// for (int i = 0; i < SOLDIERS_MAX; i++)
	// 	printf("%s %s\n", soldiers[i].suit, soldiers[i].vname);

	// for (int i = 0; i < HAND_MAX; i++)
	// 	printf("%s %d\n", hand[i].suit, hand[i].value);
	
	//准备牌堆
	deque deck = createDeque();
	addCardsToDeck(&deck, soldiers, SOLDIERS_MAX);
	// 从牌堆抽取手牌
	hireFromDeck(&deck, hand, HAND_MAX, &handNum);
	printf("PRINT HAND\n");
	displayHand(hand, handNum);
	// 当前enemy登场
	printf("PRINT ENEMIES\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);
	// 打出手牌
	int inputNum = getValidInput(hand, &handNum, buffer, &bufferNum);
	// 激活红色技能
	activateRedSuitPower(hand, &handNum, buffer, bufferNum, enemies[enemyIndex],inputNum, discard, &discardNum, &deck);
	// 攻击enemy
	attackEnemy(&enemies[enemyIndex], buffer, bufferNum, inputNum, hand);
	printf("PRINT ENEMIES\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);
	// 展示牌组情况
	printf("PRINT HAND\n");
	displayHand(hand, handNum);
	printf("PIRNT BUFFER\n");
	displayHand(buffer, bufferNum);
	printf("PRINT DISCARD\n");
	displayHand(discard, discardNum);
	// 受到攻击弃牌
	sufferDamage(hand, &handNum, buffer, &bufferNum, enemies[enemyIndex]);
	printf("PRINT HAND\n");
	displayHand(hand, handNum);
	printf("PIRNT BUFFER\n");
	displayHand(buffer, bufferNum);
	// 使用joker技能
	// useJokerPower(hand, &handNum,buffer, &bufferNum,&deck,&jokerNum);
	// printf("PRINT HAND\n");
	// displayHand(hand, handNum);
	// printf("PIRNT BUFFER\n");
	// displayHand(buffer, bufferNum);
	return 0;
}