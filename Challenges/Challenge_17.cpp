#include "stdafx.h"
#include "Challenge_17.h"
#include <thread>

void Challenge_17::Part1()
{
	vector<string> input = InputReader::GetRawLines("../Input/Test.txt");
	vector<pair<int, int>> coordinates;
	pair<int, int> minCoord = pair<int, int>(numeric_limits<int>::max(), 0);
	pair<int, int> maxCoord = pair<int, int>(numeric_limits<int>::min(), numeric_limits<int>::min());
	for (auto line : input)
	{
		int commaPos = line.find(',');
		string p1 = line.substr(0, commaPos);
		string p2 = line.substr(commaPos);

		pair<int, int> xRange, yRange;
		auto p1Digits = InputReader::GetNumbersFromString(p1);
		auto p2Digits = InputReader::GetNumbersFromString(p2);
		if (p1.find('x') != string::npos)
			xRange = pair<int, int>(p1Digits[0], p1Digits.size() > 1 ? p1Digits[1] : p1Digits[0]);
		else if (p1.find('y') != string::npos)
			yRange = pair<int, int>(p1Digits[0], p1Digits.size() > 1 ? p1Digits[1] : p1Digits[0]);
		if (p2.find('x') != string::npos)
			xRange = pair<int, int>(p2Digits[0], p2Digits.size() > 1 ? p2Digits[1] : p2Digits[0]);
		else if (p2.find('y') != string::npos)
			yRange = pair<int, int>(p2Digits[0], p2Digits.size() > 1 ? p2Digits[1] : p2Digits[0]);

		coordinates.push_back(xRange);
		coordinates.push_back(yRange);

		if (xRange.first < minCoord.first)
			minCoord.first = xRange.first;
		if (xRange.second > maxCoord.first)
			maxCoord.first = xRange.second;
		if (yRange.first < minCoord.second)
			minCoord.second = yRange.first;
		if (yRange.second > maxCoord.second)
			maxCoord.second = yRange.second;
	}

	int width = maxCoord.first - minCoord.first + 3;
	int height = maxCoord.second - minCoord.second + 1;

	char* field = new char[width * height];
	memset(field, '.', width * height);
	for (int i = 0; i < coordinates.size(); i += 2)
	{
		const int minX = coordinates[i].first + 1;
		const int maxX = coordinates[i].second + 1;
		const int minY = coordinates[i + 1].first;
		const int maxY = coordinates[i + 1].second;

		for (int x = minX; x <= maxX; ++x)
		{
			for (int y = minY; y <= maxY; ++y)
			{
				int index = x - minCoord.first + (y - minCoord.second) * width;
				field[index] = '#';
			}
		}
	}

	int waterIndex = 500 - minCoord.first + 1;
	field[waterIndex] = '~';


	//PrintField(field, width, height);

	int newFilled = 1;
	bool stopRising = false;
	deque<int> toCheck;
	while (newFilled > 0 || toCheck.size() > 0)
	{
		//this_thread::sleep_for(chrono::milliseconds(200));
		if (stopRising)
		{
			if (toCheck.size() == 0)
				break;
			stopRising = false;
			waterIndex = toCheck[0];
			toCheck.pop_front();			
		}

		//PrintField(field, width, height);
		newFilled = 0;
		int hitDown = FirstHitDown(field, waterIndex, width, height);

		if (hitDown == -1)
		{
			int index = waterIndex;
			while (index < width * height)
			{
				field[index] = '~';
				index += width;
			}
			stopRising = true;
			continue;
		}

		for (int y = waterIndex / width; y < hitDown / width; ++y)
		{
			if (field[waterIndex % width + y * width] != '~')
			{
				field[waterIndex % width + y * width] = '~';
				++newFilled;
			}
		}

		int hitLeft = FirstHitLeft(field, hitDown - width, width, height);
		int hitRight = FirstHitRight(field, hitDown - width, width, height);
		
		for (int x = hitLeft + 1; x < hitRight; ++x)
		{
			if (field[x] != '~')
			{
				field[x] = '~';
				++newFilled;
			}
		}

		if (hitRight / width < height && field[hitRight + width] == '.' && field[hitRight + width - 1] != '#')
		{
			stopRising = true;
			toCheck.push_back(hitRight + width - 1);
		}
		if (hitLeft / width < height && field[hitLeft + width] == '.'&& field[hitLeft + width + 1] != '#')
		{
			stopRising = true;
			toCheck.push_back(hitLeft + width + 1);
		}

		if (!stopRising)
		{
			if (newFilled > 0)
				waterIndex = hitDown - 2 * width;
			else
			{
				waterIndex -= width;
				if (waterIndex < 0)
					break;
			}
		}
	}

	PrintField(field, width, height);
	int totalWater = -1; //Ignore original water source
	for (int i = 0; i < width * height; ++i)
	{
		if (field[i] == '~')
			++totalWater;
	}
	cout << "Total water reached: " << totalWater << endl;

	//delete[] field;
}

void Challenge_17::Part2()
{
}

void Challenge_17::PrintField(char* field, int width, int height)
{
	cout << endl;
	for (int i = 0; i < width * height; ++i)
	{
		if (i > 0 && i % width == 0)
			cout << endl;
		cout << field[i];
	}
	cout << endl;
}

int Challenge_17::FirstHitDown(char* field, int startIndex, int width, int height)
{
	int startY = startIndex / width;
	for (int y = startY; y < height; ++y)
	{
		int index = startIndex % width + y * width;
		if (index != startIndex &&  field[index] != '.')
			return index;
	}

	return -1;
}

int Challenge_17::FirstHitLeft(char* field, int startIndex, int width, int height)
{
	int x = startIndex % width;
	int y = startIndex / width;
	if (startIndex - 1 == '.')
		return startIndex;
	while(startIndex%width > 0)
	{
		--startIndex;
		if ((startIndex + width < width * height) && field[startIndex + width] == '.')
			return --startIndex;
		if (field[startIndex] == '~')
			return startIndex;
		if (field[startIndex] == '#')
			return startIndex;
	}

	return startIndex;
}

int Challenge_17::FirstHitRight(char* field, int startIndex, int width, int height)
{
	int x = startIndex % width;
	int y = startIndex / width;
	if (startIndex + 1 == '.')
		return startIndex;
	while (startIndex%width < width)
	{
		++startIndex;
		if ((startIndex + width < width * height) && field[startIndex + width] == '.')
			return ++startIndex;
		if (field[startIndex] == '~')
			return startIndex;
		if (field[startIndex] == '#')
			return startIndex;
	}

	return startIndex;
}
