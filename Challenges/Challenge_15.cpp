#include "stdafx.h"
#include "Challenge_15.h"


void Challenge_15::Part1()
{
	string input = InputReader::GetFileText("../Input/15.txt");
	int width = input.find('\n');
	int height = input.length() / width;
	input.erase(remove(input.begin(), input.end(), '\n'), input.end());

	vector<Point*> gridPoints(width * height);
	vector<Unit*> goblins;
	vector<Unit*> elfs;
	int currentIndex = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		char c = input[i];
		if (c == 'G')
		{
			goblins.push_back(new Unit{ c, currentIndex, 200 });
			gridPoints[currentIndex] = new Point(currentIndex, width, false);
			++currentIndex;
		}
		if (c == 'E')
		{
			elfs.push_back(new Unit{ c, currentIndex, 200 });
			gridPoints[currentIndex] = new Point(currentIndex, width, false);
			++currentIndex;
		}
		else if (c == '#')
		{
			gridPoints[currentIndex] = new Point(currentIndex, width, false);
			++currentIndex;
		}
		else if (c == '.')
		{
			gridPoints[currentIndex] = new Point(currentIndex, width, true);
			++currentIndex;
		}
	}

	AStarGrid * grid = new AStarGrid(gridPoints, width, height);
	PathFinder finder;
	int round = 0;
	bool stahp = false;
	while (elfs.size() > 0 && goblins.size() > 0)
	{	
		for(int i = 0; i < elfs.size(); ++i)
		{
			if (elfs[i]->hp < 200)
				cout << "Elf hp: " << elfs[i]->hp << endl;
		}
		
		vector<Unit*> availableUnits;
		availableUnits.reserve(elfs.size() + goblins.size());
		availableUnits.insert(availableUnits.end(), elfs.begin(), elfs.end());
		availableUnits.insert(availableUnits.end(), goblins.begin(), goblins.end());
		while (availableUnits.size() > 0)
		{
			auto u = min_element(availableUnits.begin(), availableUnits.end(), [](Unit* a, Unit* b) {return a->currentIndex < b->currentIndex; });
			Unit* chosenUnit = *u;
			availableUnits.erase(u);
			vector<Unit*> targets = chosenUnit->type == 'E' ? goblins : elfs;
			Unit* closestTarget = nullptr;
			//Check for units in direct range
			vector<Unit*> targetsInRange;
			for (auto t : targets)
			{
				if (chosenUnit->ManhattenDistance(t->currentIndex, width) == 1)
					targetsInRange.push_back(t);
			}

			if (targetsInRange.size() == 0)
			{
				set<int> openPositions;
				int openIndex = 0;
				for (auto t : targets)
				{
					auto indices = t->GetSurroundingIndeces(width, height);
					for (auto ind : indices)
					{
						if (grid->GetElement(ind)->open)
						{
							openPositions.insert(ind);
							++openIndex;
						}
					}
				}

				int shortestDistance = numeric_limits<int>::max();
				vector<vector<Point*>> shortestPaths;
				vector<Point*> tempDisabled;
				int shortestPosition = 99999;
				for (auto openPosition : openPositions)
				{
					if (openPosition < 0)
						continue;

					bool retry = false;
					do {
						retry = false;
						if (grid->GetNeighbours(grid->GetElement(chosenUnit->currentIndex)).size() == 0)
							continue;
						auto foundPath = finder.FindPath(grid->GetElement(chosenUnit->currentIndex), grid->GetElement(openPosition), grid);
						if (foundPath.size() < 2 || foundPath[0] == nullptr)
							continue;
						foundPath.erase(foundPath.begin());
						if (foundPath.size() < shortestDistance)
						{
							shortestPaths.clear();
							shortestDistance = foundPath.size();
							shortestPaths.push_back(foundPath);

							foundPath[0]->open = false;
							tempDisabled.push_back(foundPath[0]);
							retry = true;
							shortestPosition = openPosition;
						}
						else if (foundPath.size() == shortestDistance)
						{
							if (openPosition == shortestPosition)
								shortestPaths.push_back(foundPath);
							else if (openPosition < shortestPosition)
							{
								shortestPaths.clear();
								shortestPaths.push_back(foundPath);
								for (auto d : tempDisabled)
									d->open = true;
							}
						}
					} while (retry);


					for (auto d : tempDisabled)
						d->open = true;
				}

				if (shortestPaths.size() == 0)
					continue;

				vector<Point*> pathToTake = *min_element(shortestPaths.begin(), shortestPaths.end(), [](vector<Point*> p1, vector<Point*> p2) {return p1[0]->index < p2[0]->index; });

				//Move unit
				grid->GetElement(chosenUnit->currentIndex)->open = true;
				chosenUnit->currentIndex = pathToTake[0]->index;
				if (!grid->GetElement(chosenUnit->currentIndex)->open)
					for (int i = 0; i < 5000; i++)
					cout << "Dafak" << endl;
				grid->GetElement(chosenUnit->currentIndex)->open = false;

				//Recheck units in range
				for (auto t : targets)
				{
					if (chosenUnit->ManhattenDistance(t->currentIndex, width) == 1)
						targetsInRange.push_back(t);
				}
			}
			
			//Attack unit
			int minHealth = 201;
			for (auto t : targetsInRange)
			{
				if (t->hp < minHealth)
				{
					closestTarget = t;
					minHealth = t->hp;
				}
				else if (t->hp == minHealth && t->currentIndex < closestTarget->currentIndex)
					closestTarget = t;
			}

			//Attack unit in direct range
			if (closestTarget != nullptr)
			{
				closestTarget->hp -= 3;
				if (closestTarget->hp <= 0)
				{
					grid->GetElement(closestTarget->currentIndex)->open = true;
					auto it = find(availableUnits.begin(), availableUnits.end(), closestTarget);
					if (it != availableUnits.end())
					{
						availableUnits.erase(it);
					}
					if (closestTarget->type == 'E')
					{
						it = find(elfs.begin(), elfs.end(), closestTarget);
						if (it != elfs.end())
							elfs.erase(it);
					}
					else if (closestTarget->type == 'G')
					{
						it = find(goblins.begin(), goblins.end(), closestTarget);
						if (it != goblins.end())
							goblins.erase(it);
					}

					delete closestTarget;
				}

				if (elfs.size() == 0 || goblins.size() == 0)
				{
					stahp = true;
					break;
				}
			}
		}

		if (stahp)
			break;

		++round;
		//cout << round << endl;
		//cout << endl << "Round " << round << endl;
		////Print field
		//for (int i = 0; i < gridSize; ++i)
		//{
		//	char c = grid->GetElement(i)->open ? '.' : '#';
		//	if (find_if(elfs.begin(), elfs.end(), [i](Unit* u) {return u->currentIndex == i; }) != elfs.end())
		//		c = 'E';
		//	else if (find_if(goblins.begin(), goblins.end(), [i](Unit* u) {return u->currentIndex == i; }) != goblins.end())
		//		c = 'G';

		//	if (i > 0 && i % width == 0)
		//		cout << endl;
		//	cout << c;
		//}
		//cout << endl;
	}

	//Clean up grid (also deletes points from grid)
	delete grid;

	int total = 0;
	for (auto g : goblins)
		total += g->hp;
	for (auto e : elfs)
		total += e->hp;

	cout << "Rounds: " << round << endl;
	cout << "Total hp: " << total << endl;
	cout << total * round << endl;

	for (auto e : elfs)
		delete e;
	for (auto g : goblins)
		delete g;
}

