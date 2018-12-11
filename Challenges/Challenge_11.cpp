#include "stdafx.h"
#include "Challenge_11.h"

void Challenge_11::Part1()
{
	int serial = 2866;
	int width, height;
	width = height = 300;
	int size = width * height;
	int* grid = new int[size];
	int maxTotalPower = numeric_limits<int>::min();
	int bestIndex = -1;
	memset(grid, 0, size * sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		int x = i % width + 1;
		int y = i / width + 1;

		if (x <= 1 || x >= width || y <= 1 || y >= height)
			continue;

		//Top left
		int index = i - width - 1;
		int totalPower = GetPowerLevel(index, width, serial, grid);

		//Top
		++index;
		totalPower += GetPowerLevel(index, width, serial, grid);

		//Top right
		++index;
		totalPower += GetPowerLevel(index, width, serial, grid);
												  
		//Left									  
		index = i - 1;							  
		totalPower += GetPowerLevel(index, width, serial, grid);
												  
		//Center								  
		++index;								  
		totalPower += GetPowerLevel(index, width, serial, grid);
												  
		//Right									  
		++index;								  
		totalPower += GetPowerLevel(index, width, serial, grid);
												  
		//Bottom left							  
		index = i + width - 1;					  
		totalPower += GetPowerLevel(index, width, serial, grid);
												  
		//Bottom								  
		++index;								  
		totalPower += GetPowerLevel(index, width, serial, grid);
												  
		//Bottom right							  
		++index;								  
		totalPower += GetPowerLevel(index, width, serial, grid);

		if (totalPower > maxTotalPower)
		{
			maxTotalPower = totalPower;
			bestIndex = i - width - 1;
		}
	}

	int x = bestIndex % width + 1;
	int y = bestIndex / width + 1;
	cout << "Best: " << x << ", " << y << " with power " << maxTotalPower << endl;
	delete[] grid;
}

//TODO: Optimize this when I have too much time, check if area of half size is already calculated and add them together?
void Challenge_11::Part2()
{
	int serial = 2866;
	int width, height;
	width = height = 300;
	int size = width * height;
	int* grid = new int[size];
	int maxTotalPower = numeric_limits<int>::min();
	int bestIndex = -1;
	int bestSize = -1;
	memset(grid, 0, size * sizeof(int));

	for (int s = 1; s < 300; ++s)
	{
		int halfSize = s / 2;
		for (int i = 0; i < size; ++i)
		{
			int x = i % width + 1;
			int y = i / width + 1;

			if (x <= halfSize || x > width - halfSize || y <= halfSize || y >= height - halfSize)
				continue;

			//Top left
			int index = i - halfSize * width - halfSize;
			int totalPower = 0;
			for (int j = 0; j < s * s; ++j)
			{
				if (j > 0 && j % s == 0)
					index += width - s + 1;
				else if (j > 0)
					++index;
				totalPower += GetPowerLevel(index, width, serial, grid);
			}

			if (totalPower > maxTotalPower)
			{
				maxTotalPower = totalPower;
				bestIndex = i - halfSize * width - halfSize;
				bestSize = s;
			}
		}
	}

	int x = bestIndex % width + 1;
	int y = bestIndex / width + 1;
	cout << "Best: " << x << "," << y << "," << bestSize << " with power " << maxTotalPower << endl;
	delete[] grid;
}

int Challenge_11::GetPowerLevel(int i, int width, int serial, int* grid)
{
	if (grid[i] != 0)
		return grid[i];

	int x = i % width + 1;
	int y = i / width + 1;
	int rackID = x + 10;
	int powerLevel = (rackID * y + serial) * rackID;
	if (powerLevel < 100)
		powerLevel = 0;
	else
		powerLevel = powerLevel / 100 % 10;

	grid[i] = powerLevel - 5;
	return powerLevel - 5;
}
