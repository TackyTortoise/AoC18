#pragma once
class Challenge
{
public:
	Challenge(){}
	virtual ~Challenge(){};

	virtual void Part1() = 0;
	virtual void Part2() = 0;
};

