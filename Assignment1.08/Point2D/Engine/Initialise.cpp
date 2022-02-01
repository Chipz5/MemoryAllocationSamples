#include<iostream>
#include "Point2DTest.cpp"

namespace Engine {
	void initialise() {
		std::printf("HELLO!");
	}

	inline void test() {
		std::printf("Running test cases ... ");
		Point2DTest();
	}

	inline void displayGameName(const char* name) {
		std::cout << name << std::endl;
	}

	inline Entity* initialiseEntity(char* name, int xCoordinate, int yCoordinate) {
		
		Entity* entity = new Entity(name, xCoordinate, yCoordinate);
		return entity;
	}
}