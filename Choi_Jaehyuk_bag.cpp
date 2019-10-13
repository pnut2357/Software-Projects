//**************************************************************************************
//  FILE: Choi_Jaehyuk_hw3.cpp
//  NAME: Choi_Jaehyuk_hw3
//
//  DESCRIPTION
//  This program is a High-Low-Guess card game based on singly linked-list data structure.
//	The bag contains 54 bag nodes as a singly linked-list, and each bag node has a pointer to
//	each card structure that contains each card information: suit and value of a card.
//	At the starting point, a card is drawn with the output of the analysis of probabilities
//  for the left cards in the deck. Then, the user have three choices to guess 1) if the value
//	the next card is higher, 2) lower, or 3) the exact value of the next card. For the option 1)
//	and 2), the user earns 1 point with correct guess, continuing the game. The option 3)
//	requests prompt of guess from the user so if the guess is right, the user earns 5 points.
//  If the guess is not right, the program terminates and outputs "GAME OVER".
//
//  Created by Jaehyuk Choi on 3/19/19. (jchoi154@asu.edu)
//
//  COURSE INFO
//  CSE240 Spring 2019
//  Homework4 03-20-2019 / Time: 2:00pm - 2:50pm MWF
//
//  Copyright © 2019 Jaehyuk Choi. All rights reserved.
//**************************************************************************************
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <string.h>
#include <iomanip>
#include "Choi_Jaehyuk_bag.h"

#define num_Suit 4
#define num_Value 13


node *head, *tail, *ptr;


using namespace std;

/*
 * integerToString(int) function converts integer value to string.
 */
string integerToString(int number)
{
	ostringstream s;
	s << number;
	return s.str();
}
/*
 * getStringFromValue(int) function transforms the special case of values
 * such as 1, 11, 12, and 13 into Ace, Jack, Queen, King
 */
string getStringFromValue(int pValue)
{
	switch(pValue)
	{
		case 1:
			return "A"; // Ace of 'A'
		case 11:
			return "J"; // Jack of 'J'
		case 12:
			return "Q";	// Queen of 'Q'
		case 13:
			return "K"; // King of 'K'
	}
	return integerToString(pValue); // returns the values from 2 to 10 as string values.
}
/*
 * getStringFromSuit(int) function transforms four suits of card from integers into strings.
 */
string getStringFromSuit(int pSuit)
{
	switch(pSuit)
	{
		case 1:
			return "S"; // Spade of 'S'
		case 2:
			return "C"; // Club of 'C'
		case 3:
			return "D"; // Diamond of 'D'
		case 4:
			return "H"; // Heart of 'H'
	}
	return integerToString(pSuit); // default case.
}
/*
 * getCurrentSize () function counts all bag nodes in the bag and return it.
 */
int getCurrentSize ()
{
	int count = 0;
	node *temp = head;
	while(temp != NULL)
	{
		++count;
		temp = temp->next;
	}
	return count;
}
/*
 * isEmpty() function checks if the bag is empty or not.
 */
bool isEmpty()
{
	bool result = false;
	if(head == NULL)
		result = true;
	else
		result = false;
	return result;
}
/*
 * add(int, int) function add each bag node with card structure to the list.
 */
void add(int pSuit, int pValue)
{
	node *temp = NULL;
	if(head == NULL)	// case1) if the list is empty.
	{
		head = new node; //in C, head = (node *)malloc(sizeof(node));
		head->card = new card; // in C, head->card = (card*)malloc(sizeof(card));
		head->card->Suit = pSuit;
		head->card->Value = pValue;
		head->next = NULL;
		tail=head;
	}
	else				// case2) if the list has more than one node.
	{
		temp = new node; // in C, temp = (node *)malloc(sizeof(node));
		temp->card = new card; // in C, temp->card = (card *)malloc(sizeof(card));
		temp->card->Suit = pSuit;
		temp->card->Value = pValue;
		temp->next = NULL;
		tail->next = temp; // adds at the end of the list.
		tail=temp; // tail = tail->next;
	}
}
/*
 * grab() function randomly picks one bag node with the card structure to which
 * the bag points. It should consider three cases: 1) the random index is the first
 * (i.e. the first bag node), 2) the random index is the last (ie.e the last bag node),
 * and 3) the random index is between 2 and the last-1.
 */
