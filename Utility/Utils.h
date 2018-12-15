#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Point
{
	Point(int index, int width, bool Open) : index(index), x(index % width), y(index / width), open(Open){}
	//Point(int X, int Y, bool Open) : x(X), y(Y), open(Open) {}
	int index = 0;
	int x = 0;
	int y = 0;
	bool open = false;

	float GScore = 0.f;
	float HScore = 0.f;
	float FScore = 0.f;
	Point* parent = nullptr;

	bool operator== (Point other) const
	{
		return x == other.x && y == other.y && open == other.open;
	}
};

ostream& operator<<(ostream& s, const Point p)
{
	return s << "[" << p.x << ", " << p.y << "]";
}

class AStarGrid
{
public:
	AStarGrid(const vector<Point*>& elements, int width, int height) : Elements(elements), WIDTH(width), HEIGHT(height)
	{
	}

	~AStarGrid()
	{
		for (auto e : Elements)
		{
			delete e;
			e = nullptr;
		}
		Elements.clear();
	}

	Point* GetElement(int x, int y)
	{
		return Elements[y * WIDTH + x];
	}

	Point* GetElement(int i)
	{
		return Elements[i];
	}

	void ClearParents()
	{
		for (auto e : Elements)
		{
			e->parent = nullptr;
		}
	}

	vector<Point*> GetNeighbours(Point* p)
	{
		vector<Point *> result;
		int index = p->index;

		//Up
		if (p->y > 0 && Elements[index - WIDTH]->open)
			result.push_back(Elements[index - WIDTH]);

		//Left
		if (p->x > 0 && Elements[index - 1]->open)
			result.push_back(Elements[index - 1]);

		//Right
		if (p->x < WIDTH - 1 && Elements[index + 1]->open)
			result.push_back(Elements[index + 1]);

		//Down
		if (p->y < HEIGHT - 1 && Elements[index + WIDTH]->open)
			result.push_back(Elements[index + WIDTH]);

		return result;
	}

	void Draw()
	{
		for (int i = 0; i < Elements.size(); ++i)
		{
			char c = Elements[i]->open ? '.' : '#';
			cout << c;
			if (i % WIDTH == WIDTH - 1)
				cout << endl;
		}
	}
	vector<Point *>Elements;

private:
	int WIDTH;
	int HEIGHT;
};

class PathFinder
{
public:
	const std::vector<Point*>& FindPath(Point* startElement, Point* endElement, AStarGrid* grid)
	{
		if (grid->GetNeighbours(startElement).size() == 0)
			return { };

		ClearContainers();
		grid->ClearParents();
		if (startElement == endElement)
		{
			m_vPath.push_back(startElement);
			return m_vPath;
		}

		deque<Point*> openList;
		deque<Point*> closedList;

		Point* currentPoint = nullptr;
		openList.push_back(startElement);

		while (openList.size() != 0)
		{
			//get node with lowest f score
			float lowestFScore = numeric_limits<float>::max();

			for (auto el : openList)
			{
				if (el->FScore < lowestFScore || el->FScore == lowestFScore && el->index < currentPoint->index)
				{
					currentPoint = el;
					lowestFScore = el->FScore;
				}
			}

			//pop current of open list and push in closed list
			openList.erase(std::remove_if(openList.begin(), openList.end(),
				[currentPoint](const Point* e) { return currentPoint == e; }));

			closedList.push_back(currentPoint);

			//retrieve neighboors
			auto nb = grid->GetNeighbours(currentPoint);

			//if end is in neighbours return
			if (find(nb.begin(), nb.end(), endElement) != nb.end())
			{
				endElement->parent = currentPoint;
				openList.clear();
				break;
			}

			//else go over all neighbours
			for (auto n : nb)
			{
				if (find(closedList.begin(), closedList.end(), n) != closedList.end())
				{
					continue;
				}
				//if node not in open list, compute score and add it
				if (find(openList.begin(), openList.end(), n) == openList.end())
				{
					//set parent to current element
					n->parent = currentPoint;

					//calculate h, g and f score
					//g = current.g + cost(dist current and this) ---> OR ues GetTileCost() if using hard value (needs extra support for diagonal movement)
					float cost = Euclidean(abs(currentPoint->x - n->x), abs(currentPoint->y - n->y));
					n->GScore = n->parent->GScore + cost;

					//h = distance this and goal
					n->HScore = Euclidean(abs(n->x - endElement->x), abs(n->y - endElement->y));

					//f = g + h
					n->FScore = n->GScore + n->HScore;

					//add to openlist
					openList.push_back(n);
				}
			}
		}

		if (HeuristicManhatten(abs(currentPoint->x - endElement->x), abs(currentPoint->y - endElement->y)) > 1)
		{
			m_vPath.clear();
			return m_vPath;
		}

		m_vPath.push_back(endElement);
		m_vPath.push_back(currentPoint);
		Point* nextElement = currentPoint->parent;
		while (nextElement != nullptr)
		{
			m_vPath.push_back(nextElement);
			nextElement = nextElement->parent;
			if (find(m_vPath.begin(), m_vPath.end(), nextElement) != m_vPath.end())
				return std::vector<Point*>{nullptr};
		}
		reverse(m_vPath.begin(), m_vPath.end());
		return m_vPath;
	}
	void ClearContainers()
	{
		m_vPath.clear();
	}

private:
	std::vector<Point*> m_vPath;
	inline float HeuristicManhatten(int x, int y)
	{
		return float(x + y);
	}
	inline float TestHeuristic(int x, int y)
	{
		return float(sqrt(x + y) * (x + y));
	}
	inline float Octile(int x, int y)
	{
		auto f = sqrt(2) - 1;
		return float((x < y) ? f * x + y : f * y + x);
	}
	inline float Euclidean(int x, int y)
	{
		return float(sqrt(x*x + y * y));
	}
	inline float Chebyshev(int x, int y)
	{
		return std::max(x, y);
	}

	int shortestPathLength = INT_MAX;
};

bool operator< (Point p1, Point p2)
{
	if (p1.x != p2.x)
		return p1.x < p2.x;

	if (p1.y != p2.y)
		return p1.y < p2.y;

	return p1.open;
}

struct myPath
{
	myPath(Point s, Point e, unsigned int l) :start(s), end(e), length(l) {}
	Point start;
	Point end;
	unsigned int length;
};