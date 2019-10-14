/****************************************************************************************
 * FILE: Choi_Jaehyuk_assn5.cpp
 * NAME: Choi_Jaehyuk_assn5.cpp
 *
 * DESCRIPTION
 * This program outputs word frequency analysis in a text file by reading a text file
 * based on a templated binary-search-tree (BST) data structure. The .cpp file outputs total
 * number of words followed by all the words with their frequencies in the text, total number
 * of unique words followed by all unique words with their frequencies (i.e. frequency must be
 * 1 for all unique words), 5 most and least frequently used words. The program provide the
 * options: 1. Word Analysis in Alphabetical Order, 2. Word Analysis in Frequency Order, 3.
 * Find Words from Hamlet.txt, 4. Output to a Text File Named out_Hamlet.txt, and 5. Quit.
 * The option 3 finds the word for which a user look and prints the frequency of the word.
 * The option 4 outputs the word frequency analysis to a text file for review.
 *
 * Created by Jaehyuk Choi on 3/19/19. (jchoi154@asu.edu)
 *
 * COURSE INFO
 * CSE240 Spring 2019
 * Homework5 04-07-2019 / Time: 2:00pm - 2:50pm MWF
 *
 * Copyright © 2019 Jaehyuk Choi. All rights reserved.
 *
 * **************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "Choi_bst.h"

#define WIDTH 45
#define ENDWIDTH 10

//using namespace std;
std::string convertToLower(std::string);
/**
 * The class WordCounter counts the word if the word from a text file is already in the tree.
 * The getWord() and getCount() are accessors in the class. and the operator==(), operator>(),
 * and operator<() are overloading methods to apply to the word frequency analysis project.
 * The incrementWordCount() increases the integer value of WordCount if the word is duplicate.
 */
class WordCounter
{
public:
	WordCounter(std::string);
	std::string getWord() const;
	int getCount() const;
	bool operator==(const WordCounter&) const;
	bool operator>(const WordCounter&) const;
	bool operator<(const WordCounter&) const;
	void incrementWordCount();
private:
	int wordCount;
	std::string word;
};

WordCounter :: WordCounter(std::string pWord)
{
	wordCount = 1;
	word = pWord;

}
std::string WordCounter :: getWord() const
{
	return word;
}
int WordCounter :: getCount() const
{
	return wordCount;
}
bool WordCounter :: operator==(const WordCounter& other) const
{
	//if ( convertToLower(this->word) == convertToLower(other.getWord()) )
		//++wordCount;
	return convertToLower(this->word) == convertToLower(other.getWord());
}
bool WordCounter :: operator>(const WordCounter& other) const
{
	return convertToLower(this->word) > convertToLower(other.getWord());
}
bool WordCounter :: operator<(const WordCounter& other) const
{
	return convertToLower(this->word) < convertToLower(other.getWord());
}
void WordCounter :: incrementWordCount()
{
	++wordCount;
}
/**
 * The convertToLower converts upper-case of alphabets to lower-case of alphabets.
 * In this project, the word should be case insensitive. (e.g. 'The', 'thE', 'thE',
 * 'tHE', 'ThE', 'THe', and 'THE' are treated as the same.)
 */
std::string convertToLower(std::string pValue)
{
	unsigned int i;
	for (i=0; i<pValue.length(); ++i)
	{
		pValue[i] = tolower(pValue[i]);
	}
	return pValue;
}
/**
 * The isFineToKeep() returns boolean ture or false whether to keep a character or not.
 */
bool isFineToKeep(char pCharacter)
{
	bool result = false;
    if ( isalpha(pCharacter) || pCharacter == '\'' || pCharacter == '-' || pCharacter == '\0' )
        result = true;
    else if ( ispunct(pCharacter) || isdigit(pCharacter) )
    	result = false;
    return result;
}
/**
 * The insertUnique helps to store words in a vector if the word is new. Otherwise, it increments
 * the WordCount for duplicates of the words
 */
void insertUnique(std::vector<WordCounter>& pWCount, WordCounter pWordCounter)
{
	std::vector<WordCounter> :: iterator iterator = std::find(pWCount.begin(), pWCount.end(), pWordCounter);
	if (iterator == pWCount.end()/*!std::binary_search(pWCount.begin(), pWCount.end(), pWordCounter)*/)
		pWCount.push_back(pWordCounter);
	else
		iterator->incrementWordCount();
}
/**
 * The compareCount() compares two counts in two objects.
 */
