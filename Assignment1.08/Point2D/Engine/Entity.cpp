#include <stdlib.h>
#include "Point2D.cpp"

class Entity {

	const char* name = new char[50];
	int id = 0;
	Point2D point;
	int life = 0;
	

public:

	Entity(int entityId, int xCoor, int yCoor, int entityLife) {
		id = entityId;
		point = Point2D(xCoor, yCoor);
		life = entityLife;
	}

	Entity() {
		life = 5;
	}

	~Entity() {
		
	}


	Entity(char* entityName, int xCoor, int yCoor) {
		name = entityName;
		point = Point2D(xCoor, yCoor);
	}

	const char* getName() {
		return name;
	}

	int getXCoordinate() {
		return point.getXCoordinate();
	}

	int getYCoordinate() {
		return point.getYCoordinate();
	}

	void setXCoordinate(int x) {
		point.setXCoordinate(x);
	}

	void setYCoordinate(int y) {
		point.setYCoordinate(y);
	}

	void updatePositions(int xValue, int yValue) {
		life--;
		Point2D p = Point2D(xValue, yValue);
		point = point + p;	
	}

	int getLife() {
		return life;
	}

	int getId() {
		return id;
	}

	void destroyObjects() {
		delete name;
		/*if (point != nullptr) {
			delete point;
		}*/
	
	}


};

