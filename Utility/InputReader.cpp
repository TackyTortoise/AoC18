#include "stdafx.h"
#include "InputReader.h"

InputReader::InputReader(){}
InputReader::~InputReader(){}

string InputReader::GetFileText(const string& filePath)
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

vector<string> InputReader::SplitString(const string& input, const string& delim)
{
	vector<string> result;
	int startSearchPos = 0;
	int lastFoundPos = 0;
	while ((lastFoundPos = input.find(delim, startSearchPos)) != string::npos)
	{
		result.push_back(input.substr(startSearchPos, lastFoundPos - startSearchPos));
		startSearchPos = lastFoundPos + delim.length();
	}
	result.push_back(input.substr(startSearchPos));
	return result;
}

set<string> InputReader::SplitStringSet(const string& input, const string& delim)
{
	set<string> result;
	int startSearchPos = 0;
	int lastFoundPos = 0;
	while ((lastFoundPos = input.find(delim, startSearchPos)) != string::npos)
	{
		result.insert(input.substr(startSearchPos, lastFoundPos - startSearchPos));
		startSearchPos = lastFoundPos + delim.length();
	}
	result.insert(input.substr(startSearchPos));
	return result;
}

std::vector<std::string> InputReader::GetRawLines(const std::string& filePath)
{
	vector<string> result;
	ifstream file(filePath);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
			result.push_back(line);
		file.close();
	}

	return result;
}