bool compareCount(const WordCounter& pWord1, const WordCounter& pWord2)
{
	bool result;
	if (pWord1.getCount() > pWord2.getCount())
		result = true;
	else
		result = false;
	return result;
}
/**
 * The compareCount() compares two words in two objects.
 */
bool compareWord(const WordCounter& pWord1, const WordCounter& pWord2)
{
	bool result;
	if (pWord1.getWord() < pWord2.getWord())
		result = true;
	else
		result = false;
	return result;
}
/**
 * The print5MostVector() prints the 5 most frequently used words if bool printMostFreq is true.
 * Otherwise, it prints the 5 least frequently used words.
 */
void print5MostVector(std::vector< WordCounter > pWCount, bool printMostFreq)
{
	unsigned int i;
	const unsigned int numOfVectorToPrint=5;
	if (printMostFreq == true)
	{
		for (i=0; i<numOfVectorToPrint; ++i)
			std::cout << pWCount[i].getWord() << " (" << pWCount[i].getCount() << ") ";
	}
	else
	{
		for (i=0; i<numOfVectorToPrint; ++i)
			std::cout << pWCount[pWCount.size()-(numOfVectorToPrint-i)].getWord() << " (" << pWCount[pWCount.size()-(numOfVectorToPrint-i)].getCount() << ") ";
	}
	std::cout << std::endl;
}
/**
 * The wordAnalysis() shows the options for word frequency analysis of a text file.
 */
