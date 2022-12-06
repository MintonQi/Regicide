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

	printf("PRINT HAND\n");
	displayHand(hand, handNum);

	// printf("PRINT BUFFER\n");
	// displayHand(buffer, bufferNum);

	// 赋值弃牌堆（暂时用一下手牌
	// for (int i = 0; i < handNum; i++) {
	// 	discard[i] = hand[i];
	// 	discardNum++;
	// }

	// printf("PRINT DISCARD\n");
	// displayHand(discard, discardNum);

	int inputNum = getValidInput(hand, &handNum, buffer, &bufferNum);

	activateRedSuitPower(hand, &handNum, buffer, bufferNum, inputNum, discard, &discardNum, &deck);

	printf("PRINT ENEMIES\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);
	
	attackEnemy(&enemies[enemyIndex], buffer, bufferNum, inputNum, hand);
	printf("PRINT ENEMIES\n");
	printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	       enemies[enemyIndex].attack, enemies[enemyIndex].health);
	printf("PRINT HAND\n");
	displayHand(hand, handNum);
	printf("PIRNT BUFFER\n");
	displayHand(buffer, bufferNum);
	printf("PRINT DISCARD\n");
	displayHand(discard, discardNum);

	takeEnemyAttack(hand, &handNum, buffer, &bufferNum, enemies[enemyIndex]);
	printf("PRINT HAND\n");
	displayHand(hand, handNum);
	printf("PIRNT BUFFER\n");
	displayHand(buffer, bufferNum);
	
	// printf("PRINT DECK.SIZE\n");
	// printf("%d\n", deck.size);
	// overkill(buffer, &bufferNum, discard, &discardNum, &enemyIndex);
	// printf("PRINT NEW ENEMIES\n");
	// printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
	//        enemies[enemyIndex].attack, enemies[enemyIndex].health);
	// printf("PRINT BUFFER\n");
	// displayHand(buffer, bufferNum);
	// printf("PINRT DISCARD\n");
	// displayHand(discard, discardNum);
	
	// printf("ADOPT\n");
	// adopt(buffer, &bufferNum, discard, &discardNum, enemies[enemyIndex],&enemyIndex,&deck);
	// hireFromDeck(&deck,hand,2,&handNum);
	// printf("PRINT HAND\n");
	// displayHand(hand, handNum);
	// printf("PRINT DECK.SIZE\n");
	// printf("%d\n", deck.size);
	
	return 0;
}