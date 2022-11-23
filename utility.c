#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utility.h"

void shuffle(void *arr, int size)
{
	struct card *cards = (struct card *)arr;

	for (int i = 0; i < size; i++) {
		int j = rand() % size;
		// printf("%d\n", j);
		struct card temp = cards[j];
		cards[j]         = cards[i];
		cards[i]         = temp;
	}
}

void printCard(struct card *cards, int start, int end)
{
	int count = 0;
	for (int i = start; i <= end; i++) {
		for (int j = 0; j < 4; j++) {
			switch (j) {
			case 0:
				cards[count].suit = "Spade";
				break;
			case 1:
				cards[count].suit = "Club";
				break;
			case 2:
				cards[count].suit = "Heart";
				break;
			case 3:
				cards[count].suit = "Diamond";
				break;
			default:
				break;
			}

			cards[count].value = i;
			
			switch (i)
			{
			case 1:
				cards[count].vname = "A";
				break;
			case 11:
				cards[count].vname = "J";
				break;
			case 12:
				cards[count].vname = "Q";
				break;
			case 13:
				cards[count].vname = "K";
				break;
			default:
				//itoa(i, &cards[count].vname, 10);
				break;
			}

			count++;
		}
	}
}
