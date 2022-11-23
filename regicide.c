#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"
#include "deque.h"

int main()
{
	struct card monsters[12];
	struct card soldiers[40];
	

	srand((unsigned int)time(NULL));

	//怪物队列
	printCard(monsters, 11, 13);

	shuffle(monsters, 4);
	shuffle(monsters + 4, 4);
	shuffle(monsters + 8, 4);

	printCard(soldiers, 1, 10);
	shuffle(soldiers, 40);

	for (int i = 0; i < 12; i++)
		printf("%s %s\n", monsters[i].suit, monsters[i].vname);

	for (int i = 0; i < 40; i++)
		printf("%s %s\n", soldiers[i].suit, soldiers[i].vname);

	struct deque deck = createDeque();
	enqueueHead(&deck, monsters[0]);
	enqueueHead(&deck, monsters[1]);

	
	return 0;
}