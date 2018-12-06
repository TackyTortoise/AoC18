#pragma once
#include "Challenge.h"

struct Int2;

class Challenge_06 : public Challenge
{
public:
	Challenge_06() = default;
	~Challenge_06() = default;
	void Part1() override;
	void Part2() override;
	int GetArea(int start, int* grid, int width, int height, vector<int>& allVisitedNodes);

private:
	struct Int2
	{
		Int2() { x = 0; y = 0; }
		Int2(int xx, int yy) { x = xx; y = yy; }

		int x;
		int y;

		const Int2& operator-(const Int2& o)
		{
			return Int2(x - o.x, y - o.y);
		}

		const Int2& operator+(const Int2& o)
		{
			return Int2(x + o.x, y + o.y);
		}

		int GetIndex(int width)
		{
			return x + y * width;
		}

		int ManhattenDistance(int ox, int oy)
		{
			return abs(ox - x) + abs(oy - y);
		}
	};
};

