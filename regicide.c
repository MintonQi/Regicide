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
	int   handNum = 0, enemyIndex = 0, discardNum = 0, bufferNum = 0;
	int   validInput[INPUT_MAX];

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
	hireFromDeck(&deck, hand, 4, &handNum);
	// displayEnemy(enemies[enemyIndex]);
	printf("打印手牌\n");
	displayHand(hand, handNum);

	// 赋值弃牌堆（暂时用一下手牌
	for (int i = 0; i < handNum; i++) {
		discard[i] = hand[i];
		discardNum++;
	}

	printf("打印弃牌堆\n");
	displayHand(discard, discardNum);
	// healFromDiscard(&deck,discard,5,&discardNum);
	// displayHand(discard,discardNum);

	int inputNum = getValidInput(hand, validInput);
	// printf("%d\n", inputNum);
	//  for(int i=0; i < inputNum; i++){
	//  	printf("%d ",validInput[i]);
	//  }
	// rearrangeCards(hand);

	activateRedSuitPower(hand, &handNum, validInput, inputNum, discard, &discardNum, &deck);
	printf("打印手牌\n");
	displayHand(hand, handNum);
	printf("打印弃牌堆\n");
	displayHand(discard, discardNum);
	printf("打印deck数量\n");
	printf("%d\n", deck.size);

	printf("打印enemy信息\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);
	attackEnemy(&enemies[enemyIndex], validInput, inputNum, hand);
	printf("打印enemy信息\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);

	playCard(validInput, inputNum, buffer, &bufferNum, hand, &handNum);
	printf("打印手牌\n");
	displayHand(hand, handNum);
	printf("打印buffer\n");
	displayHand(buffer, bufferNum);

	overkill(buffer, &bufferNum, discard, &discardNum, &enemyIndex);
	printf("打印enemy信息\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);
	printf("打印buffer\n");
	displayHand(buffer, bufferNum);
	printf("打印弃牌堆\n");
	displayHand(discard, discardNum);
	return 0;
}