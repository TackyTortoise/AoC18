#include "stdafx.h"
#include "Challenge_18.h"

void Challenge_18::Part1()
{
	string input = InputReader::GetFileText("../Input/18.txt");
	int width = input.find('\n');
	int height = input.length() / width;
	input.erase(remove(input.begin(), input.end(), '\n'), input.end());
	const int TOTAL_MINUTES = 10;
	for (int min = 0; min < TOTAL_MINUTES; ++min)
	{
		string updatedState = input;
		for (int i = 0; i < width * height; ++i)
		{
			int x = i % width;
			int y = i / width;
			string neighbours;
			//Left
			if (x > 0)
			{
				neighbours += input[i - 1];
				//Left Top
				if (y > 0)
					neighbours += input[i - width - 1];
				//Left Bottom
				if (y < height - 1)
					neighbours += input[i + width - 1];
			}
			//Right
			if (x < width - 1)
			{
				neighbours += input[i + 1];
				//Right top
				if (y > 0)
					neighbours += input[i - width + 1];
				//Right bottom
				if (y < height - 1)
					neighbours += input[i + width + 1];
			}
			//Top
			if (y > 0)
				neighbours += input[i - width];
			//Bottom
			if (y < height - 1)
				neighbours += input[i + width];

			int treeCount = count(neighbours.begin(), neighbours.end(), '|');
			int lumberCount = count(neighbours.begin(), neighbours.end(), '#');
			char current = input[i];
			if (current == '.' && treeCount > 2)
				updatedState[i] = '|';
			else if (current == '|' && lumberCount > 2)
				updatedState[i] = '#';
			else if (current == '#' && !(lumberCount > 0 && treeCount > 0))
				updatedState[i] = '.';
		}
		input = updatedState;
		//InputReader::PrintField(&input[0], width, height);
	}

	int woodAreas = count(input.begin(), input.end(), '|');
	int lumberAreas = count(input.begin(), input.end(), '#');
	cout << "Resource value: " << woodAreas * lumberAreas << endl;
}

void Challenge_18::Part2()
{
	string input = InputReader::GetFileText("../Input/18.txt");
	int width = input.find('\n');
	int height = input.length() / width;
	input.erase(remove(input.begin(), input.end(), '\n'), input.end());
	const int TOTAL_MINUTES = 1000000000;
	vector<string> encountered;
	encountered.push_back(input);
	bool jumped = false;
	for (int min = 0; min < TOTAL_MINUTES; ++min)
	{
		string updatedState = input;
		for (int i = 0; i < width * height; ++i)
		{
			int x = i % width;
			int y = i / width;
			string neighbours;
			//Left
			if (x > 0)
			{
				neighbours += input[i - 1];
				//Left Top
				if (y > 0)
					neighbours += input[i - width - 1];
				//Left Bottom
				if (y < height - 1)
					neighbours += input[i + width - 1];
			}
			//Right
			if (x < width - 1)
			{
				neighbours += input[i + 1];
				//Right top
				if (y > 0)
					neighbours += input[i - width + 1];
				//Right bottom
				if (y < height - 1)
					neighbours += input[i + width + 1];
			}
			//Top
			if (y > 0)
				neighbours += input[i - width];
			//Bottom
			if (y < height - 1)
				neighbours += input[i + width];

			int treeCount = count(neighbours.begin(), neighbours.end(), '|');
			int lumberCount = count(neighbours.begin(), neighbours.end(), '#');
			char current = input[i];
			if (current == '.' && treeCount > 2)
				updatedState[i] = '|';
			else if (current == '|' && lumberCount > 2)
				updatedState[i] = '#';
			else if (current == '#' && !(lumberCount > 0 && treeCount > 0))
				updatedState[i] = '.';
		}
		input = updatedState;

		auto it = find(encountered.begin(), encountered.end(), input);
		if (!jumped && it != encountered.end())
		{
			int lastMin = it - encountered.begin();
			int diff = min - lastMin + 1;
			int toEnd = TOTAL_MINUTES - min;
			int partDiff = toEnd / diff;
			min += partDiff * diff;
			jumped = true;
			cout << "Found loopy boy at minute " << min << " same as min " << lastMin << endl;
		}

		encountered.push_back(input);
	}

	int woodAreas = count(input.begin(), input.end(), '|');
	int lumberAreas = count(input.begin(), input.end(), '#');
	cout << "Resource value: " << woodAreas * lumberAreas << endl;
}
