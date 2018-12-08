#include "stdafx.h"
#include "./Challenges/Challenge.h"
#include "./Challenges/Challenge_01.h"
#include "./Challenges/Challenge_02.h"
#include "./Challenges/Challenge_03.h"
#include "./Challenges/Challenge_04.h"
#include "./Challenges/Challenge_05.h"
#include "./Challenges/Challenge_06.h"
#include "./Challenges/Challenge_07.h"
#include "./Challenges/Challenge_08.h"

int main()
{
	Challenge_08 today;
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
