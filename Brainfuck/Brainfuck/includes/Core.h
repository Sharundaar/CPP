#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

#define RAM_SIZE 1000

class Core {
	public:
		Core();
		virtual ~Core();

		void go();

		void init();
		void loop();

		void incCursor();
		void decCursor();

		void compute(char ptr);
		//void compute(char[] file);

	private:
		char mRAM[RAM_SIZE];
		char cursor;
};

#endif