Card* grab() // structure Card pointer returns
{
	srand(time(0));
	int seed = rand()%getCurrentSize() + 1;	// random index.

	node *faster_ptr = head, *slower_ptr = head;
	ptr = head;
	if (seed == 1)								// case1) the random index is the first bag node
	{
		head = head->next;
	}
	else if(seed == getCurrentSize())			// case2) the random index is the last bag node
	{
		int i;
		for (i=1; i<seed-1; ++i)
		{
			ptr = ptr->next;
		}

		tail = ptr;
		ptr = tail->next;
		tail->next = NULL;
	}
	else if (seed > 1 && seed < getCurrentSize())// case3) the random index is between 2 and the last-1.
	{
		int i;
		for (i=1; i<seed-1; ++i)
		{
			slower_ptr = faster_ptr;
			faster_ptr = faster_ptr->next;
		}
		slower_ptr->next = faster_ptr->next;
		faster_ptr->next = NULL;
		// faster_ptr should be replaced by global pointer ptr to be deleted later.
		ptr=faster_ptr;
	}
	return ptr->card;
}
/*
 * getFrequencyOf(int) function counts the number of duplicated values of the cards
 * in the current deck so that it facilitates probability calculations.
 */
int getFrequencyOf(int pValue)
{
	int count = 0;
	node *temp = head;
	while(temp!=NULL)
	{
		int CASE = temp->card->Value;
		if(pValue == CASE)
		{
			++count;
		}
		temp = temp->next;
	}
	return count;
}
/*
 * empty() function clears all nodes in the bag.
 */
void empty()
{
	while(head != NULL) {
		node *temp = head;
		delete head->card;
		delete head;
		head = temp->next;
	}
}
/*
 * fillWithCards() function fills all the cards in the bag.
 */
void fillWithCards()
{
	int i, j;
	for(i=1; i<=num_Suit; ++i)
		for(j=1; j<=num_Value; ++j)
			add(i,j);
}
/*
 * removeLastCard() function searches and removes the last drawn card
 */
void removeLastCard()
{
	node *slower_ptr = head, *faster_ptr = head;
	while (faster_ptr!=NULL)
	{
		if ((faster_ptr->card->Value == ptr->card->Value) && (faster_ptr->card->Suit == ptr->card->Suit) )
		{
			slower_ptr->next = faster_ptr->next;
			faster_ptr->next = NULL;
			delete faster_ptr->card;
			delete faster_ptr;
		}
		slower_ptr = faster_ptr;
		faster_ptr = faster_ptr->next;
	}
}
/*
 * print(vector<Card*>) function prints suits and values of the cards stored in the list of vector.
 * NOTE: Those cards are drawn as long as the user plays the game until the game is over.
 */
void print(vector<Card*> list)
{
	int i;
	for (i=0; i < list.size(); ++i)
	{
		cout << "[" << getStringFromSuit(list.at(i)->Suit) << "-" << getStringFromValue(list.at(i)->Value) << "] ";
	}
}
/*
 * runProbabilities(float, int) function calculates the probabilities of each card left in the deck.
 */
void runProbabilities(float probablities[], int probSize)
{
	int cardValue;
	for(cardValue = 0; cardValue < probSize; cardValue++)
	{
		probablities[cardValue] = ((float)getFrequencyOf(cardValue+1))/getCurrentSize()*100;
	}
}
/*
 * outputProbabilities(float, int) function outputs the probabilities of each card left in the deck.
 */
void outputProbabilities(float probabilities[], int probSize)
{
	int cardValue;
	for(cardValue = 0; cardValue < probSize; cardValue++)
		cout << getStringFromValue(cardValue+1) << ":\t" << probabilities[cardValue] << "%" << endl;
}
/*
 * output(vector<Card*> &, int, int, float, int) function prints the analysis of probabilities
 * for facilitating the player to guess well.
 */
