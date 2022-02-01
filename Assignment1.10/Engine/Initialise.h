#pragma once
#include "Entity.h"
#include "EntityComponent.cpp"

namespace Engine {
	void initialise();

	void test();

	void displayGameName(const char* name);

	Entity* initialisePlayer(char* name, int xCoordinate, int yCoordinate);
}