/*
 * Choi_Jaehyuk_bag.h
 *
 *  Created on: Mar 12, 2019
 *      Author: Jae
 */

#ifndef CHOI_JAEHYUK_BAG_H_
#define CHOI_JAEHYUK_BAG_H_

using namespace std;

typedef struct Card
{
	int Suit;
	int Value;
}card;

typedef struct BagNode
{
	Card *card;
	BagNode *next;
}node;

string integerToString(int);
string getStringFromValue(int);
string getStringFromSuit(int);
int getCurrentSize ();
bool isEmpty();
void add(int, int);
Card* grab();
int getFrequencyOf(int);
void empty();
void fillWithCards();
void removeLastCard();
void print(vector<Card*>);
void runProbabilities(float, int);
void outputProbabilities(float, int);
void output(vector<Card*>, int, int, float, int);
void HiLowGuessGame();
void removePtr();

#endif /* CHOI_JAEHYUK_BAG_H_ */

