#pragma once

#define UNCLASSYFIED 0
#define TOKEN_RESERVED -1
#define TOKEN_IF -2
#define TOKEN_ELSE -3
#define TOKEN_FOR -4
#define TOKEN_WHILE -5
#define TOKEN_DEFINE -6
#define TOKEN_RETURN -7
#define TOKEN_READ -8
#define TOKEN_WRITE -9
#define TOKEN_TYPE_INT -10
#define TOKEN_TYPE_BOOL -11
#define TOKEN_TYPE_CHAR -12
#define TOKEN_TYPE_STRING -13
#define TOKEN_SEPARTOR -14
#define TOKEN_OPERATION -15
#define TOKEN_ALPHABET -16
#define TOKEN_CHAR -16
#define IDENTIFIER -17
#define CONSTANT -18
#define SEPARATOR -19
#define OPERATOR -20


#include <string>
#include <fstream>
#include <iostream>

#include "PIF.h"

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(std::string tokenFile, std::string programName)
	{
		this->tokensFile = this->path + tokenFile;
		this->programName = this->path + programName;
	}
	~LexicalAnalyzer()
	{

	}

	/*
	* def: returns 0 if correct
	*		return the number of the incorrect line
	*/
	int analyze()
	{
		std::ifstream fileIn(this->programName);
		std::string token;
		while (fileIn >> token)
		{
			classify(token);
			codify(token);
		}
		return 0;
	}


	int classify(std::string token)
	{
		ifstream checkFile(this->tokensFile);
		std::string currToken;
		bool reservedTokenFlag = false;
		bool classyfied = false;
		int flag = UNCLASSYFIED;
		while (checkFile >> currToken && reservedTokenFlag == false)
		{
			if (currToken == token)
			{
				reservedTokenFlag = true;
				classyfied = true;
				flag = TOKEN_RESERVED;
			}
		}
		if (reservedTokenFlag == false)
		{
			if (isalpha(currToken[0]) || currToken[0] == '_')
			{
				classyfied = true;
				flag = IDENTIFIER;;
			}
		}
		
		checkFile.close();

		return flag;
	}

	void codify(std::string token)
	{

	}

private:
	std::string programName, tokensFile;
	std::string path;
	PIF PIFTable;
	int tokenFlag;
};