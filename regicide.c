#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"
#include "deque.h"

int main()
{
	card  enemies_cards[ENEMIES_MAX];
	enemy enemies[ENEMIES_MAX];
	card  soldiers[SOLDIERS_MAX];
	card  hand[HAND_MAX]        = { 0 };
	card  buffer[SOLDIERS_MAX]  = { 0 };
	card  discard[SOLDIERS_MAX] = { 0 };
	int   handNum = 0, enemyIndex = 0, discardNum = 0, bufferNum = 0, jokerNum = 2; // 一开始有两张joker
	int   alive = 1, status;                                                        // alive = 1代表活着

	// 用时间来产生seed 产生随机数来洗牌
	srand((unsigned int)time(NULL));

	// 准备城堡牌堆
	castleDeck(enemies_cards, enemies);
	// 准备手牌队列
	printCard(soldiers, 1, 10);
	shuffle(soldiers, SOLDIERS_MAX);
	// 准备牌堆
	deque deck = createDeque();
	addCardsToDeck(&deck, soldiers, SOLDIERS_MAX);
	// 从牌堆抽满手牌
	hireFromDeck(&deck, hand, HAND_MAX, &handNum);

	while (alive) {
		// 展示当前enemy
		printf("PRINT ENEMIES\n");
		printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
		       enemies[enemyIndex].attack, enemies[enemyIndex].health);
		// 展示当前牌组
		displayCards(hand, handNum, HAND_TYPE);
		displayCards(buffer, bufferNum, BUFFER_TYPE);
		displayCards(discard, discardNum, DISCARD_TYPE);
		// 阶段一 出牌前询问是否用joker技能
		if (isUseJokerPower(hand, &handNum, buffer, &bufferNum, &deck, &jokerNum)) {
			// 展示重抽后牌组
			displayCards(hand, handNum, HAND_TYPE);
			displayCards(buffer, bufferNum, BUFFER_TYPE);
		}
		// 打出手牌 inputNum为打出手牌数
		int inputNum = getValidInput(hand, &handNum, buffer, &bufferNum);
		// 激活红色技能
		activateRedSuitPower(hand, &handNum, buffer, bufferNum, enemies[enemyIndex], inputNum, discard, &discardNum, &deck);
		// 攻击enemy status=0还活着 1代表overkill 2代表归化
		status = attackEnemy(&enemies[enemyIndex], buffer, bufferNum, inputNum, hand);
		// 如果enemy没死 承受攻击
		if (status == 0) {
			// 展示现在enemy状态
			printf("PRINT ENEMIES\n");
			printf("%s %s %d %d\n", enemies[enemyIndex].enemy_card.suit, enemies[enemyIndex].enemy_card.vname,
			       enemies[enemyIndex].attack, enemies[enemyIndex].health);
			// 展示现在牌组
			displayCards(hand, handNum, HAND_TYPE);
			displayCards(buffer, bufferNum, BUFFER_TYPE);
			// 阶段四 承受伤害前询问是否用joker技能
			if (isUseJokerPower(hand, &handNum, buffer, &bufferNum, &deck, &jokerNum)) {
				// 展示重抽后牌组
				displayCards(hand, handNum, HAND_TYPE);
				displayCards(buffer, bufferNum, BUFFER_TYPE);
			}
			// 受到攻击弃牌
			sufferDamage(hand, &handNum, buffer, &bufferNum, enemies[enemyIndex], &alive);
			displayCards(hand, handNum, HAND_TYPE);
			displayCards(buffer, bufferNum, BUFFER_TYPE);
		} else { // enemy死了 进入新的回合
			killEnemy(buffer, &bufferNum, discard, &discardNum, enemies[enemyIndex], &enemyIndex, &deck, status);
		}
	}
	return 0;
}