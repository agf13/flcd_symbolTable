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
#define TOKEN_IDENTIFIER -17
#define TOKEN_CONSTANT -18
#define SEPARATOR -19
#define OPERATOR -20
#define LEXICAL_ERROR -21
#define TOKEN_OPERATOR -22
#define SPACING_CHARACTER -23
#define TOKEN_ATTRIBUTION -24

#define RESERVED_SIZE 12
#define OPERATIOS_SIZE 14
#define SEPARATORS_SIZE 7


#include <string>
#include <fstream>
#include <iostream>

#include "PIF.h"

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(std::string programName)
	{
		this->pathToFiles = "files/";
		this->programRelativePath = this->pathToFiles + programName;
		this->filePIFOut.open("outPIF.txt");
		this->fileSTOut.open("outST.txt");

	}
	~LexicalAnalyzer()
	{
		populatePIFOut();
		populateSTOut();
		this->filePIFOut.close();
		this->fileSTOut.close();
	}

	/*
	* def: returns 0 if correct
	*		return the number of the incorrect line
	*/
	int analyze()
	{
		std::ifstream fileIn(this->programRelativePath);
		std::string token;
		int numberLine = 0;
		int lexicalErrors = 0;
		while (std::getline(fileIn, token))
		{
			numberLine++;
			std::string auxString = token;
			do
			{
				token = auxString; //this line makes sense if the loop is looping (ex.: if token="1234(2+2)", then on second loop, token will become "(2+2)"

				//split the token if any charather other than letters, digits or underscore are found
				int positionInString = checkForSpecialCharacters(token);
				if (positionInString == -1)
				{
					auxString = ""; //we don't have special chars, so we need to set this to null string for while condition
				}
				else if (positionInString == 0)
				{
					if (token.length() > 1)
					{
						auxString = token.substr(1);
						token = token[0];

						if ( (token[0] == '!' && auxString[0] == '=') ||
						 	 (token[0] == '=' && auxString[0] == '=') ||
							 (token[0] == '<' && auxString[0] == '=') ||
							 (token[0] == '>' && auxString[0] == '=') )
						{
							token += auxString[0];
							auxString = auxString.substr(1);
						}
					}
					else
					{

						auxString = "";
					}
				}
				else
				{
					auxString = token.substr(positionInString);
					token = token.substr(0, positionInString);
				}
				
				std::string resultClassify = classify(token);

				if (this->tokenFlag != SPACING_CHARACTER)
				{
					//std::cout << token << " - " << resultClassify << "\n";

					//adding to PIF
					int positionInSt = -1;
					if (this->tokenFlag == TOKEN_IDENTIFIER || this->tokenFlag == TOKEN_CONSTANT)
					{
						positionInSt = this->st.add(token);
					}

					PIFPair* newPair = new PIFPair(token, positionInSt);
					this->PIFTable.add(newPair);
				}
				if (this->tokenFlag == LEXICAL_ERROR)
				{
					std::cout << " - LEXICAL ERROR at line " << numberLine << " at token " << token << "\n";
					lexicalErrors++;
				}

				codify(token);
			} while (auxString.empty() == 0);
		}
		if (lexicalErrors == 0)
		{
			std::cout << " - LEXICALLY CORRECT\n";
		}
		return 0;
	}


	std::string classify(std::string token)
	{
		if (token == "\t" || token == " " || token == "\n")
		{
			this->tokenFlag = SPACING_CHARACTER;
			return "";
		}
		for (int i = 0; i < RESERVED_SIZE; i++)
		{
			if (token == this->reserved[i])
			{
				this->tokenFlag = TOKEN_RESERVED;
				return "reserved word";
			}
		}
		for (int i = 0; i < OPERATIOS_SIZE; i++)
		{
			if (token == this->operators[i])
			{
				this->tokenFlag = TOKEN_OPERATION;
				return "operator";
			}
		}
		for (int i = 0; i < SEPARATORS_SIZE; i++)
		{
			if (token == this->separators[i])
			{
				this->tokenFlag = TOKEN_SEPARTOR;
				return "separator";
			}
		}
		if (isdigit(token[0]) || token[0] == '-' || token[0] == '+')
		{
			for (unsigned int i = 1; i < token.size(); i++)
			{
				if (!isdigit(token[i]))
				{
					this->tokenFlag = LEXICAL_ERROR;
					return "lexical error";
				}
			}
			this->tokenFlag = TOKEN_CONSTANT;
			return "constant";
		}
		else if (!isalpha(token[0]) && token[0] != '_' && token[0] != '+' && token[0] != '-')
		{
			this->tokenFlag = LEXICAL_ERROR;
			return "lexical error";
		}
		else if (token == "true" || token == "false")
		{
			this->tokenFlag = TOKEN_CONSTANT;
			return "constant";
		}
		else if (isalpha(token[0]))
		{
			for (unsigned int i = 1; i < token.size(); i++)
			{
				if (!isalnum(token[i]) && token[i] != '_')
				{
					this->tokenFlag = LEXICAL_ERROR;
					return "lexical error";
				}
			}
			this->tokenFlag = TOKEN_IDENTIFIER;
			return "identifier";
		}
		//constant was here
		else if (token[0] == '-' || token[0] == '+')
		{
			if (token.size() < 2)
			{
				this->tokenFlag = LEXICAL_ERROR;
				return "lexical error";
			}
			for (unsigned int i = 1; i < token.size(); i++)
			{
				if (!isdigit(token[i]))
				{
					this->tokenFlag = LEXICAL_ERROR;
					return "lexical error";
				}
			}
			this->tokenFlag = TOKEN_CONSTANT;
			return "constant";
		}

		return "";
	}

	void codify(std::string token)
	{

	}

	//def: checks if the string given, contains anything else except letters, digits, or underscore
	//out: returns the position where something was found or -1 if not found
	int checkForSpecialCharacters(std::string token)
	{
		int index = -1;
		for (unsigned int i = 0; i < token.size(); i++)
		{
			if (!isalnum(token[i]) && token[i] != '_')
			{
				if (i < token.size() - 1 && (token[i] == '+' || token[i] == '-') && i == 0)
				{
					if (isdigit(token[i + 1]))
					{
						for (unsigned int j = i + 1; j < token.size(); j++)
						{
							if (!isdigit(token[j]))
							{
								return j;
							}
						}
					}
				}
				return i;
			}
		}
		return -1;
	}

	void populatePIFOut()
	{
		for (unsigned int i = 0; i < this->PIFTable.getSize(); i++)
		{
			PIFPair* pair = this->PIFTable.get(i);
			this->filePIFOut << pair->getName() << " - " << pair->getPositionInST() << "\n";
		}
	}

	void populateSTOut()
	{
		for (unsigned int i = 0; i < this->st.getSize(); i++)
		{
			//if(this->st.getByIndex(i) != nullptr)
		}
	}

private:
	std::string programRelativePath, pathToFiles;
	std::ofstream filePIFOut, fileSTOut;
	std::string reserved[RESERVED_SIZE] = {"define", "for", "while", "if", "else", "return", "read", "write", "char", "int", "string", "bool"};
	std::string operators[OPERATIOS_SIZE] = {"+","-","*","/","%","\"","'","=","<=",">=","<",">","==","!="};
	std::string separators[SEPARATORS_SIZE] = { "(",")","{","}","[","]",";" };
	PIF PIFTable;
	SymbolTable st;
	int tokenFlag;
};