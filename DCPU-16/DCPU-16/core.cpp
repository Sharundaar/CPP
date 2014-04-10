#include "core.h"

using namespace BubbleCat;

Core::Core(void) : A(0), B(0), C(0), X(0), Y(0), Z(0), I(0), J(0), PC(0), SP(0), EX(0), IA(0), mRunning(false), mNbDevices(0) {
	for(unsigned int i=0x0 ; i<0x10000 ; i++) {
		mRAM[i] = 0;
	}

	for(unsigned int i=0 ; i<0x10000 ; i++) {
		mDevices[i] = NULL;
	}
}


Core::~Core(void) {
}

bool Core::go() {
	mRunning = true;

	while(mRunning) {
		mRunning = compute(getRamValue(PC));
	}

	return true;
}

bool Core::step() {
	return compute(getRamValue(PC));
}

bool Core::compute(UInt16 word) {
	UInt16 a, b, op;
	UInt16 savedWord = word;

	// An instruction has the format aaaaaabbbbbooooo
	word = word/1024;
	a = word;

	word = savedWord-a*1024;
	word = word/32;
	b = word;

	word = savedWord-a*1024-b*32;
	op = word;

	increaseRegister(PC);

	return compute(a, b, op);
}

bool Core::compute(UInt16 a, UInt16 b, UInt16 op) {
	UInt16 value;
	UInt16* oldvalueptr = NULL;

	value = handleA(a);
	oldvalueptr = handleB(b);
	return handleOpCode(oldvalueptr, value, op);
}

