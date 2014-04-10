#pragma once

#include <iostream>
#include <fstream>
#include <utility> // Include to use the pair class
#include <vector>
#include <string>

namespace BubbleCat {
	class Assembler
	{
	public:
		Assembler(void);
		virtual ~Assembler(void);

		void loadGrammar(std::string grammarPath);
		bool loadPairFromFile(std::string file, std::vector<std::pair<std::string, int> > &arr);

		void handleLine(std::string line);

		bool isBasic(std::string s);
		bool isSpecial(std::string s);
		bool isValue(std::string s);


	private:
		std::vector<std::pair<std::string, int> > mBasicOpCodeArray;
		std::vector<std::pair<std::string, int> > mSpecialCodeArray;
		std::vector<std::pair<std::string, int> > mValueArray;
	};
}

