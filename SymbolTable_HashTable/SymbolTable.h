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

	int add(std::string symbol)
	{
		int code = getCodeValue(symbol);
		int index = hash(code);
		while (!symbolTable[index].empty())
		{
			index++;
			if (index >= size)
				index = 0;
		}
		symbolTable[index] = symbol;
		return index;
	}

	int getCodeValue(std::string symbol)
	{
		int code = 0;
		for (unsigned int i = 0; i < symbol.size(); i++)
		{
			code += (int)symbol[i];
		}
		return code;
	}

	int hash(int code)
	{
		return (code % size);
	}

	std::string getByIndex(int index)
	{
		return symbolTable[index];
	}


private:
	int size;
	std::string *symbolTable;
		
};
