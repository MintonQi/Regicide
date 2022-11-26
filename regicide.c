#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "utility.h"
#include "deque.h"

int main()
{
	struct card enemies[ENEMIES_MAX];
	struct card soldiers[SOLDIERS_MAX];
	struct card hand[HAND_MAX] = {0};
	int handNum = 0;
	
	srand((unsigned int)time(NULL));

	//准备怪物队列
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
	
	// for (int i = 0; i < HAND_MAX; i++)
	// 	printf("%s %d\n", hand[i].suit, hand[i].value);

	//准备牌堆
	struct deque deck = createDeque();

	addCardsToDeck(&deck, soldiers, SOLDIERS_MAX);
	hireFromDeck(&deck, hand, 8, &handNum);
	displayHand(hand);
	// getValidInput(hand); 
	// printf("%s", validInput[0]->vname);

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