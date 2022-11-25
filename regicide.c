#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "utility.h"
#include "deque.h"

int main()
{
	struct card enemies[ENEMIES_MAX];
	struct card soldiers[SOLDIERS_MAX];
	struct card player[PLAYER_MAX] = {0};
	int playerCardsNum = 0;
	
	srand((unsigned int)time(NULL));

	//怪物队列
	printCard(enemies, 11, 13);

	shuffle(enemies, 4);
	shuffle(enemies + 4, 4);
	shuffle(enemies + 8, 4);

	printCard(soldiers, 1, 10);
	shuffle(soldiers, SOLDIERS_MAX);

	// for (int i = 0; i < ENEMIES_MAX; i++)
	// 	printf("%s %s\n", enemies[i].suit, enemies[i].vname);

	// for (int i = 0; i < SOLDIERS_MAX; i++)
	// 	printf("%s %s\n", soldiers[i].suit, soldiers[i].vname);
	
	// for (int i = 0; i < PLAYER_MAX; i++)
	// 	printf("%s %d\n", player[i].suit, player[i].value);

	struct deque deck = createDeque();

	addCardsToDeck(&deck, soldiers, SOLDIERS_MAX);
	hireFromDeck(&deck, player, 8, &playerCardsNum);
	displayPlayerCards(player);
	

	// enqueueHead(&deck, enemies[0]);
	// enqueueHead(&deck, enemies[1]);
	// enqueueTail(&deck, enemies[11]);
	// printf("%d\n", getSize(&deck));
	// printf("%s\n", deck.head->next->data.vname);
	// printf("%s\n", deck.head->next->next->data.vname);
	// printf("%s\n", deck.head->next->next->next->data.vname);
	// printf("%s\n", dequeueHead(&deck).vname);
	// printf("%s\n", dequeueHead(&deck).vname);
	// printf("%s\n", dequeueHead(&deck).vname);
	// printf("%d\n", deck.size);
	return 0;
}