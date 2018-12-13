#include "stdafx.h"
#include "Challenge_13.h"


void Challenge_13::Part1()
{
	string input = InputReader::GetFileText("../Input/13.txt");
	int width = input.find('\n');
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	vector<Cart*> carts;
	int cartN = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == '>')
		{
			carts.push_back(new Cart{cartN++, i, 0 });
			input[i] = '-';
		}
		else if (input[i] == 'v')
		{
			carts.push_back(new Cart{ cartN++, i,1 });
			input[i] = '|';
		}
		else if (input[i] == '<') 
		{
			carts.push_back(new Cart{ cartN++, i,2 });
			input[i] = '-';
		}
		else if (input[i] == '^')
		{
			carts.push_back(new Cart{ cartN++, i,3 });
			input[i] = '|';
		}
	}

	bool collision = false;
	while (!collision)
	{
		vector<Cart*> available = carts;
		while (available.size() > 0)
		{
			//Find top left most cart
			auto minCartIterator = min_element(available.begin(), available.end(), [](Cart* x, Cart* y) {return x->currentIndex < y->currentIndex; });
			auto minCart = *minCartIterator;
			int nextIndex = minCart->GetNextIndex(width);
			minCart->currentIndex = nextIndex;
			char newBlock = input[nextIndex];
			int oldDirection = minCart->currentDirection;
			if (newBlock == '\\')
				minCart->currentDirection = 1 - minCart->currentDirection;
			else if (newBlock == '/')
				minCart->currentDirection = 3 - minCart->currentDirection;
			else if (newBlock == '+')
			{
				if (minCart->turnIndex == 0)
					--minCart->currentDirection;
				else if (minCart->turnIndex == 2)
					++minCart->currentDirection;
				++minCart->turnIndex;
				minCart->turnIndex %= 3;
			}

			minCart->currentDirection %= 4;
			if (minCart->currentDirection < 0)
				minCart->currentDirection += 4;

#pragma region test
			//Test
			if (newBlock == '\\')
			{
				if (oldDirection == 0 && minCart->currentDirection != 1 ||
					oldDirection == 1 && minCart->currentDirection != 0 || 
					oldDirection == 2 && minCart->currentDirection != 3 || 
					oldDirection == 3 && minCart->currentDirection != 2)
				{
					cout << "dafak" << endl;
				}
			}
			else if (newBlock == '/')
			{
				if (oldDirection == 0 && minCart->currentDirection != 3 ||
					oldDirection == 1 && minCart->currentDirection != 2 ||
					oldDirection == 2 && minCart->currentDirection != 1 ||
					oldDirection == 3 && minCart->currentDirection != 0)
				{
					cout << "dafak" << endl;
				}
			}
#pragma endregion

			//Check for collisions
			for (int i = 0; i < carts.size(); ++i)
			{
				for (int j = i + 1; j < carts.size(); ++j)
				{
					if (carts[i]->currentIndex == carts[j]->currentIndex)
					{
						int x = carts[i]->currentIndex % width;
						int y = carts[i]->currentIndex / width;
						cout << "Carts did an oopsie at " << x << "," << y << endl;
						collision = true;
					}
				}
			}

			available.erase(minCartIterator);
		}

#pragma region printing
		/*for (int i = 0; i < input.size(); ++i)
		{
			if (i > 0 && i % width == 0)
				cout << endl;
			auto f = find_if(carts.begin(), carts.end(), [i](Cart* c) {return c->currentIndex == i; });
			if (f != carts.end())
			{
				int dir = (*f)->currentDirection;
				if (dir == 0)
					cout << ">";
				else if (dir == 1)
					cout << "v";
				else if (dir == 2)
					cout << "<";
				else if (dir == 3)
					cout << "^";
				else
					cout << "f";
			}
			else
				cout << input[i];
		}*/
#pragma endregion 
	}

	for (Cart* c : carts)
		delete c;
	cout << endl;
}

void Challenge_13::Part2()
{
	string input = InputReader::GetFileText("../Input/13.txt");
	int width = input.find('\n');
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	vector<Cart*> carts;
	int cartN = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == '>')
		{
			carts.push_back(new Cart{ cartN++, i, 0 });
			input[i] = '-';
		}
		else if (input[i] == 'v')
		{
			carts.push_back(new Cart{ cartN++, i,1 });
			input[i] = '|';
		}
		else if (input[i] == '<')
		{
			carts.push_back(new Cart{ cartN++, i,2 });
			input[i] = '-';
		}
		else if (input[i] == '^')
		{
			carts.push_back(new Cart{ cartN++, i,3 });
			input[i] = '|';
		}
	}

	bool stop = false;
	while (carts.size() > 1)
	{
		vector<Cart*> available = carts;
		while (available.size() > 0)
		{
			//Find top left most cart
			auto minCartIterator = min_element(available.begin(), available.end(), [](Cart* x, Cart* y) {return x->currentIndex < y->currentIndex; });
			auto minCart = *minCartIterator;
			int nextIndex = minCart->GetNextIndex(width);
			minCart->currentIndex = nextIndex;
			char newBlock = input[nextIndex];
			if (newBlock == '\\')
				minCart->currentDirection = 1 - minCart->currentDirection;
			else if (newBlock == '/')
				minCart->currentDirection = 3 - minCart->currentDirection;
			else if (newBlock == '+')
			{
				if (minCart->turnIndex == 0)
					--minCart->currentDirection;
				else if (minCart->turnIndex == 2)
					++minCart->currentDirection;
				++minCart->turnIndex;
				minCart->turnIndex %= 3;
			}

			minCart->currentDirection %= 4;
			if (minCart->currentDirection < 0)
				minCart->currentDirection += 4;

			//Check for collisions
			if (!stop)
			{
				for (int i = 0; i < carts.size(); ++i)
				{
					for (int j = i + 1; j < carts.size(); ++j)
					{
						if (carts[i]->currentIndex == carts[j]->currentIndex)
						{
							Cart* f = carts[i];
							Cart* s = carts[j];
							int x = carts[i]->currentIndex % width;
							int y = carts[i]->currentIndex / width;
							cout << "Carts did an oopsie at " << x << "," << y << endl;
							auto firstDelit = carts.begin() + i;
							carts.erase(carts.begin() + i);
							stop = carts.size() == 1;
							if (stop)
							{
								delete f;
								break;
							}

							auto secondDelit = carts.begin() + j;
							carts.erase(carts.begin() + j - 1);
							stop = carts.size() == 1;
							available.erase(remove_if(available.begin(), available.end(), [f,s](Cart* c) {return c == f || c == s; }), available.end());
							i = j = 0;

							delete f;
							delete s;

							if (stop)
								break;
						}
					}
				}
			}

			if (find(available.begin(), available.end(), minCart) != available.end())
				available.erase(remove_if(available.begin(), available.end(), [&minCart](Cart* c) {return c == minCart; }));
		}

		if (stop)
			break;
	}

	int x = carts[0]->currentIndex % width;
	int y = carts[0]->currentIndex / width;
	cout << "Last lonely cart at " << x << "," << y << endl;
	delete carts[0];
}