void Challenge_15::Part2()
{
	string input = InputReader::GetFileText("../Input/15.txt");
	int width = input.find('\n');
	int height = input.length() / width;
	input.erase(remove(input.begin(), input.end(), '\n'), input.end());

	vector<Point*> gridPoints(width * height);
	vector<Unit*> goblins;
	vector<Unit*> elfs;
	PathFinder finder;

	bool noElfsLost = false;
	for (int attackPower = 4; !noElfsLost; ++attackPower)
	{
		noElfsLost = true;

		int round = 0;
		bool stahp = false;

		int currentIndex = 0;
		elfs.clear();
		goblins.clear();
		for (int i = 0; i < input.size(); ++i)
		{
			char c = input[i];
			if (c == 'G')
			{
				goblins.push_back(new Unit{ c, currentIndex, 200 });
				gridPoints[currentIndex] = new Point(currentIndex, width, false);
				++currentIndex;
			}
			if (c == 'E')
			{
				elfs.push_back(new Unit{ c, currentIndex, 200 });
				gridPoints[currentIndex] = new Point(currentIndex, width, false);
				++currentIndex;
			}
			else if (c == '#')
			{
				gridPoints[currentIndex] = new Point(currentIndex, width, false);
				++currentIndex;
			}
			else if (c == '.')
			{
				gridPoints[currentIndex] = new Point(currentIndex, width, true);
				++currentIndex;
			}
		}

		AStarGrid* grid = new AStarGrid(gridPoints, width, height);

		while (elfs.size() > 0 && goblins.size() > 0)
		{
			vector<Unit*> availableUnits;
			availableUnits.reserve(elfs.size() + goblins.size());
			availableUnits.insert(availableUnits.end(), elfs.begin(), elfs.end());
			availableUnits.insert(availableUnits.end(), goblins.begin(), goblins.end());
			while (availableUnits.size() > 0)
			{
				auto u = min_element(availableUnits.begin(), availableUnits.end(), [](Unit* a, Unit* b) {return a->currentIndex < b->currentIndex; });
				Unit* chosenUnit = *u;
				availableUnits.erase(u);
				vector<Unit*> targets = chosenUnit->type == 'E' ? goblins : elfs;
				Unit* closestTarget = nullptr;
				//Check for units in direct range
				vector<Unit*> targetsInRange;
				for (auto t : targets)
				{
					if (chosenUnit->ManhattenDistance(t->currentIndex, width) == 1)
						targetsInRange.push_back(t);
				}

				if (targetsInRange.size() == 0)
				{
					set<int> openPositions;
					int openIndex = 0;
					for (auto t : targets)
					{
						auto indices = t->GetSurroundingIndeces(width, height);
						for (auto ind : indices)
						{
							if (grid->GetElement(ind)->open)
							{
								openPositions.insert(ind);
								++openIndex;
							}
						}
					}

					int shortestDistance = numeric_limits<int>::max();
					vector<vector<Point*>> shortestPaths;
					vector<Point*> tempDisabled;
					int shortestPosition = 99999;
					for (auto openPosition : openPositions)
					{
						if (openPosition < 0)
							continue;

						bool retry = false;
						do {
							retry = false;
							if (grid->GetNeighbours(grid->GetElement(chosenUnit->currentIndex)).size() == 0)
								continue;
							auto foundPath = finder.FindPath(grid->GetElement(chosenUnit->currentIndex), grid->GetElement(openPosition), grid);
							if (foundPath.size() < 2 || foundPath[0] == nullptr)
								continue;
							foundPath.erase(foundPath.begin());
							if (foundPath.size() < shortestDistance)
							{
								shortestPaths.clear();
								shortestDistance = foundPath.size();
								shortestPaths.push_back(foundPath);

								foundPath[0]->open = false;
								tempDisabled.push_back(foundPath[0]);
								retry = true;
								shortestPosition = openPosition;
							}
							else if (foundPath.size() == shortestDistance)
							{
								if (openPosition == shortestPosition)
									shortestPaths.push_back(foundPath);
								else if (openPosition < shortestPosition)
								{
									shortestPaths.clear();
									shortestPaths.push_back(foundPath);
									for (auto d : tempDisabled)
										d->open = true;
								}
							}
						} while (retry);


						for (auto d : tempDisabled)
							d->open = true;
					}

					if (shortestPaths.size() == 0)
						continue;

					vector<Point*> pathToTake = *min_element(shortestPaths.begin(), shortestPaths.end(), [](vector<Point*> p1, vector<Point*> p2) {return p1[0]->index < p2[0]->index; });

					//Move unit
					grid->GetElement(chosenUnit->currentIndex)->open = true;
					chosenUnit->currentIndex = pathToTake[0]->index;
					if (!grid->GetElement(chosenUnit->currentIndex)->open)
						for (int i = 0; i < 5000; i++)
							cout << "Dafak" << endl;
					grid->GetElement(chosenUnit->currentIndex)->open = false;

					//Recheck units in range
					for (auto t : targets)
					{
						if (chosenUnit->ManhattenDistance(t->currentIndex, width) == 1)
							targetsInRange.push_back(t);
					}
				}

				//Attack unit
				int minHealth = 201;
				for (auto t : targetsInRange)
				{
					if (t->hp < minHealth)
					{
						closestTarget = t;
						minHealth = t->hp;
					}
					else if (t->hp == minHealth && t->currentIndex < closestTarget->currentIndex)
						closestTarget = t;
				}

				//Attack unit in direct range
				if (closestTarget != nullptr)
				{
					int damage = chosenUnit->type == 'E' ? attackPower : 3;
					closestTarget->hp -= damage;
					if (closestTarget->hp <= 0)
					{
						grid->GetElement(closestTarget->currentIndex)->open = true;
						auto it = find(availableUnits.begin(), availableUnits.end(), closestTarget);
						if (it != availableUnits.end())
						{
							availableUnits.erase(it);
						}
						if (closestTarget->type == 'E')
						{
							noElfsLost = false;
							it = find(elfs.begin(), elfs.end(), closestTarget);
							if (it != elfs.end())
								elfs.erase(it);
						}
						else if (closestTarget->type == 'G')
						{
							it = find(goblins.begin(), goblins.end(), closestTarget);
							if (it != goblins.end())
								goblins.erase(it);
						}
					}

					delete closestTarget;

					if (elfs.size() == 0 || goblins.size() == 0)
					{
						stahp = true;
						break;
					}
				}
			}

			if (stahp)
				break;

			++round;
		}

		//Clean up grid (also deletes points from grid)
		delete grid;

		if (noElfsLost)
		{
			int totalHP = 0;
			for (auto e : elfs)
				totalHP += e->hp;

			cout << "Round " << round << endl;
			cout << "Total hp " << totalHP << endl;
			cout << "Combat result " << round * totalHP << endl;
			cout << "No elfs lost at attack power " << attackPower << endl;
		}
	}

	for (auto e : elfs)
		delete e;
	for (auto g : goblins)
		delete g;
}
