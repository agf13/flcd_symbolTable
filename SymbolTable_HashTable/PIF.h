#pragma once

#include <vector>
#include <string>

class PIFPair
{
public:
	PIFPair(std::string name, int positionInSt)
	{
		this->name = name;
		this->positionInST = positionInSt;
	}
	PIFPair(std::string name)
	{
		this->name = name;
	}

	void setPositionInST(int newPosition)
	{
		this->positionInST = newPosition;
	}

	int getPositionInST()
	{
		return this->positionInST;
	}
	std::string getName()
	{
		return this->name;
	}


private:
	std::string name;
	int positionInST;
};

class PIF
{
public:
	PIF()
	{

	}
	~PIF()
	{
		for (int i = 0; i < elements.size(); i++)
		{
			delete elements[i];
		}
	}

	void add(std::string name, int position)
	{
		PIFPair *newPair = new PIFPair(name, position);
		elements.push_back(newPair);
	}

	int add(PIFPair* newPair)
	{
		int index = this->elements.size();
		elements.push_back(newPair);
		return index;
	}

	PIFPair* get(int index)
	{
		if (index > elements.size())
		{
			return NULL;
		}
		return elements[index];
	}

	unsigned int getSize()
	{
		return elements.size();
	}

private:
	std::vector< PIFPair* > elements;
};