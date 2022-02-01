#include <iostream>
#include <Initialise.cpp>
#define _CRTDBG_MAP_ALLOC

using namespace std;

static int noOfMonsters = 0;
static int monsterNo = 1;
static int maxMonsters = 100;
Entity* monsters = nullptr;
//menu options
void ShowMenu() {
    cout << "Enter choice\n";
    cout << "a - Player moves left\n";
    cout << "d - Player moves right\n";
    cout << "w - Player moves up\n";
    cout << "s - Player moves down\n";
    cout << "q - Quit\n\n";

}

//updates monster positions
void updateMonsterPositions(Entity* monsters, Entity* player) {
    int playerXCoordinate = player->getXCoordinate();
    int playerYCoordinate = player->getYCoordinate();
    for (int i = 0; i < noOfMonsters; i++) {
        monsters[i].updatePositions((rand() % 101 + (-50)), (rand() % 101 + (-50)));
        // game stops if monster and player are at the same position.
        if (monsters[i].getXCoordinate() == playerXCoordinate && monsters[i].getYCoordinate() == playerYCoordinate) {
            cout << "GAME OVER! MONSTER AND PLAYER ARE AT THE SAME POSITION" << endl << "START AGAIN" << endl;
            return;
         
        }
        // each monster starts out with 5 lives which decrements after each player turn
        // when the life hits 0, the monster is destroyed.
        if (monsters[i].getLife() == 1) {
            cout << "WARNING: Monster" << monsters[i].getId() << " is almost out of lives" <<endl;
        }
        
    }
  
   for (int i = 0; i < noOfMonsters && i >=0; i++) {
       if (monsters[i].getLife() == 0) {
           for (int j = i; j < noOfMonsters-1; j++) {
                monsters[j] = monsters[j + 1];
            }
            i--;
            noOfMonsters--;
      }
   }
    
}

inline Entity* initialiseMonsters() {
    if (monsters != nullptr) {
        cout << "Initialisation failed" << endl;
    }
    else {
        if (noOfMonsters > maxMonsters) {
            maxMonsters = noOfMonsters;
        }
        monsters = new Entity[maxMonsters];
        for (int j = 0; j < noOfMonsters; j++) {
            monsters[j] = *new Entity(monsterNo, rand() % 50 + 1, rand() % 50 + 1, 5);
            monsterNo = monsterNo + 1;
        }
    }
    return monsters;
}

//checks if monster can be added based on whether random no. generated is even.
void canAddMonster(Entity* monsters) {
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

int main(void) {
    Engine::test();
    Engine::displayGameName("-------------------- MONSTER CHASE ---------------------");
    char* nameOfPlayer;
    nameOfPlayer = new char[50];
    cout << "Enter the player name (maximum 50 chars)" << endl;
    cin >> nameOfPlayer;
    Entity* player = Engine::initialiseEntity(nameOfPlayer, 0, 0);
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
    monsters = initialiseMonsters();
    if (monsters == nullptr) {
        return 0;
    }
    bool quit = false;
    char move;
    while (!quit) {
        cout << "Current positions" << endl;
        for (int i = 0; i < noOfMonsters; i++) {
            printf("Monster : ");
            cout << monsters[i].getId() << endl;
            cout << endl << "X coordinate : " << monsters[i].getXCoordinate() << endl << "Y coordinate : " << monsters[i].getYCoordinate() << endl;
        }
        printf("Player: ");
        cout << player->getName() << endl;
        printf("X coordinate : %d \n", player->getXCoordinate());
        printf("y coordinate : %d \n ", player->getYCoordinate());
        
        ShowMenu();

        cin >> move;

        switch (move) {
        case 'a':
            player->updatePositions(-1, 0);
            updateMonsterPositions(monsters, player);
            canAddMonster(monsters);
            break;

        case 'w':
            player->updatePositions(0, 1);
            updateMonsterPositions(monsters, player);
            canAddMonster(monsters);
            break;

        case 'd':
            player->updatePositions(1, 0);
            updateMonsterPositions(monsters, player);
           canAddMonster(monsters);
            break;

        case 's':
            player->updatePositions(0, -1);
            updateMonsterPositions(monsters, player);
            canAddMonster(monsters);
            break;

        case 'q':
            quit = true;
            break;

        default:
            cout << "Bad Input, Try again " << endl;
            break;
        }

    }
    delete[] nameOfPlayer;
    delete player;
    delete[] monsters;
    return 0;
}
