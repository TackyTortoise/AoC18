#include "stdafx.h"
#include "Challenge_01.h"
#include <set>

Challenge_01::Challenge_01()= default;
Challenge_01::~Challenge_01() = default;

void Challenge_01::Part1()
{
	auto input = InputReader::GetFileLines<int>("../Input/01.txt");
	int currentFreq = 0;
	for (int change : input)
		currentFreq += change;

	cout << currentFreq << endl;
	cout << "Part 1 done" << endl;
}

void Challenge_01::Part2()
{
	auto input = InputReader::GetFileLines<int>("../Input/01.txt");
	int currentFreq = 0;
	int i = 0;
	//Set test
	set<int> encounteredFreqsSet;
	while (true)
	{
		currentFreq += input[i];
		if (encounteredFreqsSet.find(currentFreq) != encounteredFreqsSet.end())
			break;
		encounteredFreqsSet.insert(currentFreq);
		++i;
		i %= input.size();
	}

	cout << currentFreq << endl;
	cout << "Part 2 done" << endl;
}
