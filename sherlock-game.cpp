// sherlock-game.cpp : Defines the entry point for the console application.
// This is the console executable, that make use of the class fSherlock.
// It is responsible for all user interaction: for game logic, please see the fSherlock class.

#include "stdafx.h"

// to comply with Unreal coding standards
using FText = std::string;
using int32 = int;

void PrintArt();
int32 SetDifficulty();
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintSummary();

// global variables
fSherlock SherlockGame;
FText Guess;
int32 Level_Chosen;

int32 main()
{
	bool bPlayAgain = false;
	do
	{
		PrintArt();
		SetDifficulty();
		SherlockGame.GenerateSecretCode();
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintArt()
{

	std::cout << "___________________________¶¶¶\n";
	std::cout << "_______________________¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "______________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "____________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "__________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_____________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "___________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "__________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_____________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "____________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶___¶¶¶\n";
	std::cout << "____________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "____________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "___________¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "__________¶¶____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_________¶¶¶____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_________¶¶¶____¶¶¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "¶¶¶¶¶¶¶__¶¶______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_¶¶¶¶¶__¶¶_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_¶¶¶¶¶__¶¶______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "__¶¶¶¶¶¶¶_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "___¶¶¶¶¶_________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_________________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "________________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "______________________¶¶¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "_____________________¶¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "____________________¶¶¶¶¶¶¶¶¶¶\n";
	std::cout << "____________________¶¶¶¶¶¶¶¶\n";
	std::cout << "___________________¶¶¶¶¶\n\n";

	std::cout << "\tWelcome Sherlock.\n\n\tDo you think you can break my code?\n\n";
	return;
}

int32 SetDifficulty()
{
	std::cout << "Fist, select a level of difficulty."; 
	do
	{
		std::cout << "\nPlease enter 1, 2 or 3: ";
		std::cin >> Level_Chosen;

		// clear cin buffer 
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (Level_Chosen != 1 && Level_Chosen != 2 && Level_Chosen != 3);

	SherlockGame.SetCodeLength(Level_Chosen);

	return Level_Chosen;
}

void PrintIntro()
{
	FText Code = SherlockGame.GetSecret_Code();
	std::cout << "\n\nYou chose the difficulty level "<< Level_Chosen << ". Here are the rules:\n\n";
	std::cout << "- The code is a " << Code.length() << " letter isogram.\n\n";
	std::cout << "- You have " << SherlockGame.GetMax_Tries() << " tries: once you used them all, you lose.\n\n";
	std::cout << "- Hints: if you receive an X, one letter of your guess is right and and at the right place. If you receive an |, one letter of your guess is right, but at the wrong place.";
	return;
}

void PlayGame()
{
	SherlockGame.Reset();

	int32 My_Max_Tries = SherlockGame.GetMax_Tries();
	while (!SherlockGame.IsGameWon() && SherlockGame.GetCurrent_Try() <= My_Max_Tries)
	{
		std::cout << "\n\nTry " << SherlockGame.GetCurrent_Try() << ".\n";
		GetValidGuess();
		SherlockGame.SubmitValidGuess(Guess);

		if (!SherlockGame.IsGameWon() && SherlockGame.GetCurrent_Try() <= My_Max_Tries)
		{
			std::cout << "\nYou have " << (My_Max_Tries +1) - SherlockGame.GetCurrent_Try() << " tries left.";
		}	
	}

	PrintSummary();

	return;
}


FText GetValidGuess()
{
	eGuessStatus GuessValidity = eGuessStatus::Invalid_Status;
	FText Code = SherlockGame.GetSecret_Code();

	do {
		// get guess from user
		std::cout << "Please enter your guess: ";
		std::getline (std::cin,Guess);

		// check guess validity and gives user some feedback
		GuessValidity = SherlockGame.CheckGuessValidity(Guess);
		switch (GuessValidity)
		{
		case eGuessStatus::Contains_Digit:
			std::cout << "\nPlease enter a word containing letters only. ";
			break;
		case eGuessStatus::Not_Isogram:
			std::cout << "\nPlease enter a word without repeating letters. ";
			break;
		case eGuessStatus::Wrong_Length:
			std::cout << "\nPlease enter a word of " << Code.length() << " letters. ";
			break;
		default:
			return Guess;
			break;
		}
	} while (GuessValidity != eGuessStatus::OK);
	
	return Guess;
}

void PrintSummary()
{
	if (SherlockGame.IsGameWon())
	{
		std::cout << "\n\nYou're a smart cookie, you cracked the code!";
	}
	else
	{
		std::cout << "\n\nToo bad! Better luck next time.";
	}
}

bool AskToPlayAgain()
{
	std::cout << "\n\nDo you want to play again? [Y/N]\n";
	FText User_Response;
	std::getline(std::cin, User_Response);
	return (User_Response[0] =='Y' || User_Response[0] == 'y');
}



