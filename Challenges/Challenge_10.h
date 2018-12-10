#pragma once
#include "Challenge.h"
class Challenge_10 : public Challenge
{
public:
	Challenge_10() = default;
	~Challenge_10() = default;
	void Part1() override;
	void Part2() override;

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

	struct LightPoint
	{
		Int2 startPosition;
		Int2 velocity;
	};
};

