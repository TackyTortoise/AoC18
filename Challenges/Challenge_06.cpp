#include "stdafx.h"
#include "Challenge_06.h"

void Challenge_06::Part1()
{
	string inputStr = InputReader::GetFileText("../Input/06.txt");
	vector<string> input = InputReader::SplitString(inputStr, "\n");
	vector<Int2> coordinates;
	Int2 minCoord(numeric_limits<int>::max(), numeric_limits<int>::max()), maxCoord(numeric_limits<int>::min(), numeric_limits<int>::min());
	for (string line : input)
	{
		int commaPos = line.find(',');
		Int2 n(stoi(line.substr(0, commaPos)), stoi(line.substr(commaPos + 2)));
		if (n.x < minCoord.x)
			minCoord.x = n.x;
		if (n.y < minCoord.y)
			minCoord.y = n.y;
		if (n.x > maxCoord.x)
			maxCoord.x = n.x;
		if (n.y > maxCoord.y)
			maxCoord.y = n.y;
		coordinates.push_back(n);
	}

	int width = maxCoord.x - minCoord.x + 1;
	int height = maxCoord.y - minCoord.y + 1;
	int* grid = new int[width * height];

	for (int i = 0; i < width * height; ++i)
	{
		auto x = i % width;
		auto y = i / width;
		x += minCoord.x;
		y += minCoord.y;
		auto shortestDistance = numeric_limits<int>::max();
		for (auto c = 0; c < coordinates.size(); ++c)
		{
			auto dist = coordinates[c].ManhattenDistance(x, y);
			if (dist < shortestDistance)
			{
				shortestDistance = dist;
				grid[i] = c;
			}
			else if (dist == shortestDistance)
				grid[i] = -1;
		}
	}

	map<int, int> values;
	vector<int> invalid;
	for (int i = 0; i < width * height; ++i)
	{
		int x = i % width;
		int y = i / height;
		if ((x == 0 || x == width - 1 || y == 0 || y == height - 1) && find(invalid.begin(), invalid.end(), grid[i]) == invalid.end())
			invalid.push_back(grid[i]);
		values[grid[i]]++;
	}

	int maxArea = numeric_limits<int>::min();
	for (auto value : values)
	{
		if (value.second > maxArea && find(invalid.begin(), invalid.end(), value.first) == invalid.end())
			maxArea = value.second;
	}

	cout << maxArea << endl;
}


void Challenge_06::Part2()
{
	string inputStr = InputReader::GetFileText("../Input/06.txt");
	vector<string> input = InputReader::SplitString(inputStr, "\n");
	vector<Int2> coordinates;
	Int2 minCoord(numeric_limits<int>::max(), numeric_limits<int>::max()), maxCoord(numeric_limits<int>::min(), numeric_limits<int>::min());
	for (string line : input)
	{
		int commaPos = line.find(',');
		Int2 n(stoi(line.substr(0, commaPos)), stoi(line.substr(commaPos + 2)));
		if (n.x < minCoord.x)
			minCoord.x = n.x;
		if (n.y < minCoord.y)
			minCoord.y = n.y;
		if (n.x > maxCoord.x)
			maxCoord.x = n.x;
		if (n.y > maxCoord.y)
			maxCoord.y = n.y;
		coordinates.push_back(n);
	}

	int width = maxCoord.x - minCoord.x + 1;
	int height = maxCoord.y - minCoord.y + 1;
	int* grid = new int[width * height];
	memset(grid, 0, width * height * sizeof(int));
	for (int i = 0; i < width * height; ++i)
	{
		auto x = i % width;
		auto y = i / width;
		x += minCoord.x;
		y += minCoord.y;
		for (auto c = 0; c < coordinates.size(); ++c)
		{
			auto dist = coordinates[c].ManhattenDistance(x, y);
			grid[i] += dist;
		}
	}

	int max = 10000;
	int total = 0;
	for (int i = 0; i < width * height; ++i)
	{
		if (grid[i] < max)
			++total;
	}

	cout << total << endl;
}

//Why the hell did I write this stuff, for some reason I assumed there could be multiple regions of the same value split apart, which is dumb, leaving this code here to learn from it and maybe use for something in the future
int Challenge_06::GetArea(int start, int* grid, int width, int height, vector<int>& allVisitedNodes)
{
	vector<int> visitedNodes;
	vector<int> foundNeighboors;
	int foundNeighboor = -1;
	vector<int> nodesToCheck = { start };
	bool invalid = true;
	do
	{
		foundNeighboor = 0;
		vector<int> newNodesToCheck;
		for (auto nodeIndex : nodesToCheck)
		{
			int x = nodeIndex % width;
			int y = nodeIndex % height;
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
				invalid = true;

			//Top
			if (y > 0)
			{
				if (grid[nodeIndex - width] == grid[start] && find(visitedNodes.begin(), visitedNodes.end(), nodeIndex - width) == visitedNodes.end())
				{
					newNodesToCheck.push_back(nodeIndex - width);
					++foundNeighboor;
					foundNeighboors.push_back(nodeIndex - width);
				}
				visitedNodes.push_back(nodeIndex - width);
			}
			//Under
			if (y < width)
			{
				if (grid[nodeIndex + width] == grid[start] && find(visitedNodes.begin(), visitedNodes.end(), nodeIndex + width) == visitedNodes.end())
				{
					newNodesToCheck.push_back(nodeIndex + width);
					++foundNeighboor;
					foundNeighboors.push_back(nodeIndex + width);
				}
				visitedNodes.push_back(nodeIndex + width);
			}
			//Left
			if (x > 0)
			{
				if (grid[nodeIndex - 1] == grid[start] && find(visitedNodes.begin(), visitedNodes.end(), nodeIndex - 1) == visitedNodes.end())
				{
					newNodesToCheck.push_back(nodeIndex - 1);
					++foundNeighboor;
					foundNeighboors.push_back(nodeIndex - 1);
				}
				visitedNodes.push_back(nodeIndex - 1);
			}
			//Right
			if (x < width)
			{
				if (grid[nodeIndex + 1] == grid[start] && find(visitedNodes.begin(), visitedNodes.end(), nodeIndex + 1) == visitedNodes.end())
				{
					newNodesToCheck.push_back(nodeIndex + 1);
					++foundNeighboor;
					foundNeighboors.push_back(nodeIndex + 1);
				}
				visitedNodes.push_back(nodeIndex + 1);
			}
		}
		nodesToCheck = newNodesToCheck;
	} while (foundNeighboor > 0);

	return invalid ? -1 : foundNeighboors.size();
}
