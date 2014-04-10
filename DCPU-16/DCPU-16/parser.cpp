#include "parser.h"

using namespace std;

Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}

char getNextCharacter(FILE* file) {
	char c;
	while((c=getc(file)) <= ' ') {
		if(c == EOF)
			return c;
	}

	return c;
}
char* getNextLine(FILE* file, char* buff) {
	int i=0;
	char c;

	while((c=fgetc(file)) != '\n' && c != EOF) {
		if(buff != NULL) {
			buff[i] = c;
			i++;
		}
	}
	if(buff != NULL) {
		buff[i] = '\0';
	}

	return buff;
}

vector<int> Parser::parseDCPUFile(char* filepath) {
	vector<int> output;
	ifstream file(filepath, ios::in);
	string 
	string buff;

	if(!file.is_open()) {
		cerr << "Unable to open the file : " << filepath << endl;
	} else {
		while(getline(file, buff)) {

		}
	}

	file.close();

	return output;
}

void lowerCase(string& s) {
	for(int i=0 ; i<s.size() ; i++) {
		if(s[i] >= 'A' || s[i] <= 'Z') {
			s[i] = s[i]-'A'+'a';
		}
	}
}

int Parser::handleOperator(string ope) {
	lowerCase(ope);
	int opcode;

	if(ope == "SET") {
		opcode = 1;
	} else if(ope == "ADD") {
		opcode = 2;
	} else if(ope == "SUB") {
		opcode = 3;
	} else if(ope == "MUL") {
		opcode = 4;
	} else if(ope == "MLI") {
		opcode = 5;
	} else if(ope == "DIV") {
		opcode = 6;
	} else if(ope == "DVI") {
		opcode = 7;
	} else if(ope == "MOD") {
		opcode = 8;
	} else if(ope == "MDI") {
		opcode = 9;
	} else if(ope == "AND") {
		opcode = 10;
	} else if(ope == "BOR") {
		opcode = 11;
	} else if(ope == "XOR") {
		opcode = 12;
	} else if(ope == "SHR") {
		opcode = 13;
	} else if(ope == "ASR") {
		opcode = 14;
	} else if(ope == "SHL") {
		opcode = 15;
	} else if(ope == "IFB") {
		opcode = 16;
	} else if(ope == "IFC") {
		opcode = 17;
	} else if(ope == "IFE") {
		opcode = 18;
	} else if(ope == "IFN") {
		opcode = 19;
	} else if(ope == "IFG") {
		opcode = 20;
	} else if(ope == "IFA") {
		opcode = 21;
	} else if(ope == "IFL") {
		opcode = 22;
	} else if(ope == "IFU") {
		opcode = 23;
	} else if(ope == "ADX") {
		opcode = 0x1A;
	} else if(ope == "SBX") {
		opcode = 0x1B;
	} else if(ope == "STI") {
		opcode = 0x1E;
	} else if(ope == "STD") {
		opcode = 0x1F;
	} else if(ope == "JSR") {
		opcode = 0x20;
	} else if(ope == "INT") {
		opcode = 0x27;
	} else if(ope == "IAG") {
		opcode = 0x28;
	} else if(ope == "IAS") {
		opcode = 0x29;
	} else if(ope == "RFI") {
		opcode = 0x2A;
	} else if(ope == "IAQ") {
		opcode = 0x2B;
	} else if(ope == "HWN") {
		opcode = 0x2F;
	} else if(ope == "HWQ") {
		opcode = 0x30;
	} else if(ope == "HWI") {
		opcode = 0x31;
	} else {
		opcode = -1;
	}

	return opcode;
}

int Parser::handleOperande(std::string opa, bool isA) {

}