#include "Monster.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

Monster::Monster(){
	id = rand() % 100;
	xCoordinate = rand() % 50 + 1;
	yCoordinate = rand() % 50 + 1;
	life = 5;
}

int Monster::getXCoordinate() {
	return xCoordinate;
}

int Monster::getYCoordinate() {
	return yCoordinate;
}

void Monster::updatePositions() {
	life--;
	xCoordinate = xCoordinate + (rand() % 101 + (-50));
	yCoordinate = yCoordinate + (rand() % 101 + (-50));
}

int Monster::getLife() {
	return life;
}

int Monster::getId() {
	return id;
}
