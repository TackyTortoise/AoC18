#pragma once

class InputReader
{
public:
	InputReader();
	~InputReader();

	static std::string GetFileText(const std::string& filePath);
	static std::vector<std::string> SplitString(const std::string& input, const std::string& delim);
	template<typename T>
	static std::vector<T> GetFileLines(std::string filePath);
};

template<typename T>
std::vector<T> InputReader::GetFileLines(std::string filePath)
{
	ifstream file(filePath);
	if (file.is_open())
	{
		std::vector<T>result((std::istream_iterator<T>(file)), std::istream_iterator<T>());
		file.close();
		return result;
	}

	return {};
}
