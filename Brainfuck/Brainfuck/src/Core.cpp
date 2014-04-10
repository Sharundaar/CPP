#include <Core.h>

Core::Core() {}

Core::~Core() {}

void Core::go() {
	this->init();
	this->loop();
}

void Core::init() {
	for(int i=0 ; i<RAM_SIZE ; i++) {
		mRAM[i] = 0;
	}
	cursor = 0;
}

void Core::loop() {
	std::string code = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++<<+++++.>++++++.>+++++++.";
	int i=0;
	while(code[i]!=EOF) {
		compute(code[i]);
	}
}

void Core::incCursor() {
	if(cursor<RAM_SIZE)	{
		cursor++;
	} else {
		cursor = 0;
	}
}

void Core::decCursor() {
	if(cursor>0) {
		cursor--;
	} else {
		cursor = (char)RAM_SIZE-1;
	}
}

void Core::compute(char ptr) {
	switch(ptr) {
		case '>': 
			this->incCursor();
			break;

		case '<': 
			this->decCursor();
			break;

		case '+': 
			this->mRAM[cursor] += (char)1;
			break;

		case '-': 
			this->mRAM[cursor] -= (char)1;
			break;

		case '.': 
			putc(mRAM[cursor], stdout);
			break;

		case ',': 
			this->mRAM[cursor] = getc(stdin);
			break;

		case '[': 
			break;

		case ']': 
			break;

		default:
			break;
	}
}

int main(int argc, char* argv[]) {
	Core core;
	core.go();
}