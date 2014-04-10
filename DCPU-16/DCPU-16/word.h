#pragma once

#include <string>

namespace BubbleCat {
	class Word
	{
	public:
		Word(void);
		virtual ~Word(void);

	private:
		std::string word;
		unsigned int value;
	};
}
