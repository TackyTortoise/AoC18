#pragma once
#include "Challenge.h"
class Challenge_17 : public Challenge
{
public:
	Challenge_17() = default;
	~Challenge_17() = default;
	
	void Part1() override;
	void Part2() override;

	void PrintField(char* field, int width, int height);
	int FirstHitDown(char* field, int startIndex, int width, int height);
	int FirstHitLeft(char* field, int startIndex, int width, int height);
	int FirstHitRight(char* field, int startIndex, int width, int height);
};

