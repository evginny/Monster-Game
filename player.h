// The file "player.h" contains declaration of Player class
// Contains all information about player and player's monster list
// Contains all player functionality 

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "monster.h"

using namespace std;

class Player
{
    public:
        Player();
        // Constructor for the player's values and list of monsters
        Player(int, int);
        // Destructor for the player's list of monsters
        ~Player();

        // Getter for the player's X coordinate
        int GetX() const;
        // Getter for the player's Y coordinate
        int GetY() const;
        // Getter for the player's current coin count
        int GetCoinCount() const;
        // Getter for the player's current number of monsters
        int GetMonsterCount() const;
        // Getter for the player's current potion count
        int GetPotionCount() const;


        // Setter for the player's X coordinate
        void SetX(int);
        // Setter for the player's Y coordinate
        void SetY(int);

        // Print monster list, for testing
        void PrintMonList();

        // Print single monster data
        void PrintMonData(int ind) const;

        // Add a monster to the roster if caught
        void AddMonster(Monster*&);
        // Remove a monster from the roster when they faint
        void RemoveMonster(int ind);

        // Add a coin to the player's inventory
        void AddCoin();
        // Add a potion to the player's inventory
        void AddPotion();
        // Remove a potion from the player's inventory when used
        void RemovePotion();

        // Used by the game class to move the player
        void MovePlayer(char, int);

        // Returns the monster list
        Monster** GetMonsterList() const;
        Monster* GetPlayerMon(int) const;

        bool PlayerMonSpAtk(int, Monster*);
        bool PlayerMonPhysAtk(int, Monster*);

    private:
        // Dynamic array of monsters
        Monster** monsterList;
        // Max size of the monster list
        int maxSize;
        // Current size of the monster list
        int currentSize;
        // Grows the list if needed
        void Grow();

        // Player's inventory of coins
        int coins;
        // Player's inventory of potions
        int potions;

        // Player's X position on the map
        int x_coord;
        // Player's Y position on the map
        int y_coord;
};

#endif