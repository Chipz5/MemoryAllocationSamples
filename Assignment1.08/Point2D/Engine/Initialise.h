#pragma once
#include "Entity.h"

namespace Engine {
	void initialise();

	inline void test();

	inline void displayGameName(const char* name);

	Entity* initialiseEntity(char* name, int xCoordinate, int yCoordinate);
}