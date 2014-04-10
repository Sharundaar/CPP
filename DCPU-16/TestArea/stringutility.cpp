#include "stringutility.h"


StringUtility::StringUtility(void)
{
}


StringUtility::~StringUtility(void)
{
}

bool StringUtility::isNumerical(char c) {
	if(c >= '0' && c <= 9) {
		return true;
	} else {
		return false;
	}
}

bool StringUtility::isLetter(char c) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		return true;
	} else {
		return false;
	}
}
