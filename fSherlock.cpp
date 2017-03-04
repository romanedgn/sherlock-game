#pragma once
#include "stdafx.h"

// to comply with Unreal coding standards
using FText = std::string;
using int32 = int;
#define TMap std::map

int32 fSherlock::GetCurrent_Try() const { return Current_Try; }
FText fSherlock::GetSecret_Code() { return Secret_Code; }
bool fSherlock::IsGameWon() { return bGameIsWon; }

// default constructor
fSherlock::fSherlock() { Reset(); }

void fSherlock::Reset()
{
	Current_Try = 1;
	bGameIsWon = false;
	return;
}

// link the difficulty level chosen by player to the length of the code
int32 fSherlock::SetCodeLength(int32 Difficulty)
{
	TMap<int32, int32> LevelToWordLength{ { 1, 4 },{ 2, 5 },{ 3, 6 } };
	Code_Length = LevelToWordLength[Difficulty];

	return Code_Length;
}

// link the length of the secret code to the number of maximum tries the player has
int32 fSherlock::GetMax_Tries() const 
{ 
	TMap<int32, int32> CodeLengthToMaxTries{ {4, 7}, {5, 10}, {6, 14} };
	return CodeLengthToMaxTries[Secret_Code.length()]; 
}

// generate a random word from our isogram list to define the secret code
FText fSherlock::GenerateSecretCode()
{
	std::ifstream Word_List;
	Word_List.open("isograms.txt");
	int32 Lines_File = CountLines();
	int32 Word_Index = rand() % Lines_File;

	if (!Word_List.is_open())
	{
		std::cout << "There was a problem opening the file isograms.txt.";
		return "";
	}
	else
	{
		// load word list in memory
		std::vector<FText> Words;
		FText Temp_Word;
		while (std::getline(Word_List, Temp_Word))
		{
			Words.push_back(Temp_Word);
		}

		// select a random word from the list
		Secret_Code = Words[Word_Index];

		// check that the word selected is of the right length 
		while (Code_Length != Secret_Code.length()) 
		{
			Word_Index = rand() % Lines_File; 
			Secret_Code = Words[Word_Index];
		}

		return Secret_Code;
	}
}

// count how many lines are in the file isograms.txt
int32 fSherlock::CountLines()
{
	int32 Number_Lines = 0;
	FText Line;
	std::ifstream Word_List("isograms.txt");

	while (std::getline(Word_List, Line))
	{
		++Number_Lines;
	}

	return Number_Lines;
}

eGuessStatus fSherlock::CheckGuessValidity(FText Guess)
{
	std::transform(Guess.begin(), Guess.end(), Guess.begin(), ::tolower); // convert uppercase characters of Guess into lowercase

	if (!IsIsogram(Guess))
	{
		return eGuessStatus::Not_Isogram;
	}
	else if (IsNumber(Guess)) 
	{
		return eGuessStatus::Contains_Digit;
	}
	else if (Guess.length() != Secret_Code.length())
	{
		return eGuessStatus::Wrong_Length;
	}
	else // assumes Guess is valid 
	{
		return eGuessStatus::OK;
	}
}

// submit valid guess and compare it to the secret code
FText fSherlock::SubmitValidGuess(FText Guess)
{
	// increment current try
	Current_Try++;

	// prints the hints 
	std::cout << "\nHints: ";

	int32 Word_Length = Guess.length();
	// loop through all letters of guess to compare to code
	for ( int32 i = 0; i < Word_Length; i++)
	{
		for (int32 j = 0; j < Word_Length; j++) // assumes guess and code are the same length
		{
			if (Guess[i] == Secret_Code[j])
			{
				if (i == j)
				{
					std::cout << "X";
				}
				else std::cout << "|";
			} 
		}

		// handle win/lose condition
		if (Guess == Secret_Code)
		{
			bGameIsWon = true;
		}
		else bGameIsWon = false;
	}

	return Guess;
}

// check whether Guess is an isogram
bool fSherlock::IsIsogram(FText Word)
{
	TMap<char, bool> Letter_Seen; // creates the map Letter_Seen, to review all the letters in the Guess
	
	if (Word.length() <= 1) { return true; } // consider guesses of 0 or 1 characters as isograms
	
	for (auto Letter : Word)
	{
		if (Letter_Seen[Letter]) // if the letter is already in the map
		{
			return false; // the guess is not an isogram
		}
		else
		{
			Letter_Seen[Letter] = true; // adds the letter to the map
		}
	}
	return true;
}

// check if Guess contains digits
bool fSherlock::IsNumber(FText Word)
{
	for (auto Letter : Word)
	{
		if (isdigit(Letter))
		{
			return true;
		}
	}
	return false;
}