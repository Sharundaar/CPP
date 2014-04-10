#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

typedef enum parserstate {
	INITIAL_STATE=0, OPERATOR_STATE, OPERANDE_STATE, LABEL_STATE
} ParserState;

class Parser
{
public:
	Parser(void);
	virtual ~Parser(void);

	std::vector<int> parseDCPUFile(char* filepath);
	int handleOperator(std::string ope);

	void exportBinaryCode(std::vector<int> code, char* output);
	void exportBinaryCode(char* input, char* output);

};

