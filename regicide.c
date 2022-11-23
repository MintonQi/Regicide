#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"

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
		if (monsters[i].value == 1 || (monsters[i].value >= 11 && monsters[i].value <= 13)) {
			printf("%s %s\n", monsters[i].suit, monsters[i].vname);
		} else
			printf("%s %d\n", monsters[i].suit, monsters[i].value);

	for (int i = 0; i < 40; i++)
		if (soldiers[i].value == 1 ) {
			printf("%s %s\n", soldiers[i].suit, soldiers[i].vname);
		} else
			printf("%s %d\n", soldiers[i].suit, soldiers[i].value);

	return 0;
}