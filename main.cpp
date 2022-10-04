#include <iostream>
#include "monster.h"
#include "game.h"
#include "player.h"

using namespace std;

int main()
{
    int mapSize;
    cout << "Enter map size: ";
    cin >> mapSize;
    Map gameMap(mapSize);

    gameMap.Print();

    

    do
    {
        cout << "Entities in map: " << gameMap.GetEntityCount() << '\n';
        //cout << "Moving player\n";
        gameMap.MovePlayer();
        //cout << "Printing map\n";
        if (gameMap.GetPlayerMonCount() != 0){
            gameMap.Print();
        }
        
        //cout << "Entity count: " << gameMap.GetEntityCount();
        //cout << "Player mon count: " << gameMap.GetPlayerMonCount();
        
    } while((gameMap.GetEntityCount() > 1) && (gameMap.GetPlayerMonCount() > 0));

    cout << "The player's final coin count is: " << gameMap.GetPlayerCoinCount() << '\n';
    cout << "Main loop exited\n";
}