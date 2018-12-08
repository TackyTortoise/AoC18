#include "stdafx.h"
#include "Challenge_08.h"


void Challenge_08::Part1()
{
	vector<int> input = InputReader::GetFileLines<int>("../Input/08.txt");
	int cursor = 0;
	int totalMeta = 0;
	Node* root = ProcessNode(cursor, input, nullptr, totalMeta);
	cout << totalMeta << endl;
}

void Challenge_08::Part2()
{
	vector<int> input = InputReader::GetFileLines<int>("../Input/08.txt");
	int cursor = 0;
	int totalMeta = 0;
	Node* root = ProcessNode(cursor, input, nullptr, totalMeta);
	cout << root->GetValue() << endl;
}

Challenge_08::Node* Challenge_08::ProcessNode(int& cursor, const vector<int>& input, Node* parent, int& totalMeta)
{
	int children = input[cursor];
	++cursor;
	int metaData = input[cursor];
	++cursor;
	Node* newNode = new Node(children, metaData);

	if (parent != nullptr)
		parent->childNodes.push_back(newNode);

	if (children == 0 || cursor >= input.size() - 1)
	{
		for (int i = 0; i < metaData; ++i)
		{
			newNode->metaEntries.push_back(input[cursor + i]);
			totalMeta += input[cursor + i];
		}
		cursor += metaData;
		return newNode;
	}

	for (int i = 0; i < children; ++i)
		ProcessNode(cursor, input, newNode, totalMeta);

	for (int i = 0; i < metaData; ++i)
	{
		newNode->metaEntries.push_back(input[cursor + i]);
		totalMeta += input[cursor + i];
	}
	cursor += metaData;
	return newNode;
}
