#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"
#include "deque.h"

int main()
{
	struct card  enemies_cards[ENEMIES_MAX];
	struct enemy enemies[ENEMIES_MAX];
	struct card  soldiers[SOLDIERS_MAX];
	struct card  hand[HAND_MAX] = { 0 };
	int          handNum        = 0;
	int validInput[INPUT_MAX]; 

	srand((unsigned int)time(NULL));

	//准备城堡牌堆
	castleDeck(enemies_cards, enemies);

	//手牌队列
	printCard(soldiers, 1, 10);
	shuffle(soldiers, SOLDIERS_MAX);

	// for (int i = 0; i < ENEMIES_MAX; i++)
	// 	printf("%s %s %d %d\n", enemies[i].enemy_card.suit, enemies[i].enemy_card.vname,
	// 	       enemies[i].attack, enemies[i].health);

	// for (int i = 0; i < SOLDIERS_MAX; i++)
	// 	printf("%s %s\n", soldiers[i].suit, soldiers[i].vname);

	// for (int i = 0; i < HAND_MAX; i++)
	// 	printf("%s %d\n", hand[i].suit, hand[i].value);

	//准备牌堆
	struct deque deck = createDeque();
	addCardsToDeck(&deck, soldiers, SOLDIERS_MAX);
	hireFromDeck(&deck, hand, 8, &handNum);
	displayHand(hand, handNum);

	int cnt = getValidInput(hand,validInput);
	printf("%d\n", cnt);
	for(int i=0; i < cnt; i++){
		printf("%d ",validInput[i]);
	}
	rearrangeCards(hand);
	int validInput[5];
	int input_size = getValidInput(hand, validInput);
	for(int i = 0; i < input_size; i++){
		printf("%d ", validInput[i]);
	}

	return 0;
}