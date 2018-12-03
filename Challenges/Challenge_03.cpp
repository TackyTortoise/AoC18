#include "stdafx.h"
#include "Challenge_03.h"

Challenge_03::Challenge_03() = default;
Challenge_03::~Challenge_03() = default;

void Challenge_03::Part1()
{
	string text = InputReader::GetFileText("../Input/03.txt");
	vector<string>input = InputReader::SplitString(text, "\n");

	map<int, map<int, int>> gridMap;
	regex rgx("[0-9]+");
	smatch match;
	int nums[5];
	int idx;
	for (auto line : input)
	{
		idx = 0;
		while (regex_search(line, match, rgx) && match.size() > 0)
		{
			nums[idx] = stoi(match[0].str());
			++idx;
			line = match.suffix().str();
		}

		for (int x = 0; x < nums[3]; ++ x)
		{
			for (int y = 0; y < nums[4]; ++y)
			{
				++gridMap[nums[1] + x][(nums[2] + y)];
			}
		}
	}

	int result = 0;
	for (auto outerPair : gridMap)
	{
		for (auto pair : outerPair.second) 
		{
			if (pair.second >= 2)
				++result;
		}
	}
	cout << result << endl;
}

void Challenge_03::Part2()
{
	string text = InputReader::GetFileText("../Input/03.txt");
	vector<string>input = InputReader::SplitString(text, "\n");

	map<int, map<int, unordered_set<int>>> gridMap;
	regex rgx("[0-9]+");
	smatch match;
	int nums[5];
	int idx;
	set<int> availableSingleCuts;
	for (auto line : input)
	{
		idx = 0;
		while (regex_search(line, match, rgx) && match.size() > 0)
		{
			nums[idx] = stoi(match[0].str());
			++idx;
			line = match.suffix().str();
		}

		for (int x = 0; x < nums[3]; ++x)
		{
			for (int y = 0; y < nums[4]; ++y)
			{
				gridMap[nums[1] + x][(nums[2] + y)].insert(nums[0]);
			}
		}
		availableSingleCuts.insert(nums[0]);
	}

	for (auto outerPair : gridMap)
	{
		for (auto pair : outerPair.second)
		{
			if (pair.second.size() >= 2)
			{
				for (auto cut: pair.second)
				{
					if (find(availableSingleCuts.begin(), availableSingleCuts.end(), cut) != availableSingleCuts.end())
						availableSingleCuts.erase(cut);
				}
			}
		}
	}
	cout << *availableSingleCuts.begin() << endl;
}
