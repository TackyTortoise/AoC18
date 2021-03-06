#pragma once

class InputReader
{
public:
	InputReader();
	~InputReader();

	static std::string GetFileText(const std::string& filePath);
	static std::vector<std::string> SplitString(const std::string& input, const std::string& delim);
	template<typename T>
	static std::vector<T> GetFileLines(const std::string& filePath);
	static std::set<std::string> SplitStringSet(const std::string& input, const std::string& delim);
	static std::vector<std::string> GetRawLines(const std::string& filePath);
	static std::vector<int> GetNumbersFromString(std::string string);
	static void PrintField(char* field, int width, int height);
};

template<typename T>
std::vector<T> InputReader::GetFileLines(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file.is_open())
	{
		std::vector<T>result((std::istream_iterator<T>(file)), std::istream_iterator<T>());
		file.close();
		return result;
	}

	return {};
}
