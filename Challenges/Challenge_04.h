#pragma once
#include "Challenge.h"
class Challenge_04 : public Challenge
{
public:
	Challenge_04() = default;
	~Challenge_04() = default;
	void Part1() override;
	void Part2() override;

	struct Entry 
	{
		Entry() = default;
		Entry(string input);

		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		int action; //-1 is fall asleep, -2 is wake up, 0 or higher is guard number
	};

	struct Guard
	{
		int guardNumber = -1;
		Entry lastSleepTime;
		int totalMinutesSlept = 0;
		map<int, int> minutesSlept;

		void FinishSleeping(const Entry& stopEntry)
		{
			int totalSecondsA = stopEntry.month * 31 * 24 * 60 + stopEntry.day * 24 * 60 + stopEntry.hour * 60 + stopEntry.minute;
			int totalSecondsB = lastSleepTime.month * 31 * 24 * 60 + lastSleepTime.day * 24 * 60 + lastSleepTime.hour * 60 + lastSleepTime.minute;
			int difference = abs(totalSecondsB - totalSecondsA);
			if (stopEntry.minute > lastSleepTime.minute)
			{
				for (int i = lastSleepTime.minute; i < stopEntry.minute; ++i)
					minutesSlept[i]++;
			}
			else
			{
				for (int i = lastSleepTime.minute; i < 60; ++i)
					minutesSlept[i]++;
				for (int i = 0; i < stopEntry.minute; ++i)
					minutesSlept[i]++;
			}
			
			totalMinutesSlept += difference;
			lastSleepTime = stopEntry;
		}
	};
};

