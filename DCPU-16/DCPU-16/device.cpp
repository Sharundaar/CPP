#include "device.h"

using namespace BubbleCat;

Device::Device(void)
{
	mID[0] = 0;
	mID[1] = 0;

	mManufacturer[0] = 0;
	mManufacturer[1] = 0;
}


Device::~Device(void) {
}

void Device::setCore(BubbleCat::Core* core) {
	this->core = core;
}

/*
 * Need to review this part !!
 */
bool Device::query() {
	core->setRegisterA(mID[1]);
	core->setRegisterB(mID[0]);
	core->setRegisterC(mVersion);
	core->setRegisterX(mManufacturer[1]);
	core->setRegisterY(mManufacturer[0]);
}
