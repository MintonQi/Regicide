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
	card  hand[HAND_MAX]    = { 0 };
	card  buffer[SOLDIERS_MAX]  = { 0 };
	card  discard[SOLDIERS_MAX] = { 0 };
	int   handNum = 0, enemyIndex = 0, discardNum = 0;
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
	//displayEnemy(enemies[enemyIndex]);
	displayHand(hand, handNum);

	for(int i = 0;i<handNum;i++){
		discard[i] = hand[i];
		discardNum++;
	}
	displayHand(discard,discardNum);
	// healFromDiscard(&deck,discard,5,&discardNum);
	// displayHand(discard,discardNum);

	int inputNum = getValidInput(hand, validInput);
	printf("%d\n", inputNum);
	for(int i=0; i < inputNum; i++){
		printf("%d ",validInput[i]);
	}
	rearrangeCards(hand);

	activateRedSuitPower(hand, &handNum, validInput, inputNum, discard, &discardNum, &deck);
	displayHand(discard, discardNum);
	displayHand(hand, handNum);
	printf("%d\n", deck.size);
	return 0;
}