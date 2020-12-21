#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

//INITAL_MENU
int menu()
{
	int choice;
	bool valid;

	cout << "Choose a topic" << endl;
	cout << "1 - Countries" << endl;
	cout << "2 - States" << endl;
	cout << "3 - Fruits" << endl;
	cout << "4 - Songs" << endl;
	cout << "5 - Movies" << endl;
	cout << "6 - Exit" << endl;
	
	valid = false;
	while (!valid)
	{
		cin >> choice;
		if (choice < 7 && choice > 0)
		{
			valid = true;
		}
		else
		{
			cout << "That is not a valid option, please try again" << endl;
		}
	}

	return choice;
}

//GENERATING_A_RANDOM_NUMBER_AND_KEYWORD
string randNum(string topic[20],string fileName,string prevWord)
{
	bool notCopy = false;
	string keyword;
	while (!notCopy)
	{
		int seed;
		srand((int)time(NULL));
		seed = rand() % 20;

		int x = 0;
		ifstream file;
		file.open(fileName.c_str());

		if (!file)
		{
			cout << "Cannot open text file." << endl;
		}
		else
		{
			while (!file.eof() && x < 20)
			{
				getline(file, topic[x]);
				x++;
			}
		}
		file.close();

		if (prevWord != topic[seed])
		{
			keyword = topic[seed];
			notCopy = true;
		}
	}
	return keyword;
}

char guess()
{
	char currentGuess;
	bool valid = false;

	while(!valid)
	{	
		cout << "Guess a letter, please make all guesses CAPITALIZED" << endl;
		cin >> currentGuess;
	
		if(isalpha(currentGuess) && isupper(currentGuess))
		{
			valid = true;
		}
	}
	
	return currentGuess;
}

void printout(int attempts);

//START_OF_INT_MAIN
int main()
{
	int topic;
	int topicLength;
	string fileToOpen;
	string category[20];
	string keyword;
	char guessedletter;
	bool win = false;
	bool hint = false;
	int counter;
	int correct;
	int attempts = 6;
	string guessed;
	bool finished = false;
	string prevWord;

	while (finished == false)
	{
		topic = menu();

		if (topic == 6)
		{
			cout << "Goodbye." << endl;
			return 0;
		}

		if (topic == 1)
		{
			cout << "COUNTRIES" << endl;
			fileToOpen = "countries.txt";
		}

		if (topic == 2)
		{
			cout << "STATES" << endl;
			fileToOpen = "states.txt";
		}

		if (topic == 3)
		{
			cout << "FRUITS" << endl;
			fileToOpen = "fruits.txt";
		}

		if (topic == 4)
		{
			cout << "SONGS" << endl;
			fileToOpen = "songs.txt";
		}

		if (topic == 5)
		{
			cout << "MOVIES" << endl;
			fileToOpen = "movies.txt";
		}

		//GAME_START
		keyword = randNum(category, fileToOpen, prevWord);

		

		//TURN_STRING_INTO_CHARACTER_ARRAY
		int keylength = keyword.length();
		char keyarray[keylength + 1];

		strcpy(keyarray, keyword.c_str());

		char playspace[keylength + 1];

		for (int t = 0; t < keylength; t++)
		{
			if (int(keyarray[t]) == 32)
			{
				playspace[t] = ' ';
			}
			else
			{
				playspace[t] = '-';
			}
		}
		//PREEMPTIVE_CLEAR_AND_RESET
		system("clear");
		bool win = false;
		guessed = "";
		attempts = 6;

		//ACTUAL_GAMEPLAY
		while (!win)
		{
			cout << "WHEN YOU HAVE A FULL GUESS, TYPE OUT ONE LETTER AT A TIME" << endl
				<< "EACH INCORRECT LETTER IN A GUESS COUNTS AS ONE ATTEMPT" << endl
				<< "REPEAT LETTERS WILL COUNT AGAINST YOU SO BE CAREFUL" << endl << endl;
			cout << "GUESSED LETTERS: " << guessed << endl;
			counter = 0;
			correct = 0;
			cout << "You Have " << attempts << " Attempts Remaining" << endl;
			//PRINTOUT_FOR_ASCIIMAN
			printout(attempts);

			for (int n = 0; n < keylength; n++)
			{
				cout << playspace[n];
			}
			//		cout << endl << keyword << endl;

			cout << endl << "=======================================================" << endl;

			if (attempts == 2)
			{
				cout << "Common letters to try for all words are: R, S, T, L, N, and E" << endl;
			}
			if (attempts == 1 && hint == false)
			{
				int L = 0;
				for (int r = 0; r < keylength; r++)
				{
					if (playspace[r] == '-')
					{
						L = r;
						break;
					}
				}
				cout << "Have you tried the letter: " << keyarray[L] << "?" << endl;
				hint = true;
			}
			if (attempts == 0)
			{
				cout << "YOU LOSE" << endl;
				break;
			}

			guessedletter = guess();
			cout << "YOU GUESSED: " << guessedletter << endl;
			guessed = guessed + guessedletter + ",";

			//CHECK_IF_GUESS_HOLDS_UP
			for (int p = 0; p < keylength; p++)
			{
				if (int(playspace[p]) == 45)
				{
					if (keyarray[p] == guessedletter)
					{
						playspace[p] = guessedletter;
						counter++;
						correct++;
					}
				}
				else
				{
					counter++;
				}
			}

			if (correct == 0)
			{
				attempts--;
			}

			if (counter == keyword.length())
			{
				win = true;
			}

			system("clear");
		}

		cout << "YOU WIN" << endl;
		if (attempts == 6)
		{
			cout << "A PERFECT GAME. WELL DONE." << endl;
		}
		
		char areyoudone;
		bool validchoice = false;
		while (validchoice == false)
		{
			cout << "Would you like to play again? (Y/N)" << endl;
			cin >> areyoudone;
			if(areyoudone == 'N')
			{ 
				validchoice = true;
				finished = true;
			}
			if(areyoudone == 'Y')
			{
				validchoice = true;
			}
			else
			{
				cout << "That is not a valid answer, please try again." << endl;
			}
		}
	}
	return 0;
}

