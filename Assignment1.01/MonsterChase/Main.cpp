#include <iostream>

#include "Monster.h"
#include "Player.h"

using namespace std;

static int noOfMonsters = 0;
Monster* monsters = nullptr;
static int maxMonsters = 50;
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
void updateMonsterPositions(Monster* monsters, Player* player) {
    int playerXCoordinate = player->getXCoordinate();
    int playerYCoordinate = player->getYCoordinate();
    for (int i = 0; i < noOfMonsters; i++) {
        monsters[i].updatePositions();
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

    for (int i = 0; i < noOfMonsters && i>=0; i++) {
        if (monsters[i].getLife() == 0) {
            for (int j = i; j < noOfMonsters-1; j++) {
                monsters[j] = monsters[j + 1];
            }
            i--;
            noOfMonsters--;
        }
    }
    
}

////checks if monster can be added based on whether random no. generated is even.
void canAddMonster(Monster* monsters) {
   if ((rand() % 100) % 2 == 0) {
       if (noOfMonsters >= maxMonsters) {
           Monster* temp = monsters;
           monsters = (Monster*)realloc(temp, sizeof(Monster) * ((size_t)(100)));
           maxMonsters = maxMonsters + 100;
       }
       if (monsters != NULL) {
           Monster m;
           monsters[noOfMonsters] = m;
           noOfMonsters = noOfMonsters + 1;
           cout << "New Monster Added" << endl;
       }
       else {
              cout << "Monster allocation failed" << endl;
            }
    }

}

int main() {
    char* nameOfPlayer;
    nameOfPlayer = new char[50];
    cout << "------------- MONSTER CHASE --------------" << endl;
    cout << "Enter the player name (maximum 50 chars)" << endl;
    cin >> nameOfPlayer;
    while (cin.fail() || noOfMonsters <= 0)
    {
        cout << "Enter the number of monsters to spawn (maximum 50)" << endl;
        cin.clear(); 
        cin.ignore(INT_MAX, '\n'); 
        cin >> noOfMonsters;
        if (noOfMonsters <= 0) {
            cout << "Bad Input... Try again" << endl;
        }
    }
    

    Player* player = new Player(nameOfPlayer);
    if (noOfMonsters > maxMonsters) {
        maxMonsters = noOfMonsters;
    }
    Monster* monsters = new Monster[maxMonsters];
    bool quit = false;
    char move;
 
    while (!quit) {
        cout << "Current positions" << endl;
        for (int i = 0; i < noOfMonsters; i++) {
            printf("Monster : ");
            cout << "M" << monsters[i].getId();
            cout << endl << "X coordinate : "<< monsters[i].getXCoordinate() << endl << "Y coordinate : "<< monsters[i].getYCoordinate() <<endl;
        }
        printf("Player: ");
        cout << player->name <<endl;
        printf("X coordinate : %d \n", player->getXCoordinate());
        printf("y coordinate : %d \n ", player->getYCoordinate());
        ShowMenu();
        cin >> move;

        switch (move) {
        case 'a':
            player->setXCoordinate(player->getXCoordinate() -1);
            updateMonsterPositions(monsters, player);
            canAddMonster(monsters);
            break;

        case 'w':
            player->setYCoordinate(player->getYCoordinate() +1);
            updateMonsterPositions(monsters, player);
            canAddMonster(monsters);
            break;

        case 'd':
            player->setXCoordinate(player->getXCoordinate() +1);
            updateMonsterPositions(monsters, player);
            canAddMonster(monsters);
            break;

        case 's':
            player->setYCoordinate(player->getYCoordinate() -1);
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
    delete[]monsters;
    _CrtDumpMemoryLeaks();
    return 0;
}