void wordAnalysis(Choi_BST< std::string > pTree, std::vector< WordCounter > pWCount, std::string pFilename)
{
	int choice;
	bool done = false;
	while(done == false)
	{
		// Gets the prompt from the user for guessing.
		// options
		std::cout << "Choose option:" << std::endl;
		std::cout << "1. Word Analysis in Alphabetical Order" << std::endl;
		std::cout << "2. Word Analysis in Frequency Order" << std::endl;
		std::cout << "3. Find Words from " << pFilename << std::endl;
		std::cout << "4. Output to a Text File Named " << "out_"+pFilename << std::endl;
		std::cout << "5. Quit" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				std::cout << "******* Word Analysis in Alphabetical Order *******" << std::endl;
				std::sort(pWCount.begin(), pWCount.end(), compareWord);
				// Total words with number of total words followed by total words with their frequencies
				std::cout << "Total Words: " << pTree.length() << std::endl;
				unsigned int i;
				for (i=0; i<pWCount.size(); ++i)
				{
					std::cout << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
				}
				// Total unique words with number of unique total words followed by total unique words with their frequencies
				unsigned int uniqueCount=0;
				for (i=0; i<pWCount.size(); ++i)
				{
					if( pWCount[i].getCount() == 1 )
						++uniqueCount;
				}
				std::cout << "\nTotal Unique Words: " << uniqueCount << std::endl;
				for (i=0; i<pWCount.size(); ++i)
				{
					if( pWCount[i].getCount() == 1 )
						std::cout << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
				}
				// 5 most and least frequently used words
				std::sort(pWCount.begin(), pWCount.end(), compareCount);
				std::cout << "\n5 most frequently used words: " << std::endl;
				print5MostVector(pWCount, true);
				std::cout << "\n5 least frequently used words: " << std::endl;
				print5MostVector(pWCount, false);
				std::cout << std::endl;
			}
				break;
			case 2:
			{
				std::cout << "******* Word Analysis in Frequency Order *******" << std::endl;
				std::sort(pWCount.begin(), pWCount.end(), compareCount);
				// Total words with number of unique total words followed by total words with their frequencies
				std::cout << "Total Words: " << pTree.length() << std::endl;
				unsigned int i;
				for (i=0; i<pWCount.size(); ++i)
				{
					std::cout << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
				}
				// Total unique words with number of unique total words followed by total unique words with their frequencies
				unsigned int uniqueCount=0;
				for (i=0; i<pWCount.size(); ++i)
				{
					if( pWCount[i].getCount() == 1 )
						++uniqueCount;
				}
				std::cout << "\nTotal Unique Words: " << uniqueCount << std::endl;
				for (i=0; i<pWCount.size(); ++i)
				{
					if( pWCount[i].getCount() == 1 )
						std::cout << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right <<  std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
				}
				// 5 most and least frequently used words
				std::cout << "\n5 most frequently used words: " << std::endl;
				print5MostVector(pWCount, true);
				std::cout << "\n5 least frequently used words: " << std::endl;
				print5MostVector(pWCount, false);
				std::cout << std::endl;
			}
				break;
			case 3:
			{
				std::cout << "Please enter the word you want to find: ";
				std::string userInput;
				std::cin >> userInput;
				unsigned int i;
				bool find= false;
				for (i=0; i<pWCount.size(); ++i)
				{
					if( pWCount[i].getWord() == convertToLower(userInput) )
					{
						std::cout << "The Frequency of "<< pWCount[i].getWord() << " is " << pWCount[i].getCount() << std::endl;
						find = true;
					}
				}
				if(find == false)
				{
					std::cout << "The item is not found" << std::endl;
				}
			}
				break;
			case 4:
			{
				std::cout << "Choose option:" << std::endl;
				std::cout << "1. Word Analysis in Alphabetical Order to a Text File" << std::endl;
				std::cout << "2. Word Analysis in Frequency Order to a Text File" << std::endl;
				int choiceForTextFile;
				std::cin >> choiceForTextFile;
				std::ofstream outFile;
				outFile.open(("out_"+pFilename).c_str());

				if (choiceForTextFile == 1)
				{
					outFile << "******* Word Analysis in Alphabetical Order *******" << std::endl;
					std::sort(pWCount.begin(), pWCount.end(), compareWord);
					// Total words with number of unique total words followed by total words with their frequencies
					outFile << "Total Words: " << pTree.length() << std::endl;
					unsigned int i;
					for (i=0; i<pWCount.size(); ++i)
					{
						outFile << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
					}
					// Total unique words with number of unique total words followed by total unique words with their frequencies
					unsigned int uniqueCount=0;
					for (i=0; i<pWCount.size(); ++i)
					{
						if( pWCount[i].getCount() == 1 )
							++uniqueCount;
					}
					outFile << "\nTotal Unique Words: " << uniqueCount << std::endl;
					for (i=0; i<pWCount.size(); ++i)
					{
						if( pWCount[i].getCount() == 1 )
							outFile << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
					}
					// 5 most and least frequently used words
					std::sort(pWCount.begin(), pWCount.end(), compareCount);
					const unsigned int numOfVectorToPrint=5;
					outFile << "\n5 most frequently used words: " << std::endl;
					for (i=0; i<numOfVectorToPrint; ++i)
						outFile << pWCount[i].getWord() << " (" << pWCount[i].getCount() << ") ";
					outFile << "\n5 least frequently used words: " << std::endl;
					for (i=0; i<numOfVectorToPrint; ++i)
						outFile << pWCount[pWCount.size()-(numOfVectorToPrint-i)].getWord() << " (" << pWCount[pWCount.size()-(numOfVectorToPrint-i)].getCount() << ") ";
				}
				else
				{
					outFile << "******* Word Analysis in Frequency Order *******" << std::endl;
					std::sort(pWCount.begin(), pWCount.end(), compareCount);
					outFile << "Total Words: " << pTree.length() << std::endl;
					// Total words with number of unique total words followed by total words with their frequencies
					unsigned int i;
					for (i=0; i<pWCount.size(); ++i)
					{
						outFile << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
					}
					// Total unique words with number of unique total words followed by total unique words with their frequencies
					unsigned int uniqueCount=0;
					for (i=0; i<pWCount.size(); ++i)
					{
						if( pWCount[i].getCount() == 1 )
							++uniqueCount;

					}
					outFile << "\nTotal Unique Words: " << uniqueCount << std::endl;
					for (i=0; i<pWCount.size(); ++i)
					{
						if( pWCount[i].getCount() == 1 )
							outFile << std::left << std::setw(WIDTH) << pWCount[i].getWord() << std::right << std::setw(ENDWIDTH) << "[Freq: " << pWCount[i].getCount() << "]" << std::endl;
					}
					// 5 most and least frequently used words
					const unsigned int numOfVectorToPrint=5;
					outFile << "\n5 most frequently used words: " << std::endl;
					for (i=0; i<numOfVectorToPrint; ++i)
						outFile << pWCount[i].getWord() << " (" << pWCount[i].getCount() << ") ";
					outFile << "\n5 least frequently used words: " << std::endl;
					for (i=0; i<numOfVectorToPrint; ++i)
						outFile << pWCount[pWCount.size()-(numOfVectorToPrint-i)].getWord() << " (" << pWCount[pWCount.size()-(numOfVectorToPrint-i)].getCount() << ") ";
				}
				outFile.close();
			}
				break;
			case 5:
			{
				exit(0);
			}
		}
	}
}

