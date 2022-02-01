#include "Player.h"
#include<string.h>

int Player::getXCoordinate() {
	return xCoordinate;
}

int Player::getYCoordinate() {
	return yCoordinate;
}

void Player::setXCoordinate(int updatedXCoordinate) {
	xCoordinate = updatedXCoordinate;
}

void Player::setYCoordinate(int updatedYCoordinate) {
	yCoordinate = updatedYCoordinate;
}

Player::Player(char inputName[]) {
	strcpy_s(name, inputName);
}