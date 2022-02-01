
#pragma once
using namespace std;
class Player
{
	private:
		
		int xCoordinate = 0;
		int yCoordinate = 0;

	public:
		char name[50] = { '\0' };
		int getXCoordinate();
		int getYCoordinate();
		void setXCoordinate(int updatedXCoordinate);
		void setYCoordinate(int updatedYCoordinate);
		Player(char inputName[]);

};