int main()
{
	// Instantiation of the object for BST.
	Choi_BST< std::string > charTree;
	// The vector WCount passed by WordCounter class.
	std::vector< WordCounter > WCount;
	// filename to read a text file.
	std::string filename;
	std::cout << "Enter the filename to read: ";
	std::cin >> filename;
	std::ifstream inFile;
	// In the case that the file is not read.
	if (!inFile)
	{
		std::cout << "Cannot open the file.";
		exit(-1); // terminate with error.
	}
	// Read a text file and stores the words in the BST and vector with frequency of the word usage.
	inFile.open(filename.c_str());
	std::string word;
	std::string token;
	while(inFile >> word)
	{
		//std::cout << word << std::endl;
		unsigned int i, start=0, end;
		bool keepTheWord, combinedWord=false;
		for (i=0; i< word.length(); ++i)
		{
			end = word.length()-1;
			if (isFineToKeep(word[i]) == false) // word case 1: word not to keep (i.e. punctuations and digits)
			{
				keepTheWord = false;
				token = word.erase(i--, 1);
			}
			else if (isFineToKeep(word[i+1]) == false && isalpha(word[i])) //  word case 2: word that has punctuations (e.g. [hey]]])
			{
				//std::cout << "Check4" << std::endl;
				keepTheWord = true;
				//token = word.substr(start, i-start);
				word.erase(i+1, 1);
				--i;
			}
			else // word case 3: word to keep (1) word with hyphen word-word-word (2) word'word
			{
				keepTheWord = true;
				if (word[i] == '-' && isalpha(word[i+1])) // (1) word with hyphen word-word-word: take care of word before '-'
				{
					combinedWord = true;
					//std::cout << "Check3" << std::endl;
					keepTheWord = false;
					token = word.substr(start, i-start);

					token.erase(std::remove(token.begin(), token.end(), '\0'),token.end());
					//std::cout << token << token.length() << std::endl;
					WordCounter object(convertToLower(token));
					insertUnique(WCount, object);
					charTree.insertNode(convertToLower(token));
					word.erase(i--,1);
					start = i+1;
				}
				else if(word[i]=='-' && !isalpha(word[i+1])) // remove if digits-punctuation, digits-digits, or punctuation-punctuation
				{
					token = word.erase(i--,1);
				}
				else if(isalpha(word[i]) && combinedWord == false) // keep the word if the word has neither punctuation nor digit and is
				{												   // not a combined word.
					//std::cout << "Check1" << std::endl;
					token = word;
				}
				else if(i == end && combinedWord == true)  // (1) word with hyphen word-word-word: take care of word at the end.
				{
					//std::cout << "Check2" << std::endl;
					keepTheWord = false;
					token = word.substr(start, end);
					token.erase(std::remove(token.begin(), token.end(), '\0'),token.end());
					//std::cout << token << token.length() << std::endl;
					WordCounter object(convertToLower(token));
					insertUnique(WCount, object);
					charTree.insertNode(convertToLower(token));
				}
				else if(word[i] == '\'' && word[i+1] == '\0' && combinedWord == false) // remove if it has single ' without word
				{
					keepTheWord = false;
					word.erase(i--,1);
				}

			}

		}
		if( keepTheWord == true && combinedWord == false )
		{

			token.erase(std::remove(token.begin(), token.end(), '\0'),token.end());
			//std::cout << token << token.length() << std::endl;
			WordCounter object(convertToLower(token));
			insertUnique(WCount, object);
			charTree.insertNode(convertToLower(token));
		}
	}
	inFile.close(); // inFile close.
	wordAnalysis(charTree, WCount, filename); // word frequency analysis output
	charTree.empty(); // empty all the nodes in the tree.
	return 0;
}
