#include "stdafx.h"
#include "Challenge_02.h"

Challenge_02::Challenge_02() = default;
Challenge_02::~Challenge_02() = default;

void Challenge_02::Part1()
{
	vector<string> input = InputReader::GetFileLines<string>("../Input/02.txt");
	map<char, int> encountered;
	int doubleLetter = 0;
	int tripleLetter = 0;
	for (auto line : input)
	{
		for (char c : line)
			++encountered[c];

		if (find_if(encountered.begin(), encountered.end(), [](pair<char, int> e) {return e.second == 2; }) != encountered.end())
			++doubleLetter;
		if (find_if(encountered.begin(), encountered.end(), [](pair<char, int> e) {return e.second == 3; }) != encountered.end())
			++tripleLetter;

		encountered.clear();
	}

	cout << doubleLetter * tripleLetter << endl;
}

void Challenge_02::Part2()
{
	vector<string> input = InputReader::GetFileLines<string>("../Input/02.txt");
	string str1;
	string str2;
	for (int i = 0; i < input.size() - 1; ++i)
	{
		str1 = input[i];
		for (int j = i + 1; j < input.size(); ++j)
		{
			str2 = input[j];
			int diff = 0;
			for (int c = 0; c < str1.size(); ++c)
			{
				if (str1[c] != str2[c])
					++diff;
			}
			if (diff == 1)
			{
				string result;
				for (int i = 0; i < str1.size(); ++i)
				{
					if (str1[i] == str2[i])
						result += str1[i];
				}

				cout << result << endl;
				return;
			}
		}
	}	
}
