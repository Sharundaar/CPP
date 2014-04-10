#include "stringutility.h"

using namespace StringUtility;

bool isNumerical(char c) {
	if(c >= '0' && c <= '9') {
		return true;
	} else {
		return false;
	}
}

bool isLetter(char c) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		return true;
	} else {
		return false;
	}
}

bool strArrayCompare(std::string s, std::string arr[], unsigned int size) {
	bool match = false;
	unsigned int i=0;

	while(!match && i < size) {
		match = (s == arr[i]);
		i++;
	}

	return match;
}

bool strArrayCompare(std::string arr1[], unsigned int size1, std::string arr2[], unsigned int size2) {
	bool match = false;
	unsigned int i=0;

	while(!match && i < size1) {
		match = StringUtility::strArrayCompare(arr1[i], arr2, size2);
		i++;
	}

	return match;
}