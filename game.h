// Contains the declarations of Item class, 
// Potion class (subclass of Item class),and Map class

#include <iostream>
#include "player.h"
#include "monster.h"

using namespace std;

class Item
{
    public:
        Item();
        Item(int, int);
        int GetX() const;
        int GetY() const;
    private:
        double x;
        double y;        
};

// Inherits from Item class
class Potion: public Item
{
    public:
        Potion();
        Potion(int, int);
        int GetX() const;
        int GetY() const;
    private:
        double x;
        double y;  
};

class Map
{
    public:
        Map(int _mapSize);
        ~Map();
        void Print();

        void MovePlayer();

        void PositionCheck();

        int GetEntityCount() const;
        int GetPlayerMonCount() const;
        int GetPlayerCoinCount() const;


    private:
        int mapSide;            // Map sides' size
        int mapArea;            // Playable map area 
        int iMaxSize;           // Max number of items
        int iCurrentSize;       // Current number of items
        int pMaxSize;           // Max number of potions
        int pCurrentSize;       // Current number of potions
        int mMaxSize;           // Max number of monsters
        int mCurrentSize;       // Current number of monsters
        int monsterCounter;     // Number of encounters with monsters. If monsterCounter == mCurrentSize, all monsters were defeated
        int entities;           // Number of coordinates (number of entities)
        //int CoordPairs[][2];
        Item* itemList;         // List of items
        Potion* potionList;     // List of potions
        Monster** monsterList;  // List of monsters
        Player AshKetchup;      // Player
        bool isRepeated(int CoordPairs[][2], int coordsCounter, int x, int y);

        bool CatchAttempt(const Monster*); // Attempts to catch the monster the player is currently in battle with
        bool monsterCaught;     // Flag for if the monster is caught

        void RemoveCoin(int);
        void RemovePotion(int);
        void RemoveMonster(int);

        int ChooseMonster();    // Handles logic for selecting a monster and putting them in play

        void Battle(Monster*);
        void Wait();
        void Run();
        void UsePotion();
};