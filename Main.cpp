#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

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
#include "./Challenges/Challenge_09.h"
#include "./Challenges/Challenge_10.h"
#include "./Challenges/Challenge_11.h"
#include "./Challenges/Challenge_12.h"
#include "./Challenges/Challenge_13.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Challenge_13 today;
	cout << "Part 1 output: " << endl;
	PerformanceTester::Start();
	today.Part1();
	PerformanceTester::Stop();
	cout << "Part 1 runtime in microseconds: ";
	PerformanceTester::Log();

	cout << "\nPart 2 output: " << endl;
	PerformanceTester::Start();
	today.Part2();
	PerformanceTester::Stop();
	cout << "Part 2 runtime in microseconds: ";
	PerformanceTester::Log();
	cin.get();
}