void printout(int attempts)
{
	if (attempts == 0)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            (   )" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            - | - " << endl;
		cout << "          |           |  |  | " << endl;
		cout << "          |              |" << endl;
		cout << "          |             / 7 " << endl;
		cout << "          |            /   7 " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
	if (attempts == 1)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            (   )" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            - | - " << endl;
		cout << "          |           |  |  | " << endl;
		cout << "          |              |" << endl;
		cout << "          |             / " << endl;
		cout << "          |            /  " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
	if (attempts == 2)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            (   )" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            - | - " << endl;
		cout << "          |           |  |  | " << endl;
		cout << "          |              |" << endl;
		cout << "          |               " << endl;
		cout << "          |               " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
	if (attempts == 3)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            (   )" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            - |" << endl;
		cout << "          |           |  |" << endl;
		cout << "          |              |" << endl;
		cout << "          |               " << endl;
		cout << "          |               " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
	if (attempts == 4)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            (   )" << endl;
		cout << "          |             ---" << endl;
		cout << "          |              |" << endl;
		cout << "          |              |" << endl;
		cout << "          |              |" << endl;
		cout << "          |               " << endl;
		cout << "          |               " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
	if (attempts == 5)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |             ---" << endl;
		cout << "          |            (   )" << endl;
		cout << "          |             ---" << endl;
		cout << "          |              " << endl;
		cout << "          |              " << endl;
		cout << "          |              " << endl;
		cout << "          |              " << endl;
		cout << "          |              " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
	if (attempts == 6)
	{
		cout << "=======================================================" << endl << endl;
		cout << "          ----------------" << endl;
		cout << "          |              |" << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |            " << endl;
		cout << "          |" << endl;
		cout << "        -----" << endl << endl;
		cout << "=======================================================" << endl;
	}
}