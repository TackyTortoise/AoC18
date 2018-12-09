#include "stdafx.h"
#include "Challenge_09.h"

void Challenge_09::Part1()
{
	const int maxPlayers = 404;
	const int maxMarble = 71852;
	int playerScores[maxPlayers];
	memset(playerScores, 0, maxPlayers * sizeof(int));
	vector<int> marbles{0};
	int currentPlayer = -1;
	int currentMarbleIndex = 0;
	for (int turn = 1; turn < maxMarble + 1; ++turn)
	{
		++currentPlayer;
		currentPlayer %= maxPlayers;
		if (turn > 0 && turn % 23 == 0)
		{
			playerScores[currentPlayer] += turn;
			currentMarbleIndex -= 7;
			if (currentMarbleIndex < 0)
				currentMarbleIndex = marbles.size() + currentMarbleIndex;
			playerScores[currentPlayer] += marbles[currentMarbleIndex];
			marbles.erase(marbles.begin() + currentMarbleIndex);
			continue;
		}

		if (marbles.size() > 0)
		{
			currentMarbleIndex += 2;
			currentMarbleIndex %= marbles.size();
		}
		if (currentMarbleIndex >= marbles.size() || currentMarbleIndex == 0)
		{
			currentMarbleIndex = marbles.size();
			marbles.push_back(turn);
		}
		else
			marbles.insert(marbles.begin() + currentMarbleIndex, turn);
	}


	int result = *max_element(&playerScores[0], &playerScores[maxPlayers]);
	cout <<  result << endl;
}

//Basically part 1 but with linked list for faster deletion, get optimized son
void Challenge_09::Part2()
{
	struct Marble
	{
		Marble(int n, Marble* p, Marble* nxt)
		{
			number = n; prev = p; next = nxt;
			if (prev != nullptr)
				prev->next = this;
			if (next != nullptr)
				next->prev = this;
		}

		int number;
		Marble* prev = nullptr;
		Marble* next = nullptr;;

		Marble* GetOffset(int offset)
		{
			if (offset < 0 && prev != nullptr)
				return prev->GetOffset(offset + 1);
			else if (offset > 0 && next != nullptr)
				return next->GetOffset(offset - 1);
			return this;
		}
	};

	const int maxPlayers = 404;
	const int maxMarble = 71852;
	long long playerScores[maxPlayers];
	memset(playerScores, 0, maxPlayers * sizeof(long long));
	Marble* current = new Marble(0, nullptr, nullptr);
	current->prev = current;
	current->next = current;
	Marble* root = current;
	int currentPlayer = -1;
	for (int turn = 1; turn < maxMarble + 1; ++turn)
	{
		++currentPlayer;
		currentPlayer %= maxPlayers;
		if (turn > 0 && turn % 23 == 0)
		{
			playerScores[currentPlayer] += turn;
			Marble* off = current->GetOffset(-7);
			off->next->prev = off->prev;
			off->prev->next = off->next;
			playerScores[currentPlayer] += off->number;
			current = off->next;
			delete off;
			continue;
		}

		Marble* c1 = current->GetOffset(1);
		Marble* c2 = current->GetOffset(2);
		current = new Marble(turn, c1, c2);
	}
	
	long long result = *max_element(&playerScores[0], &playerScores[maxPlayers]);
	cout << result << endl;

	//Memory leaks, no papa
	Marble* next;
	for (Marble* node = root; node != nullptr; node = next)
	{
		next = node->next;
		if (node ->prev != nullptr)
			node->prev->next = nullptr;
		if (next != nullptr)
			next->prev = nullptr;
		delete(node);
	}
}
