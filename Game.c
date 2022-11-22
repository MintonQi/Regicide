#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct card
{
    char *suit;
    int value;
    //char c;
};
//是不是打印出来“A 2...J Q K"而不是“1 2...11 12 13”会比较好，
//所以可能需要加个char的属性？

void shuffle(void *arr, int size)
{
    struct card *cards = (struct card *)arr;
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;
        printf("%d\n", j);
        struct card temp = cards[j];
        cards[j] = cards[i];
        cards[i] = temp;
    }
}


void create_monsters(void *arr) // 创建随机怪物队列
{ 
    struct card *monsters = (struct card *)arr;
    int count = 0;
    for (int j = 11; j < 14; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                monsters[count].suit = "Spade";
                break;
            case 1:
                monsters[count].suit = "Club";
                break;
            case 2:
                monsters[count].suit = "Heart";
                break;
            case 3:
                monsters[count].suit = "Diamond";
                break;
            default:
                break;
            }

            monsters[count].value = j;
            count++;
        }
    }
    //每次代码运行都以不同seed为种子调取伪随机数序列
    //如果srand()写到shuffle内部则连续shuffle时由于时间相近，
    //三个shuffle会使用同个seed产生相同序列，导致jqk的序列顺序相同。
    srand((unsigned int)time(NULL));
    shuffle(monsters, 4);
    shuffle(monsters + 4, 4);
    shuffle(monsters + 8, 4);
    // printf("1: pet, 11: Jack, 12: Queen, 13: King\n");
    for (int i = 0; i < 12; i++)
        printf("%s %d\n", monsters[i].suit, monsters[i].value);
}

void print_cards(){}
void use_joker(){}


int main()
{
    struct card monsters[12];
    create_monsters(monsters);
    // int a = 10; // printf("%d\n", a); // printf("%p\n",&a);
    return 0;
}

