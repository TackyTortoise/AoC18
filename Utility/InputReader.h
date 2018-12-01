#pragma once

class InputReader
{
public:
	InputReader();
	~InputReader();

	static std::string GetFileText(std::string filePath);
	static std::vector<std::string> GetFileLines(std::string filePath);
	static std::vector<int> GetFileLinesAsInts(std::string filePath);
};

