#pragma once

#include <string>
#include "core.h"

namespace BubbleCat {
	class Device
	{
	public:
		Device(void);
		virtual ~Device(void);

		void setCore(BubbleCat::Core* core);

		bool interrupt();
		bool query();

	private:
		BubbleCat::Core* core;
		
		std::string mName;
		UInt16 mID[2];
		UInt16 mVersion;
		UInt16 mManufacturer[2];

	};

}
