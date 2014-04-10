#include <iostream>
#include <vector>
#include "stringutility.h"

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> vs;
	vs.push_back("Toto");
	vs.push_back("Tata");
	vs.push_back("Hihi");

	cout << StringUtility::strArrayCompare("Toto", vs.cbegin(), 3);

	cin.ignore();
	return 0;
}