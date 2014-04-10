#pragma once

#include <string>

class StringUtility
{
public:
	StringUtility(void);
	~StringUtility(void);

public:
	static bool isNumerical(char c);
	static bool isLetter(char c);
};

