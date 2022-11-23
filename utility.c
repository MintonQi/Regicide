#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utility.h"

char *display[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

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
			cards[count].vname = display[i - 1];
			count++;
		}
	}
}
