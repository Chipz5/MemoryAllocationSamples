#pragma once
#include "Point2D.cpp"
#include <iostream>

using namespace std;
class EntityComponent {
	virtual void updatePositions(Point2D p) = 0;
	virtual int getInput() = 0;
	virtual void checkCondition(Point2D mon, Point2D play) = 0;
};


class Entity : EntityComponent {

	char* name = new char[50];
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

	char* getName() {
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

	void updatePositions(Point2D p) {
		life--;
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

	int getInput() {
		return 0;
	}

	void checkCondition(Point2D mon, Point2D play) {

	}

};


class Monster : EntityComponent {
	char* name = new char[50];
	int id = 0;
	Point2D point;
	int life = 0;


public:

	Monster(int entityId, int xCoor, int yCoor, int entityLife) {
		id = entityId;
		point = Point2D(xCoor, yCoor);
		life = entityLife;
	}

	Monster() {
		life = 5;
	}

	~Monster() {

	}


	Monster(char* entityName, int xCoor, int yCoor) {
		name = entityName;
		point = Point2D(xCoor, yCoor);
	}

	char* getName() {
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

	void updatePositions(Point2D p) {
		life--;
		//Point2D p = Point2D(xValue, yValue);
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

	int getInput() {
		return 0;
	}

	void checkCondition(Point2D mon, Point2D play) {

	}

};

class Player : EntityComponent {
	char* name = new char[50];
	int id = 0;
	Point2D point;
	int life = 0;


public:

	Player(int entityId, int xCoor, int yCoor, int entityLife) {
		id = entityId;
		point = Point2D(xCoor, yCoor);
		life = entityLife;
	}

	Player() {
		life = 5;
	}

	~Player() {

	}


	Player(char* entityName, int xCoor, int yCoor) {
		name = entityName;
		point = Point2D(xCoor, yCoor);
	}

	char* getName() {
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

	void updatePositions(Point2D p) {
		life--;
		//Point2D p = Point2D(xValue, yValue);
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

	int getInput() {
		return 0;
	}

	void checkCondition(Point2D mon, Point2D play) {

	}

};

class Helper : EntityComponent {
public:

	Helper(){

	}

	//menu options
	void ShowMenu() {
		cout << "Enter choice\n";
		cout << "a - Player moves left\n";
		cout << "d - Player moves right\n";
		cout << "w - Player moves up\n";
		cout << "s - Player moves down\n";
		cout << "q - Quit\n\n";

	}

	int getInput() {
		int noOfMonsters = 0;
		while (cin.fail() || noOfMonsters <= 0)
		{
			cout << "Enter the number of monsters to spawn (maximum 50)" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "You can only enter numbers.\n";
			cout << "Enter a number.\n";
			cin >> noOfMonsters;
			if (noOfMonsters <= 0) {
				cout << "Bad Input... Try again" << endl;
			}
		}
		return noOfMonsters;
	}

	void updatePositions(Point2D p) {

	}

	void checkCondition(Point2D mon, Point2D play) {

	}

};

class EntityMul : EntityComponent {
public:

	EntityMul(){

	}
	
	void addEntity(Entity* monsters, int noOfMonsters, int maxMonsters, int monsterNo) {
		Entity* temp = monsters;
		if ((rand() % 100) % 2 == 0) {
			if (noOfMonsters >= maxMonsters) {
				monsters = (Entity*)realloc(temp, sizeof(Entity) * ((size_t)(100)));
				maxMonsters = maxMonsters + 100;
			}
			if (monsters != NULL) {
				Entity m = *new Entity(monsterNo, rand() % 50 + 1, rand() % 50 + 1, 5);
				monsterNo = monsterNo + 1;
				monsters[noOfMonsters] = m;
				cout << "New Monster Added" << endl;
				noOfMonsters = noOfMonsters + 1;
			}
			else {
				cout << "Monster allocation failed" << endl;
			}

		}
	}

	void updateMonsterPositions(Entity* monsters, Entity* player, int noOfMonsters) {
		int playerXCoordinate = player->getXCoordinate();
		int playerYCoordinate = player->getYCoordinate();
		for (int i = 0; i < noOfMonsters; i++) {
			Point2D p = Point2D((rand() % 101 + (-50)), (rand() % 101 + (-50)));
			monsters[i].updatePositions(p);
			// game stops if monster and player are at the same position.
			Point2D mon = Point2D(monsters[i].getXCoordinate(), monsters[i].getYCoordinate());
			Point2D play = Point2D(playerXCoordinate, playerYCoordinate);

			checkCondition(mon, play);

			/*if (monsters[i].getXCoordinate() == playerXCoordinate && monsters[i].getYCoordinate() == playerYCoordinate) {
				cout << "GAME OVER! MONSTER AND PLAYER ARE AT THE SAME POSITION" << endl << "START AGAIN" << endl;
				return;

			}*/
			// each monster starts out with 5 lives which decrements after each player turn
			// when the life hits 0, the monster is destroyed.
			if (monsters[i].getLife() == 1) {
				cout << "WARNING: Monster" << monsters[i].getId() << " is almost out of lives" << endl;
			}

		}

		for (int i = 0; i < noOfMonsters && i >= 0; i++) {
			if (monsters[i].getLife() == 0) {
				for (int j = i; j < noOfMonsters - 1; j++) {
					monsters[j] = monsters[j + 1];
				}
				i--;
				noOfMonsters--;
			}
		}

	}


	void checkCondition(Point2D mon, Point2D play) {
		if (mon == play) {
			cout << "GAME OVER! MONSTER AND PLAYER ARE AT THE SAME POSITION" << endl << "START AGAIN" << endl;
			return;
		}

	}

	void updatePositions(Point2D p) {

	}

	int getInput() {
		return 0;
	}
};