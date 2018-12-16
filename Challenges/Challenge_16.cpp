#include "stdafx.h"
#include "Challenge_16.h"

void Challenge_16::Part1()
{
	//Create operation codes
#pragma region opcodes
	vector<OpCode> opcodes(16);
	opcodes[0] = OpCode({
		"addr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] + registers[b];
			return modified;
		}});

	opcodes[1] = OpCode({
		"addi",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] + b;
			return modified;
		}});

	opcodes[2] = OpCode({
		"mulr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] * registers[b];
			return modified;
		}});

	opcodes[3] = OpCode({
		"muli",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] * b;
			return modified;
		}});

	opcodes[4] = OpCode({
		"banr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] & registers[b];
			return modified;
		}});

	opcodes[5] = OpCode({
		"bani",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] & b;
			return modified;
		}});

	opcodes[6] = OpCode({
		"borr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] | registers[b];
			return modified;
		}});

	opcodes[7] = OpCode({
		"bori",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] | b;
			return modified;
		}});

	opcodes[8] = OpCode({
		"setr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a];
			return modified;
		}});

	opcodes[9] = OpCode({
		"seti",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = a;
			return modified;
		}});

	opcodes[10] = OpCode({
		"gtir",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = a > registers[b] ? 1 : 0;
			return modified;
		}});

	opcodes[11] = OpCode({
		"gtri",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] > b ? 1 : 0;
			return modified;
		}});

	opcodes[12] = OpCode({
		"gtrr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] > registers[b] ? 1 : 0;
			return modified;
		}});

	opcodes[13] = OpCode({
		"eqir",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = a == registers[b] ? 1 : 0;
			return modified;
		}});

	opcodes[14] = OpCode({
		"eqri",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = b == registers[a] ? 1 : 0;
			return modified;
		}});

	opcodes[15] = OpCode({
		"eqrr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] == registers[b] ? 1 : 0;
			return modified;
		} });
#pragma endregion 

	int validSamples = 0;
	vector<string> input = InputReader::GetRawLines("../Input/16.txt");
	for (int i = 0; i < input.size() - 4; i += 4)
	{
		if (i > input.size() || input[i][0] != 'B')
			break;

		vector<int> startValues = InputReader::GetNumbersFromString(input[i]);
		vector<int> operation = InputReader::GetNumbersFromString(input[i + 1]);
		vector<int> expectedValues = InputReader::GetNumbersFromString(input[i + 2]);

		int validOperations = 0;
		for (auto& op : opcodes)
		{
			vector<int> result = op.execute(startValues, operation[1], operation[2], operation[3]);
			if (result == expectedValues)
			{
				++validOperations;
				if (validOperations >= 3)
				{
					++validSamples;
					break;
				}
			}
		}
	}

	cout << "Total valid samples: " << validSamples << endl;
}

void Challenge_16::Part2()
{
	//Create operation codes
#pragma region opcodes
	vector<OpCode> opcodes(16);
	opcodes[0] = OpCode({
		"addr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] + registers[b];
			return modified;
		} });

	opcodes[1] = OpCode({
		"addi",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] + b;
			return modified;
		} });

	opcodes[2] = OpCode({
		"mulr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] * registers[b];
			return modified;
		} });

	opcodes[3] = OpCode({
		"muli",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] * b;
			return modified;
		} });

	opcodes[4] = OpCode({
		"banr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] & registers[b];
			return modified;
		} });

	opcodes[5] = OpCode({
		"bani",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] & b;
			return modified;
		} });

	opcodes[6] = OpCode({
		"borr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] | registers[b];
			return modified;
		} });

	opcodes[7] = OpCode({
		"bori",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] | b;
			return modified;
		} });

	opcodes[8] = OpCode({
		"setr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a];
			return modified;
		} });

	opcodes[9] = OpCode({
		"seti",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = a;
			return modified;
		} });

	opcodes[10] = OpCode({
		"gtir",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = a > registers[b] ? 1 : 0;
			return modified;
		} });

	opcodes[11] = OpCode({
		"gtri",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] > b ? 1 : 0;
			return modified;
		} });

	opcodes[12] = OpCode({
		"gtrr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] > registers[b] ? 1 : 0;
			return modified;
		} });

	opcodes[13] = OpCode({
		"eqir",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = a == registers[b] ? 1 : 0;
			return modified;
		} });

	opcodes[14] = OpCode({
		"eqri",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = b == registers[a] ? 1 : 0;
			return modified;
		} });

	opcodes[15] = OpCode({
		"eqrr",
		[](vector<int> registers, int a, int b, int c)
		{
			vector<int> modified = registers;
			modified[c] = registers[a] == registers[b] ? 1 : 0;
			return modified;
		} });
#pragma endregion 

	vector<string> input = InputReader::GetRawLines("../Input/16.txt");
	int lastI = 0;
	for (int i = 0; i < input.size() - 4; i += 4)
	{
		if (i > input.size() || input[i][0] != 'B')
		{
			lastI = i;
			break;
		}

		vector<int> startValues = InputReader::GetNumbersFromString(input[i]);
		vector<int> operation = InputReader::GetNumbersFromString(input[i + 1]);
		vector<int> expectedValues = InputReader::GetNumbersFromString(input[i + 2]);

		for (auto& op : opcodes)
		{
			vector<int> result = op.execute(startValues, operation[1], operation[2], operation[3]);
			if (result == expectedValues)
			{
				op.possiblePositions.insert(operation[0]);
			}
		}
	}

	while (find_if(opcodes.begin(), opcodes.end(), [](OpCode op) {return op.possiblePositions.size() > 0; }) != opcodes.end())
	{
		vector<int> toRemove;
		for (int i = 0; i < opcodes.size(); ++i)
		{
			if (opcodes[i].possiblePositions.size() == 1)
			{
				opcodes[i].actualPosition = *opcodes[i].possiblePositions.begin();
				toRemove.push_back(opcodes[i].actualPosition);
			}
		}

		for (int i = 0; i < opcodes.size(); ++i)
		{
			for (int remove : toRemove)
				opcodes[i].possiblePositions.erase(remove);
		}
	}

	vector<OpCode> orderedOpCodes(16);
	for (int i = 0; i < orderedOpCodes.size(); ++i)
	{
		auto it = find_if(opcodes.begin(), opcodes.end(), [i](OpCode op) {return op.actualPosition == i; });
		orderedOpCodes[i] = *it;
	}

	vector<int> currentRegisters{ 0,0,0,0 };
	for (int i = lastI; i < input.size(); ++i)
	{
		if (input[i].size() == 0)
			continue;

		vector<int> operation = InputReader::GetNumbersFromString(input[i]);
		currentRegisters = orderedOpCodes[operation[0]].execute(currentRegisters, operation[1], operation[2], operation[3]);
	}

	cout << "Value at end in register 0: " << currentRegisters[0] << endl;
}
