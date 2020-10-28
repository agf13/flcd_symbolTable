#pragma once		//HASH TABLE

#include <string>
#include <utility>

class Value
{
public:

private:
	int v_int;
	std::string v_string;
};

class SymbolTable
{
public:
	SymbolTable()
	{
		size = 1000;
		symbolTable = new std::string[1000];
	}
	~SymbolTable()
	{
		delete[] symbolTable;
	}

	int add(std::string symbolName, std::string symbolValue)
	{
		int code = getCodeValue(symbolName);
		int index = hash(code);
		while (!symbolTable[index].empty())
		{
			index++;
			if (index >= size)
				index = 0;
		}
		symbolTable[index] = symbolValue;
		return index;
	}
	int add(std::string symbolName)
	{
		int code = getCodeValue(symbolName);
		int index = hash(code);
		while (!symbolTable[index].empty())
		{
			index++;
			if (index >= size)
				index = 0;
		}
		symbolTable[index] = "";
		return index;
	}

	void update(int index, std::string value)
	{
		symbolTable[index] = value;
	}

	//def: computes the ascii sum of the symbol string given. 
	//out: the result should be used as argumnet in hash function to get the index from where to get/insert the element
	int getCodeValue(std::string symbol)
	{
		int code = 0;
		for (unsigned int i = 0; i < symbol.size(); i++)
		{
			code += (int)symbol[i];
		}
		return code;
	}


	//def: hash function to compute indexes for the ST
	//in: code : int (preferably the argument is the result of getCodeValue(std:string)
	int hash(int code)
	{
		return (code % size);
	}

	std::string getByIndex(int index)
	{
		return symbolTable[index];
	}

	unsigned int getSize()
	{
		return this->size;
	}


private:
	unsigned int size;
	std::string *symbolTable;
		
};
