#include "stdafx.h"
#include "Challenge_07.h"

void Challenge_07::Part1()
{
	auto input = InputReader::GetRawLines("../Input/07.txt");
	map<char, vector<char>> tree;
	for (auto line : input)
	{
		char step1 = line[5];
		char step2 = line[36];
		if (tree.find(step1) == tree.end())
			tree.insert(pair<int, vector<char>>(step1, {}));
		tree[step2].push_back(step1);
	}

	set<char> availableSteps;
	string result;
	do
	{
		for (auto step : availableSteps)
		{
			tree.erase(step);
			for (auto& otherStep : tree)
			{
				auto found = find(otherStep.second.begin(), otherStep.second.end(), step);
				if (found != otherStep.second.end())
					otherStep.second.erase(found);
			}
		}

		availableSteps.clear();

		for (auto step : tree)
		{
			if (step.second.size() == 0)
				availableSteps.insert(step.first);
		}

		if (availableSteps.size() > 0)
		{
			char first = *availableSteps.begin();
			result += first;
			availableSteps = { first };
		}
	} while (availableSteps.size() > 0);

	cout << result << endl;
}

void Challenge_07::Part2()
{
	auto input = InputReader::GetRawLines("../Input/07.txt");
	map<char, vector<char>> tree;
	for (auto line : input)
	{
		char step1 = line[5];
		char step2 = line[36];
		if (tree.find(step1) == tree.end())
			tree.insert(pair<int, vector<char>>(step1, {}));
		tree[step2].push_back(step1);
	}

	map<char, int> timers;
	string result;
	int maxWorkers = 5;
	int currentSecond = 0;
	do
	{
		if (timers.size() > 0)
			++currentSecond;

		for (auto& timer : timers)
		{
			--timer.second;
			if (timer.second == 0)
			{
				result += timer.first;
				tree.erase(timer.first);
				for (auto& otherStep : tree)
				{
					auto found = find(otherStep.second.begin(), otherStep.second.end(), timer.first);
					if (found != otherStep.second.end())
						otherStep.second.erase(found);
				}
			}
		}

		bool erasing = true;
		do {
			auto toErase = find_if(timers.begin(), timers.end(), [](pair<char,int> t) { return t.second <= 0; });
			if (toErase == timers.end())
				erasing = false;
			else
				timers.erase(toErase);
		} while (erasing);

		for (auto step : tree)
		{
			if (timers.size() < maxWorkers && step.second.size() == 0 && timers.find(step.first) == timers.end())
				timers[step.first] = step.first - 'A' + 1 + 60;
		}
	} while (find_if(timers.begin(), timers.end(), [](pair<char, int> x) {return x.second >= 0; }) != timers.end());

	cout << currentSecond << endl;
}
