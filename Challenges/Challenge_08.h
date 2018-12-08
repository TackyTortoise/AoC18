#pragma once
#include "Challenge.h"
class Challenge_08 : public Challenge
{
public:
	Challenge_08() = default;
	~Challenge_08() = default;

	void Part1() override;
	void Part2() override;

	struct Node
	{
		Node() = default;

		vector<Node*> childNodes;
		vector<int> metaEntries;

		int GetValue()
		{
			int sum = 0;
			if (childNodes.size() == 0)
			{
				for (auto meta : metaEntries)
					sum += meta;
				return sum;
			}

			for (auto meta : metaEntries)
			{
				int index = meta - 1;
				if (index < 0 || index >= childNodes.size())
					continue;
				sum += childNodes[index]->GetValue();
			}
			return sum;
		}
	};

	Node* ProcessNode(int& cursor, const vector<int>& input, Node* parent, int& totalMeta);
};

