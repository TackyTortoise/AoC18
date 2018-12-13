#pragma once
#include "Challenge.h"
class Challenge_13 : public Challenge
{
public:
	Challenge_13() = default;
	~Challenge_13() = default;
	void Part1() override;
	void Part2() override;

	struct Cart
	{
		int cartNumber;
		int currentIndex;
		int currentDirection = 0; // 0 = right, 1 = down, 2 = left = 3 = up
		int turnIndex = 0;

		int GetNextIndex(int gridWidth) const
		{
			if (currentDirection == 0)
				return currentIndex + 1;
			else if (currentDirection == 1)
				return currentIndex + gridWidth;
			else if (currentDirection == 2)
				return currentIndex - 1;
			else if (currentDirection == 3)
				return currentIndex - gridWidth;

			return -1;
		}
	};
};

