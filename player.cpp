// The file "player.cpp" contains the definition of Player class

#include "player.h"

// default constructor
Player::Player()
{
    maxSize = 6;
    currentSize = 3;

    coins = 0;
    potions = 0;

    monsterList = new Monster*[maxSize];

    monsterList[0] = new GrassMonster(0);
    monsterList[1] = new FireMonster(1);
    monsterList[2] = new WaterMonster(2);
    
    x_coord = 0;
    y_coord = 0;
}

// Constructor for the player's values and list of monsters
Player::Player(int x_in, int y_in)
{
    maxSize = 6;
    currentSize = 3;

    coins = 0;
    potions = 0;

    monsterList = new Monster*[maxSize];

    monsterList[0] = new GrassMonster(0);
    monsterList[1] = new FireMonster(1);
    monsterList[2] = new WaterMonster(2);

    x_coord = x_in;
    y_coord = y_in;
}

// Destructor for the player's list of monsters
Player::~Player()
{
    for(int i = 0; i < currentSize; i++)
    {
        delete monsterList[i];
    }
}

// Getter for the player's X coordinate
int Player::GetX() const
{
    return x_coord;
}

// Getter for the player's Y coordinate
int Player::GetY() const
{
    return y_coord;
}

// Setter for the player's X coordinate
void Player::SetX(int x_in)
{
    x_coord = x_in;
}

// Setter for the player's Y coordinate
void Player::SetY(int y_in)
{
    y_coord = y_in;
}

// Getter for the player's current coin count
int Player::GetCoinCount() const
{
    return coins;
}

// Getter for the player's current number of monsters
int Player::GetMonsterCount() const
{
    return currentSize;
}

// Getter for the player's current potion count
int Player::GetPotionCount() const
{
    return potions;
}

// Add a monster to the roster if caught
void Player::AddMonster(Monster*& newMon)
{
    if(currentSize == maxSize)
        Grow();
    
    char typeG[] = "Grass";
    char typeF[] = "Fire";
    char typeW[] = "Water";


    
    if (strcmp(typeG, newMon->GetType()) == 0){


        Monster* tempGrass = new GrassMonster(currentSize, newMon->GetSize());
        monsterList[currentSize] = tempGrass;
    }
    else if (strcmp(typeF, newMon->GetType()) == 0){


        Monster* tempFire = new FireMonster(currentSize, newMon->GetSize());

        monsterList[currentSize] = tempFire;
    }
    else if (strcmp(typeW, newMon->GetType()) == 0){

        Monster* tempW = new WaterMonster(currentSize, newMon->GetSize());
        monsterList[currentSize] = tempW;
    }
    currentSize++;
    
}

// Remove a monster from the roster when they faint
void Player::RemoveMonster(int ind){
    PrintMonData(ind);
    for(int i = ind + 1; i < currentSize; i++)
    {
        monsterList[i - 1] = monsterList[i];
    }
    monsterList[currentSize - 1] = NULL;

    currentSize--;
}

bool Player::PlayerMonSpAtk(int index, Monster* wildMon)
{
    monsterList[index]->SpecialAttack(wildMon);
    if(wildMon->GetHealth() > 0)
        return true;   // IF IT IS ALIVE
    else
        return false;  // IF IT IS DEAD
}

bool Player::PlayerMonPhysAtk(int index, Monster* wildMon)
{
    monsterList[index]->PhysicalAttack(wildMon);
    if(wildMon->GetHealth() > 0)
        return true;   // IF IT IS ALIVE
    else
        return false;  // IF IT IS DEAD
}

// Print monster list, for testing
void Player::PrintMonList()
{
    for(int i = 0; i < currentSize; i++)
    {
        cout << "Monster # " << i << '\n';
        monsterList[i]->PrintMonsterData();
        cout << "\n";
    }
}

// Print single monster data
void Player::PrintMonData(int ind) const{
    monsterList[ind]->PrintMonsterData();
}

// Grows the list if needed
void Player::Grow()
{
    // Grows the pairs array if needed
    // Increase max size of the array
    maxSize = currentSize + 1;
    // Create a new temporary pair array with the size of the new max size
    Monster** tempList = new Monster*[maxSize];

    // Copy all elements from old array to the new array
    for(int i = 0; i < currentSize; i++)
    {
        tempList[i] = monsterList[i];
    }

    // De-allocate the old array
    delete [] monsterList;

    // Re-point to the newly sized array
    monsterList = tempList;
}

// Returns the monster list
Monster** Player::GetMonsterList() const
{
    return monsterList;
}

// Returns the monster list
Monster* Player::GetPlayerMon(int index) const
{
    return monsterList[index];
}

// Add a coin to the player's inventory
void Player::AddCoin()
{
    coins++;
}

// Add a potion to the player's inventory
void Player::AddPotion()
{
    potions++;
}

// Remove a potion from the player's inventory when used
void Player::RemovePotion()
{
    potions--;
}

// Used by the game class to move the player
void Player::MovePlayer(char char_in, int mapSide)
{
    switch(char_in)
    {
        case 'W':
            if(y_coord > 1)
                y_coord--;
                
            break;

        case 'S':
            if(y_coord < (mapSide - 2))
                y_coord++;

            break;

        case 'D':
            if(x_coord < (mapSide - 2))
                x_coord++;

            break;

        case 'A':
            if(x_coord > 1)
                x_coord--;

            break;
    }
}