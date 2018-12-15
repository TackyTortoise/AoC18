#pragma once
#include "Challenge.h"
class Challenge_15 : public Challenge
{
public:
	Challenge_15() = default;
	~Challenge_15() = default;
	
	void Part1() override;
	void Part2() override;

	struct Unit
	{
		char type;
		int currentIndex;
		int hp;

		vector<int> GetSurroundingIndeces(int width, int height)
		{
			vector<int> r;
			int x = currentIndex % width;
			int y = currentIndex / width;
			if (y > 0)
				r.push_back(currentIndex - width);
			if (x > 0)
				r.push_back(currentIndex - 1);
			if (x < width - 1)
				r.push_back(currentIndex + 1);
			if (y < height - 1)
				r.push_back(currentIndex + width);
			return r;
		}

		int ManhattenDistance(int i, int width)
		{
			int x = currentIndex % width;
			int y = currentIndex / width;
			int ox = i % width;
			int oy = i / width;
			return abs(x - ox) + abs(y - oy);
		}
	};


};

