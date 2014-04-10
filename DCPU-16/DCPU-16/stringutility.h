#pragma once

#include <string>

namespace StringUtility {
	bool isNumerical(char c);
	bool isLetter(char c);
	bool strArrayCompare(std::string s, std::string arr[], unsigned int size);
	bool strArrayCompare(std::string arr1[], unsigned int size1, std::string arr2[], unsigned int size2);
}
