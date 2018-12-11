#pragma once
#include "Challenge.h"
class Challenge_11 : public Challenge
{
public:
	Challenge_11() = default;
	~Challenge_11() = default;
	void Part1() override;
	void Part2() override;

private:
	int GetPowerLevel(int i, int width, int serial, int* grid);
};

