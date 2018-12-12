#include "stdafx.h"
#include "Challenge_12.h"

void Challenge_12::Part1()
{
	vector<string> input = InputReader::GetRawLines("../Input/12.txt");
	string state = input[0].substr(input[0].find(':') + 2);
	map<string, char> rules;
	for (int i = 2; i < input.size(); ++i)
	{
		auto pos = input[i].find(" => ");
		rules[input[i].substr(0, pos)] = input[i].back();
	}
	cout << state << endl;
	int frontAdded = 0;
	for (int gen = 0; gen < 20; ++gen)
	{
		string oldState = "...." + state + "....";
		string newState = oldState;
		for (int c = 0; c < oldState.size() - 2; ++c)
		{
			auto part = oldState.substr(c, 5);
			if (rules.find(part) != rules.end())
			{
				char newChar = rules[part];
				if (c <= 2 - frontAdded)
				{
					if (newChar == '#')
						frontAdded += 2 - c;
					else
						frontAdded -= 2 - c;
				}
				newState[c + 2] = newChar;
			}
			else
				newState[c + 2] = '.';
		}
		int firstPlant = newState.find('#');
		int lastPlant = newState.rfind('#');
		state = newState.substr(firstPlant, lastPlant - firstPlant + 1);
	}

	int total = 0;
	for (int i = 0; i < state.size(); ++i)
	{
		if (state[i] == '#')
			total += i - frontAdded;
	}

	cout << total << endl;
}

void Challenge_12::Part2()
{
	struct entry
	{
		string state;
		long long gen;
		long long frontOffset;
		bool encountered = false;
	};

	vector<string> input = InputReader::GetRawLines("../Input/12.txt");
	string state = input[0].substr(input[0].find(':') + 2);
	vector<entry> encountered;
	encountered.push_back(entry{state, 0, 0});
	map<string, char> rules;
	for (int i = 2; i < input.size(); ++i)
	{
		auto pos = input[i].find(" => ");
		rules[input[i].substr(0, pos)] = input[i].back();
	}
	cout << state << endl;
	long long frontAdded = 4;
	bool stahp = false;
	const long long GENERATIONS = 50000000000;
	for (long long gen = 0; gen < GENERATIONS; ++gen)
	{
		string oldState = "...." + state + "....";
		string newState = oldState;
		for (int c = 0; c < oldState.size() - 2; ++c)
		{
			auto part = oldState.substr(c, 5);
			if (rules.find(part) != rules.end())
			{
				char newChar = rules[part];
				newState[c + 2] = newChar;
			}
			else
				newState[c + 2] = '.';
		}
		int firstPlant = newState.find('#');
		int lastPlant = newState.rfind('#');
		frontAdded += 4 - firstPlant;
		state = newState.substr(firstPlant, lastPlant - firstPlant + 1);

		if (!stahp)
		{
			for (int e = 0; e < encountered.size(); ++e)
			{
				if (encountered[e].state == state)
				{
					cout << "Loop after " << gen << " generation, with generation " << e << ", " << frontAdded << endl;

					long long div = GENERATIONS - gen + 3; //Why the fuck is this + 3???? somehow work
					int frontdiff = frontAdded - encountered[e].frontOffset;
					frontAdded += frontdiff * div;
					cout << "going to generation " << gen << endl;
					stahp = true;
					break;
				}
			}
		}

		if (stahp)
			break;
		encountered.push_back({state, gen, frontAdded});
	}

	long long total = 0;
	for (int i = 0; i < state.size(); ++i)
	{
		if (state[i] == '#')
			total += i - frontAdded;
	}

	cout << total << endl;
}
