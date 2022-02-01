#include<iostream>
#include "Initialise.h"

namespace Engine {
	void initialise() {
		std::printf("HELLO!");
	}

	void displayGameName(const char* name) {
		std::cout << name << std::endl;
	}

	Entity* initialisePlayer(char* name, int xCoordinate, int yCoordinate) {

		Entity* entity = new Entity(name, xCoordinate, yCoordinate);
		return entity;
	}
}