void output(vector<Card*> list, int pBagSize, int point, float probabilityArray[], int count)
{
	cout << "Cards drawn:" << endl;
	print(list);
	cout << endl;
	cout << "Cards left in deck: " << getCurrentSize() << endl << endl;
	runProbabilities(probabilityArray, num_Value);
	// calculates the probability of next card being higher and lower.
	float sumHigh = 0, sumLow = 0;
	int i;
	for(i=0; i<num_Value; i++)
	{
		if (i+1 < ptr->card->Value)
			sumLow += probabilityArray[i];
		else if (i+1 > ptr->card->Value)
			sumHigh += probabilityArray[i];
	}
	cout << fixed << setprecision(2);
	cout << "Probability of next card being higher: " << sumHigh << endl;
	cout << "Probability of next card being lower: " << sumLow << endl;
	cout << "Probability of next card being the same: " << ((float)getFrequencyOf(ptr->card->Value))/getCurrentSize()*100 << "%" <<endl << endl;
	cout << "Probability of next card being: " << endl;
	runProbabilities(probabilityArray, num_Value);
	outputProbabilities(probabilityArray, num_Value);

	cout << "Last card: " << "[" << getStringFromSuit(list.at(count)->Suit) << "-" << getStringFromValue(list.at(count)->Value) << "]" << endl;
	cout << "Points: " << point << endl << endl;
	// option 1, 2, and 3
	cout << "Choose option:\n"
			"1 - Next card will be higher\n"
			"2 - Next card will be lower\n"
			"3 - Guess exact value\n" << endl;
}
/*
 * HiLowGuessGame() function is to play the game.
 */
void HiLowGuessGame()
{
	head = NULL;
	tail = NULL;
	ptr = NULL;

	int choice, guess, count = 0, bagSize, point = 0;
	float probabilities[num_Value];
	fillWithCards();	// starts with new deck of cards.
	grab();				// grabs a card from the deck.
	vector<Card*> list;	// stores the drawn card into the vector list.
	list.push_back(ptr->card);
	bagSize = getCurrentSize();
	output(list, bagSize, point, probabilities, count);
	bool done = false;
	while(done == false)
	{
		// Refills a deck of cards if the number of the drawn cards are multiples of 34.
		if(/*list.size()%34 == 0*/ getCurrentSize() < 18)
		{
			empty();
			fillWithCards();
			removeLastCard();
		}
		grab();
		list.push_back(ptr->card);
		bagSize = getCurrentSize();
		// Test: cout << "Next Value is: " << ptr->card->Value << endl;
		// Gets the prompt from the user for guessing.
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				++count;
				// compare pre-card vs. post-card
				if ((list.at(count-1)->Value) > (ptr->card->Value))
				{
					cout << "GAME OVER" << endl;
					done = true;
				}
				else if ((list.at(count-1)->Value) < (ptr->card->Value))
				{
					++point; // 1 point if the guess is correct.
				}
				else if ((list.at(count-1)->Value) == ptr->card->Value)
				{
					cout << "Same card" << endl; // 0 point if the same card is drawn.
				}
				if (done == false)
				{
					output(list, bagSize, point, probabilities, count);
				}
			}
				break;
			case 2:
			{
				++count;
				// compare pre-card vs. post-card
				if ((list.at(count-1)->Value) < (ptr->card->Value))
				{
					cout << "GAME OVER" << endl;
					done = true;
				}
				else if ((list.at(count-1)->Value) > (ptr->card->Value))
				{
					++point; // 1 point if the guess is correct.
				}
				else if ((list.at(count-1)->Value) == (ptr->card->Value))
				{
					cout << "Same card" << endl; // 0 point if the same card is drawn.
				}
				if (done == false)
				{
					output(list, bagSize, point, probabilities, count);
				}
			}
				break;
			case 3:
			{
				++count;
				cout << "Enter your guess (Please type VALUES ONLY in integer): ";
				cin >> guess;
				// compare pre-card vs. post-card
				if (guess > (ptr->card->Value))
				{
					cout << "GAME OVER" << endl;
					done = true;
				}
				else if (guess < (ptr->card->Value))
				{
					cout << "GAME OVER" << endl;
					done = true;
				}
				else if (guess == (ptr->card->Value))
				{
					point += 5; // 5 point if the guess is correct.
				}
				if (done == false)
				{
					output(list, bagSize, point, probabilities, count);
				}
			}
				break;
		}
	}
}
void removePtr()
{
	delete ptr;
}

