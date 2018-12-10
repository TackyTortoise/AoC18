#include "stdafx.h"
#include "Challenge_10.h"

void Challenge_10::Part1()
{
	vector<string> input = InputReader::GetRawLines("../Input/10.txt");
	LightPoint* lights = new LightPoint[input.size()];
	Int2 low(numeric_limits<int>::max(), numeric_limits<int>::max());
	Int2 high(numeric_limits<int>::min(), numeric_limits<int>::min());
	for (int i = 0; i < input.size(); ++i)
	{
		auto nums = InputReader::GetNumbersFromString(input[i]);
		low.x = min(low.x, nums[0]);
		low.y = min(low.y, nums[1]);
		high.x = max(high.x, nums[0]);
		high.y = max(high.y, nums[1]);
		lights[i].startPosition = Int2(nums[0], nums[1]);
		lights[i].velocity = Int2(nums[2], nums[3]);
	}

	ofstream closer("../Input/Output.txt", ios::out);
	closer.close();
	ofstream out("../Input/Output.txt", ios::out | ios::app);
	stringstream boards;
	int bestSecond = -1;
	long long bestArea = numeric_limits<int>::max();
	Int2 bestLow;
	for (int second = 0; second < 50000; ++second)
	{
		Int2 lowest(numeric_limits<int>::max(), numeric_limits<int>::max());
		Int2 highest(numeric_limits<int>::min(), numeric_limits<int>::min());
		for (auto l = 0; l < input.size(); ++l)
		{
			LightPoint light = lights[l];
			int x = light.startPosition.x + light.velocity.x * second;
			int y = light.startPosition.y + light.velocity.y * second;
			lowest.x = min(lowest.x, x);
			lowest.y = min(lowest.y, y);
			highest.x = max(highest.x, y);
			highest.y = max(highest.y, y);
		}
		int areaW = highest.x - lowest.x;
		int areaH = highest.y - lowest.y;
		long long area = areaW * areaH;
		if (area < bestArea && area > 0)
		{
			bestArea = area;
			bestSecond = second;
			bestLow = lowest;
		}
	}

	int width = 100;
	int height = 10;
	char* field = new char[width * height];
	memset(field, '.', width * height);
	for (auto l = 0; l < input.size(); ++l)
	{
		LightPoint light = lights[l];
		int x = light.startPosition.x + light.velocity.x * bestSecond - bestLow.x;
		int y = light.startPosition.y + light.velocity.y * bestSecond - bestLow.y;
		if (x < 0 || x >= width || y < 0 || y >= height)
		{
			cout << "Out of bounds on board" << endl;
			break;
		}
		int idx = x + y * width;
		field[idx] = '#';
	}

	for (int i = 0; i < width * height; ++i)
	{
		if (i > 0 && i % width == 0)
			boards << endl;
		boards << field[i];
	}

	boards << endl << endl << endl;

	out << boards.str();
	out.close();

	delete[] field;
	delete[] lights;
	cout << "Done" << endl;
}

void Challenge_10::Part2()
{
	vector<string> input = InputReader::GetRawLines("../Input/10.txt");
	LightPoint* lights = new LightPoint[input.size()];
	Int2 low(numeric_limits<int>::max(), numeric_limits<int>::max());
	Int2 high(numeric_limits<int>::min(), numeric_limits<int>::min());
	for (int i = 0; i < input.size(); ++i)
	{
		auto nums = InputReader::GetNumbersFromString(input[i]);
		low.x = min(low.x, nums[0]);
		low.y = min(low.y, nums[1]);
		high.x = max(high.x, nums[0]);
		high.y = max(high.y, nums[1]);
		lights[i].startPosition = Int2(nums[0], nums[1]);
		lights[i].velocity = Int2(nums[2], nums[3]);
	}

	int bestSecond = -1;
	long long bestArea = numeric_limits<int>::max();
	for (int second = 0; second < 50000; ++second)
	{
		Int2 lowest(numeric_limits<int>::max(), numeric_limits<int>::max());
		Int2 highest(numeric_limits<int>::min(), numeric_limits<int>::min());
		for (auto l = 0; l < input.size(); ++l)
		{
			LightPoint light = lights[l];
			int x = light.startPosition.x + light.velocity.x * second;
			int y = light.startPosition.y + light.velocity.y * second;
			lowest.x = min(lowest.x, x);
			lowest.y = min(lowest.y, y);
			highest.x = max(highest.x, y);
			highest.y = max(highest.y, y);
		}
		int areaW = highest.x - lowest.x;
		int areaH = highest.y - lowest.y;
		long long area = areaW * areaH;
		if (area < bestArea && area > 0)
		{
			bestArea = area;
			bestSecond = second;
		}
	}

	delete[] lights;
	cout << bestSecond << endl;
}
