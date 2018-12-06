#include "stdafx.h"
#include "Challenge_04.h"

void Challenge_04::Part1() 
{
	string strInput = InputReader::GetFileText("../Input/Test.txt");
	set<string> input = InputReader::SplitStringSet(strInput, "\n");
	vector<Guard> guards;
	int lastGuardNumber = -1;
	for (auto line : input)
	{
		auto entry = Entry(line);
		if (entry.action >= 0)
		{
			lastGuardNumber = entry.action;
			if (find_if(guards.begin(), guards.end(), [lastGuardNumber](Guard g){return g.guardNumber == lastGuardNumber;}) == guards.end())
			{
				Guard newGuard;
				newGuard.guardNumber = lastGuardNumber;
				guards.push_back(newGuard);
			}
		}

		if (entry.action == -1)
		{
			auto guard = find_if(guards.begin(), guards.end(), [lastGuardNumber](Guard g) {return g.guardNumber == lastGuardNumber; });
			if (guard != guards.end())
				guard->lastSleepTime = entry;
		}

		if (entry.action == -2)
		{
			auto guard = find_if(guards.begin(), guards.end(), [lastGuardNumber](Guard g) {return g.guardNumber == lastGuardNumber; });
			if (guard != guards.end())
				guard->FinishSleeping(entry);
		}
	}

	int maxMinutes = numeric_limits<int>::min();
	Guard maxGuard;
	for (auto guard: guards)
	{
		if (guard.totalMinutesSlept > maxMinutes)
		{
			maxMinutes = guard.totalMinutesSlept;
			maxGuard = guard;
		}
	}

	int maxSleptOnMinute = numeric_limits<int>::min();
	int maxMinute = -1;
	for (auto minutes : maxGuard.minutesSlept)
	{
		if (minutes.second > maxSleptOnMinute)
		{
			maxMinute = minutes.first;
			maxSleptOnMinute = minutes.second;
		}
	}

	cout << maxGuard.guardNumber * maxMinute << endl;
}

void Challenge_04::Part2()
{
	string strInput = InputReader::GetFileText("../Input/Test.txt");
	set<string> input = InputReader::SplitStringSet(strInput, "\n");
	vector<Guard> guards;
	int lastGuardNumber = -1;
	for (auto line : input)
	{
		auto entry = Entry(line);
		if (entry.action >= 0)
		{
			lastGuardNumber = entry.action;
			if (find_if(guards.begin(), guards.end(), [lastGuardNumber](Guard g) {return g.guardNumber == lastGuardNumber; }) == guards.end())
			{
				Guard newGuard;
				newGuard.guardNumber = lastGuardNumber;
				guards.push_back(newGuard);
			}
		}

		if (entry.action == -1)
		{
			auto guard = find_if(guards.begin(), guards.end(), [lastGuardNumber](Guard g) {return g.guardNumber == lastGuardNumber; });
			if (guard != guards.end())
				guard->lastSleepTime = entry;
		}

		if (entry.action == -2)
		{
			auto guard = find_if(guards.begin(), guards.end(), [lastGuardNumber](Guard g) {return g.guardNumber == lastGuardNumber; });
			if (guard != guards.end())
				guard->FinishSleeping(entry);
		}
	}

	int maxSameMinuteAsleep = numeric_limits<int>::min();
	int minuteNum = -1;
	Guard maxGuard;
	for (auto guard : guards)
	{
		for(auto minute : guard.minutesSlept)
		{
			if (minute.second > maxSameMinuteAsleep)
			{
				minuteNum = minute.first;
				maxSameMinuteAsleep = minute.second;
				maxGuard = guard;
			}
		}
	}

	cout << maxGuard.guardNumber * minuteNum << endl;
}

Challenge_04::Entry::Entry(string input)
{
	smatch match;
	regex rgx("[0-9]+");
	int nums[6];
	int idx = 0;
	while (regex_search(input, match, rgx) && match.size() > 0 && idx < 6)
	{
		nums[idx] = stoi(match[0].str());
		++idx;
		input = match.suffix();
	}

	year = nums[0];
	month = nums[1];
	day = nums[2];
	hour = nums[3];
	minute = nums[4];

	if (idx == 6)
		action = nums[5];
	else
		action = input.find("falls") != string::npos ? -1 : -2;
}
