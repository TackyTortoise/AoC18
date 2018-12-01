#include "stdafx.h"
#include "InputReader.h"

InputReader::InputReader(){}
InputReader::~InputReader(){}

string InputReader::GetFileText(string filePath)
{
	ifstream file(filePath);
	if (file.is_open())
	{
		stringstream ss;
		ss << file.rdbuf();
		file.close();
		return ss.str();
	}
	return "Failed to open or read file: "+ filePath;
}

vector<std::string> InputReader::GetFileLines(string filePath)
{
	vector<string> result;
	ifstream file(filePath);
	if (file.is_open())
	{
		string line;
		while(getline(file, line))
		{
			result.push_back(line);
		}
		file.close();
	}
	return result;
}

vector<int> InputReader::GetFileLinesAsInts(string filePath)
{
	vector<int> result;
	ifstream file(filePath);
	int current;
	if (file.is_open())
	{
		while (file >> current)
			result.push_back(current);
		file.close();
	}
	return result;
}