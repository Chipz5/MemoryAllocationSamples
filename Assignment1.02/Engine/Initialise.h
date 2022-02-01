#pragma once
#include "Entity.h"

namespace Engine {
	void initialise();

	void test();

	void displayGameName(const char* name);

	Entity* initialiseEntity(char* name, int xCoordinate, int yCoordinate);
}