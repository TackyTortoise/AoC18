#include "stdafx.h"
#include "Challenge_14.h"

void Challenge_14::Part1()
{
	int recipesN = 894501;
	vector<int> recipeScores{ 3,7 };
	int e1 = 0, e2 = 1;
	int recipesCreated = 2;
	recipeScores.resize(recipesN + 10);
	while(recipesCreated < recipesN + 10)
	{
		int newScore = recipeScores[e1] + recipeScores[e2];
		vector<int>digits;
		while (newScore > 9)
		{
			digits.push_back(newScore % 10);
			newScore /= 10;
		}
		digits.push_back(newScore);
		for (int i = digits.size() - 1; i >= 0; --i)
		{
			recipeScores[recipesCreated] = digits[i];
			++recipesCreated;
			if (recipesCreated > recipesN + 10)
				break;
		}
		e1 += recipeScores[e1] + 1;
		e2 += recipeScores[e2] + 1;
		e1 %= recipesCreated;
		e2 %= recipesCreated;
	}

	for (int i = recipesN; i < recipesN + 10; ++i)
	{
		cout << recipeScores[i];
	}
}

void Challenge_14::Part2()
{
	int recipesN = 894501;
	vector<int> recipeScores{ 3,7 };
	int e1 = 0, e2 = 1;
	int recipesCreated = 2;
	recipeScores.resize(recipesN * 100);
	string recipeString = "37";
	string goal = to_string(recipesN);
	char toExpect = goal[0];
	while (recipeString != goal)
	{
		int newScore = recipeScores[e1] + recipeScores[e2];
		vector<int>digits;
		while (newScore > 9)
		{
			digits.push_back(newScore % 10);
			newScore /= 10;
		}
		digits.push_back(newScore);
		for (int i = digits.size() - 1; i >= 0; --i)
		{
			recipeScores[recipesCreated] = digits[i];
			++recipesCreated;
			char dc = to_string(digits[i])[0];
			if (dc == toExpect)
			{
				recipeString += dc;

				if (recipeString == goal)
					break;

				toExpect = goal[recipeString.size()];
			}
			else if (recipeString.size() > 0)
			{
				recipeString.clear();
				toExpect = goal[recipeString.size()];
				if (dc == toExpect)
				{
					recipeString += dc;

					if (recipeString == goal)
						break;

					toExpect = goal[recipeString.size()];
				}
			}
		}
		e1 += recipeScores[e1] + 1;
		e2 += recipeScores[e2] + 1;
		e1 %= recipesCreated;
		e2 %= recipesCreated;
	}

	cout << recipesCreated - goal.size() << endl;
}
