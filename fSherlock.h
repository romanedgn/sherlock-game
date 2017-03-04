// This is the game logic: no view code or direct user interaction.
// It defines a very simple "guess the code" game, inspired by the classic Mastermind game. 

#pragma once

// to comply with Unreal coding standards
using FText = std::string;
using int32 = int;

enum class eGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Contains_Digit,
	Wrong_Length
};

class fSherlock 
{
public:
	fSherlock(); // default constructor
	void Reset();

	// getter methods:
	int32 GetMax_Tries() const;
	int32 GetCurrent_Try() const;
	FText GetSecret_Code(); 
	bool IsGameWon();

	// game methods:
	int32 SetCodeLength(int32 Difficulty);
	FText GenerateSecretCode();
	FText SubmitValidGuess(FText Guess);
	eGuessStatus CheckGuessValidity(FText Guess);

	// helper methods
	bool IsNumber(FText Word);
	bool IsIsogram(FText Word);
	int32 CountLines();

private:
	int32 Max_Tries;
	int32 Current_Try;
	int32 Code_Length;
	FText Secret_Code; //initialised in the secret code generation function
	bool bGuess_Validity;
	bool bGameIsWon;
};