#include "stdafx.h"
#include "./Challenges/Challenge.h"
#include "./Challenges/Challenge_01.h"
#include "./Challenges/Challenge_02.h"

int main()
{
	Challenge_02 today;
	PerformanceTester::Start();
	cout << "Part 1 output: " << endl;
	today.Part1();
	cout << "Part 1 runtime in ms: ";
	PerformanceTester::StopAndLog();

	PerformanceTester::Start();
	cout << "\nPart 2 output: " << endl;
	today.Part2();
	cout << "Part 2 runtime in ms: ";
	PerformanceTester::StopAndLog();
	cin.get();
}
