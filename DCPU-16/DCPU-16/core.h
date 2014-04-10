#pragma once

#include <cstdlib>
#include <vector>
#include "device.h"

namespace BubbleCat {

	typedef unsigned short int UInt16;

	class Core 
	{
	public:
		Core(void);
		virtual ~Core(void);

		bool go();
		bool step();

		bool compute(UInt16 word);
		bool compute(UInt16 a, UInt16 b, UInt16 op);

		UInt16 handleA(UInt16 a);
		UInt16* handleB(UInt16 b);
		bool handleOpCode(UInt16* ptr, UInt16 value, UInt16 opcode);

		void setRamValue(UInt16 n, UInt16 value);

		UInt16 getRamValue(UInt16 n);
		UInt16* getRamPtr(UInt16 n);

		// Perform n%x until n < x
		int modulo(int n, int x);

		UInt16 increaseRegister(UInt16& reg);
		UInt16 decreaseRegister(UInt16& reg);

		bool connect(Device* dev);

		void setRegister(UInt16& reg, UInt16 value);
		void setRegister(unsigned int n, UInt16 value);

		void setRegisterA(UInt16 value) { A = value; }
		void setRegisterB(UInt16 value) { B = value; }
		void setRegisterC(UInt16 value) { C = value; }
		void setRegisterX(UInt16 value) { X = value; }
		void setRegisterY(UInt16 value) { Y = value; }
		void setRegisterZ(UInt16 value) { Z = value; }
		void setRegisterI(UInt16 value) { I = value; }
		void setRegisterJ(UInt16 value) { J = value; }

	private:
		UInt16 mRAM[0x10000];
		UInt16 A, B, C, X, Y, Z, I, J;
		UInt16 PC;
		UInt16 SP;
		UInt16 EX;
		UInt16 IA;
		bool mRunning;

		BubbleCat::Device* mDevices[0x10000];
		int mNbDevices;
	};
}