UInt16 Core::handleA(UInt16 a) {
	UInt16 value=0;

	switch(a) {
	
	case 0:
		value = A;
		break;

	case 1:
		value = B;
		break;

	case 2:
		value = C;
		break;

	case 3:
		value = X;
		break;

	case 4:
		value = Y;
		break;

	case 5:
		value = Z;
		break;

	case 6:
		value = I;
		break;

	case 7:
		value = J;
		break;
	
	case 8:
		value = getRamValue(A);
		break;

	case 9:
		value = getRamValue(B);
		break;

	case 10:
		value = getRamValue(C);
		break;

	case 11:
		value = getRamValue(X);
		break;

	case 12:
		value = getRamValue(Y);
		break;

	case 13:
		value = getRamValue(Z);
		break;

	case 14:
		value = getRamValue(I);
		break;

	case 15:
		value = getRamValue(J);
		break;

	case 16:
		value = getRamValue(A+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 17:
		value = getRamValue(B+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 18:
		value = getRamValue(C+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 19:
		value = getRamValue(X+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 20:
		value = getRamValue(Y+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 21:
		value = getRamValue(Z+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 22:
		value = getRamValue(I+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 23:
		value = getRamValue(J+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 0x18:
		value = getRamValue(SP);
		increaseRegister(SP);
		break;

	case 0x19:
		value = getRamValue(SP);
		break;

	case 0x1A:
		value = getRamValue(SP+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 0x1B:
		value = SP;
		break;
		
	case 0x1C:
		value = PC;
		break;

	case 0x1D:
		value = EX;
		break;

	case 0x1E:
		value = getRamValue(PC);
		increaseRegister(PC);
		break;

	default:
		value = a-0x20;
	}

	return value;
}

UInt16* Core::handleB(UInt16 b) {
	UInt16* oldvalueptr = NULL;

	switch(b) {
	
	case 0:
		oldvalueptr = &A;
		break;

	case 1:
		oldvalueptr = &B;
		break;

	case 2:
		oldvalueptr = &C;
		break;

	case 3:
		oldvalueptr = &X;
		break;

	case 4:
		oldvalueptr = &Y;
		break;

	case 5:
		oldvalueptr = &Z;
		break;

	case 6:
		oldvalueptr = &I;
		break;

	case 7:
		oldvalueptr = &J;
		break;
	
	case 8:
		oldvalueptr = getRamPtr(A);
		break;

	case 9:
		oldvalueptr = getRamPtr(B);
		break;

	case 10:
		oldvalueptr = getRamPtr(C);
		break;

	case 11:
		oldvalueptr = getRamPtr(X);
		break;

	case 12:
		oldvalueptr = getRamPtr(Y);
		break;

	case 13:
		oldvalueptr = getRamPtr(Z);
		break;

	case 14:
		oldvalueptr = getRamPtr(I);
		break;

	case 15:
		oldvalueptr = getRamPtr(J);
		break;

	case 16:
		oldvalueptr = getRamPtr(A+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 17:
		oldvalueptr = getRamPtr(B+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 18:
		oldvalueptr = getRamPtr(C+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 19:
		oldvalueptr = getRamPtr(X+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 20:
		oldvalueptr = getRamPtr(Y+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 21:
		oldvalueptr = getRamPtr(Z+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 22:
		oldvalueptr = getRamPtr(I+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 23:
		oldvalueptr = getRamPtr(J+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 0x18:
		decreaseRegister(SP);
		oldvalueptr = getRamPtr(SP);
		break;

	case 0x19:
		oldvalueptr = getRamPtr(SP);
		break;

	case 0x1A:
		oldvalueptr = getRamPtr(SP+getRamValue(PC));
		increaseRegister(PC);
		break;

	case 0x1B:
		oldvalueptr = &SP;
		break;
		
	case 0x1C:
		oldvalueptr = &PC;
		break;

	case 0x1D:
		oldvalueptr = &EX;
		break;

	case 0x1E:
		oldvalueptr = getRamPtr(PC);
		increaseRegister(PC);
		break;

	default:
		oldvalueptr = NULL;
	}

	return oldvalueptr;
}

bool Core::handleOpCode(UInt16* ptr, UInt16 value, UInt16 opcode) {
	if(ptr == NULL)
		return false;

	switch(opcode) {

	case 1: // SET
		*ptr = value;
		break;

	case 2: // ADD
		*ptr = *ptr+value;
		break;

	case 3: // SUB
		*ptr = *ptr-value;
		break;

	case 4: // MUL
		EX = ((*ptr * value) >> 16)&0xFFFF;
		*ptr = *ptr * value;
		break;

	case 5: // MLI
		break;

	case 6: // DIV
		if(value == 0) {
			*ptr = 0;
			EX = 0;
		} else {
			EX = ((*ptr / value) << 16)&0xFFFF;
			*ptr = *ptr / value;
		}
		break;

	case 7: // DVI
		break;

	case 8: // MOD
		if(value == 0) {
			*ptr = 0;
		} else {
			*ptr = modulo(*ptr, value);
		}
		break;

	case 9: // MDI
		break;

	case 10: // AND
		*ptr = *ptr & value;
		break;

	case 11: // BOR
		*ptr = *ptr | value;
		break;

	case 12: // XOR
		*ptr = *ptr ^ value;
		break;

	case 13: // SHR
		EX = ((*ptr<<16)>>value)&0xFFFF;
		*ptr = *ptr >> value;
		break;

	case 14: // ASR
		EX = ((*ptr<<16)>>value)&0xFFFF;
		*ptr = *ptr >> value;
		break;

	case 15: // SHL
		EX = ((*ptr<<value)>>16)&0xFFFF;
		*ptr = *ptr << value;
		break;

	case 0x10: // IFB
		if((*ptr)&value != 0) {

		} else {
			increaseRegister(PC);
		} break;

	case 0x11: // IFC
		if((*ptr)&value == 0) {

		} else {
			increaseRegister(PC);
		} break;

	case 0x12: // IFE
		if(*ptr == value) {

		} else {
			increaseRegister(PC);
		} break;

	case 0x13: // IFN
		if(*ptr != value) {

		} else {
			increaseRegister(PC);
		} break;

	case 0x14: // IFG
		if(*ptr > value) {

		} else {
			increaseRegister(PC);
		} break;

	case 0x15: // IFA
		break;

	case 0x16: // IFL
		if(*ptr < value) {

		} else {
			increaseRegister(PC);
		} break;

	case 0x17: // IFU
		break;

	case 0x18: case 0x19:
		break;

	case 0x1A: // ADX
		*ptr = *ptr+value+EX;
		if((int) *ptr+(int) value+(int) EX>0xFFFF) {
			EX = 1;
		} else {
			EX = 0;
		}
		break;

	case 0x1B : // SBX
		*ptr = *ptr-value+EX;
		if(*ptr < 0) {
			EX = 0xFFFF;
		} else {
			EX = 0;
		}
		break;

	case 0x1C: case 0x1D:
		break;

	case 0x1E: // STI
		*ptr = value;
		increaseRegister(I); // I
		increaseRegister(J); // J
		break;

	case 0x1F: // STI
		*ptr = value;
		decreaseRegister(I); // I
		decreaseRegister(J); // J
		break;

	case 0x20: // JSR
		setRamValue(SP, getRamValue(PC+1));
		PC = value;
		break;

	case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
		break;

	case 0x27: // INT
		break;

	case 0x28: // IAG
		A = IA;
		break;

	case 0x29: // IAS
		IA = A;
		break;

	case 0x2A: // RFI
		break;

	case 0x2B: // IAQ
		break;

	case 0x2C: case 0x2D: case 0x2E:
		break;

	case 0x2F: // HWN
		*ptr = mNbDevices;
		break;

	case 0x30: // HWQ
		if(mDevices[*ptr] != NULL) {
			return mDevices[*ptr]->query();
		}
		break;

	case 0x32: // HWI
		if(mDevices[*ptr] != NULL) {
			mDevices[*ptr]->interrupt();
		}
		break;

	case 0x33: case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39: case 0x3A: case 0x3B: case 0x3C: case 0x3D: case 0x3E: case 0x3F:
		break;

	default:
		return false;
		
	}

	return true;
}

void Core::setRamValue(UInt16 n, UInt16 value) {
	mRAM[n] = value;
}

UInt16 Core::getRamValue(UInt16 n) {
	return mRAM[n];
}

UInt16* Core::getRamPtr(UInt16 n) {
	return (mRAM + n);
}

int Core::modulo(int n, int x) {
	if(x == 0) {
		return 0;
	}
	
	n = n%x;
	if(n < x) {
		return n;
	} else {
		return modulo(n, x);
	}
}

void Core::setRegister(UInt16& reg, UInt16 value) {
	reg = value;
}

void Core::setRegister(unsigned int n, UInt16 value) {
	if(n<8) {
		switch(n) {
		case 0:
			A = value;
			break;

		case 1:
			B = value;
			break;

		case 2:
			C = value;
			break;

		case 3:
			X = value;
			break;

		case 4:
			Y = value;
			break;

		case 5:
			Z = value;
			break;

		case 6:
			I = value;
			break;

		case 7:
			J = value;
			break;
		}
	}
}

UInt16 Core::increaseRegister(UInt16& reg) {
	reg++;
	return reg;
}

UInt16 Core::decreaseRegister(UInt16& reg) {
	reg--;
	return reg;
}

bool Core::connect(Device* dev) {
	mDevices[mNbDevices] = dev;
	mNbDevices++;
	dev->setCore(this);
}