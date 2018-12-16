#pragma once
#include "Challenge.h"
class Challenge_16 : public Challenge
{
public:
	Challenge_16() = default;
	~Challenge_16() = default;

	void Part1() override;
	void Part2() override;

	struct OpCode
	{
		string code;
		function<vector<int>(vector<int>, int, int, int)> execute;
		set<int> possiblePositions;
		int actualPosition;
	};
};

