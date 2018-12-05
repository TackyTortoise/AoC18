#include <stdafx.h>
#include "Challenge_05.h"

Challenge_05::Challenge_05() = default;
Challenge_05::~Challenge_05() = default;
void Challenge_05::Part1()
{
	string input = InputReader::GetFileText("../Input/05.txt");
	string result;
	bool foundDouble = true;
	while (foundDouble)
	{
		foundDouble = false;
		for (int i = 0; i < input.size(); ++i)
		{
			if (i == input.size() - 1)
			{
				result += input[i];
				continue;
			}

			int a = (int)input[i];
			int b = (int)input[i + 1];
			if (abs(b - a) != 32)
				result += input[i];
			else
			{
				foundDouble = true;
				++i;
			}
		}
		input = result;
		result = "";
	}
	cout << input.size() << endl;
}
void Challenge_05::Part2()
{
	string orginput = InputReader::GetFileText("../Input/05.txt");
	int shortestSize = numeric_limits<int>::max();
	char optimalRemoval = ' ';
	for (char c = 'a'; c <= 'z'; ++c)
	{
		string input = orginput;
		string result;
		bool foundDouble = true;
		while (foundDouble)
		{
			foundDouble = false;
			for (int i = 0; i < input.size(); ++i)
			{
				if (i == input.size() - 1)
				{
					result += input[i];
					continue;
				}

				int a = (int)input[i];
				int b = (int)input[i + 1];
				if (abs(b - a) != 32)
				{
					if (input[i] != c && input[i] != toupper(c))
					result += input[i];
				}
				else
				{
					foundDouble = true;
					++i;
				}
			}
			input = result;
			result = "";
		}

		if (input.size() < shortestSize)
		{
			shortestSize = input.size();
			optimalRemoval = c;
		}
	}
	cout << shortestSize << endl;
}