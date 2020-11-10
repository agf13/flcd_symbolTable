#pragma once

#include <string>

class VariableIndexPair
{
public:
	VariableIndexPair(std::string varName, int pifIndex)
	{
		this->name = varName;
		this->pifIndex = pifIndex;
	}

	~VariableIndexPair()
	{

	}

	std::string getName()
	{
		return this->name;
	}

	int getPIFIndex()
	{
		return this->pifIndex;
	}


private:
	std::string name;
	int pifIndex;
};