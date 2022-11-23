#ifndef UTILITY_H
#define UTILITY_H

struct card {
	char *suit;
	char *vname;
	int   value;
};

void shuffle(void *arr, int size);
void printCard(struct card *cards, int start, int end);

#endif