#include "assembler.h"

using namespace BubbleCat;
using namespace std;


Assembler::Assembler(void)
{
}


Assembler::~Assembler(void)
{
}

void Assembler::loadGrammar(string grammarPath) {
	ifstream file;
	string BasicOpCodeFile = grammarPath;
	string SpecialOpCodeFile = grammarPath;
	string ValueFile = grammarPath;

	BasicOpCodeFile += "BasicOpCode.txt";
	SpecialOpCodeFile += "SpecialOpCode.txt";
	ValueFile += "Value.txt";

	loadPairFromFile(BasicOpCodeFile, mBasicOpCodeArray);
	loadPairFromFile(SpecialOpCodeFile, mSpecialCodeArray);
	loadPairFromFile(ValueFile, mValueArray);

}

bool Assembler::loadPairFromFile(std::string file, std::vector<std::pair<std::string, int> > &arr) {
	ifstream filestream(file);
	pair<string, int> pairbuff;
	string stringbuff;

	if(!filestream.is_open()) {
		cerr << "Unable to open the Basic Opcode file." << endl;
		return false;
	} else {
		while(!filestream.eof()) {
			filestream >> pairbuff.first >> stringbuff;
			pairbuff.second = stoi(stringbuff, 0, 16);
			arr.push_back(pairbuff);
		}
		filestream.close();
	}

	return true;
}

void Assembler::handleLine(string line) {
	string Operator="";
	int i=0;

	if(line.empty() || line[0]== '\0')
		return;
	

	while(line[i] != ' ') {
		Operator.push_back(line[i]);
		i++;
	}
	Operator.push_back('\0');
	
	if(isBasic(Operator)) {

	}
}

bool Assembler::isBasic(std::string s) {
	for(int i=0 ; i<mBasicOpCodeArray.size() ; i++) {
		if(s == mBasicOpCodeArray[i].first) {
			return true;
		}
	}

	return false;
}

bool Assembler::isSpecial(std::string s) {
	for(int i=0 ; i<mSpecialCodeArray.size() ; i++) {
		if(s == mSpecialCodeArray[i].first) {
			return true;
		}
	}

	return false;
}