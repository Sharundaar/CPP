#pragma once

#include <vector>
#include "word.h"

namespace BubbleCat {
	class Grammar
	{
	public:
		Grammar(void);
		virtual ~Grammar(void);

	private:
		std::vector<Word> WordList;
	};
}
