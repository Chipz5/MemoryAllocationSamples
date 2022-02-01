
#pragma once
using namespace std;
class Monster
{
	private:
		int xCoordinate;
		int yCoordinate;
		int life; 
		int id;

	public:
		Monster();
		int getXCoordinate();
		int getYCoordinate();
		void updatePositions();
		int getLife();
		int getId();
};

