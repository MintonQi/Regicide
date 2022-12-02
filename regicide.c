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
	struct card  hand[HAND_MAX]    = { 0 };
	struct card  buffer[SOLDIERS_MAX]  = { 0 };
	struct card  discard[SOLDIERS_MAX] = { 0 };
	int          handNum = 0, enemyIndex = 0, discardNum = 0;
	int          validInput[INPUT_MAX];

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
	//displayEnemy(enemies[enemyIndex]);
	displayHand(hand, handNum);

	// for(int i = 0;i<handNum;i++){
	// 	discard[i] = hand[i];
	// 	discardNum++;
	// }
	// displayHand(discard,discardNum);
	// healFromDiscard(&deck,discard,5,&discardNum);
	// displayHand(discard,discardNum);

	int cnt = getValidInput(hand, validInput);
	printf("%d\n", cnt);
	for(int i=0; i < cnt; i++){
		printf("%d ",validInput[i]);
	}
	rearrangeCards(hand);

	return 0;
}