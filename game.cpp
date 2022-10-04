// Contains definitions for Item, Potion, and Map classes
// Also contains command for printing menu, getting commands from the user and
// validating those commands

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "player.h"
#include "monster.h"

using namespace std;

void PrintBattleMenu();
void PrintMoveMenu();
char GetPotionCommand();
char GetBattleCommand();
char GetMoveCommand();
char GetChar();
char LegalPotion(char);
char LegalBattle(char character); 
char LegalMove(char);
void UseBattleCommand(char);
void UseMoveCommand(char);

Item::Item(){};
Item::Item(int _x, int _y)
{
    x = _x;
    y = _y;
}

int Item::GetX() const
{
    return x;
}

int Item::GetY() const
{
    return y;
}

Potion::Potion(){}
Potion::Potion(int _x, int _y)
{
    x = _x;
    y = _y;
}
int Potion::GetX() const
{
    return x;
}
int Potion::GetY() const
{
    return y;
}

Map::Map(int _mapSide)
{
    monsterCounter = 0;

    mapSide = _mapSide; // Area of square is (mapSize - 2)^2
    mapArea = (mapSide - 2) * (mapSide - 2);

    // Max size functions for items and monsters in map depending on playable map area
    iMaxSize = ((mapArea / 5) + 1);
    pMaxSize = ((mapArea / 8) + 1);
    mMaxSize = ((mapArea / 15) + 1);

    // Generates a random number of items and monsters in the map [1 - max amount]
    srand(time(0));
    iCurrentSize = 1 + (rand() % iMaxSize);
    pCurrentSize = 1 + (rand() % pMaxSize);
    mCurrentSize = 1 + (rand() % mMaxSize);

    // Initializes the lists with items and monsters
    itemList = new Item[iMaxSize];
    potionList = new Potion[pMaxSize];
    monsterList = new Monster *[mMaxSize];
    // Array of CoordPairs pairs
    entities = iCurrentSize + pCurrentSize + mCurrentSize + 1; // Items + Monsters + Player
    int coordsCounter = 0;                          // Number of coords in array
    int CoordPairs[entities][2];                    // Array created to generate unique coordinates [object][0 -> x; 1 -> y]

    // Player creation
    // Player CoordPairs
    int x, y;
    x = 1 + (rand() % (mapSide - 2)); // Generates an x coordinate inside the playable area
    y = 1 + (rand() % (mapSide - 2)); // Generates an y coordinate inside the playable area
    CoordPairs[0][0] = x;
    CoordPairs[0][1] = y;
    coordsCounter++;
    // Player AshKetchup(x,y); // Creates a player with the random CoordPairs

    AshKetchup.SetX(x);
    AshKetchup.SetY(y);

    //cout << "Item# " << iCurrentSize << endl; // --Testing--
    // Items creation
    for (int i = 0; i < iCurrentSize; i++)
    {
        do
        {
            x = 1 + (rand() % (mapSide - 2)); // Generates an x coordinate inside the playable area
            y = 1 + (rand() % (mapSide - 2)); // Generates an y coordinate inside the playable area
        } while (isRepeated(CoordPairs, coordsCounter, x, y));
        coordsCounter++;

        CoordPairs[i + 1][0] = x;
        CoordPairs[i + 1][1] = y;

        Item item(x, y);
        itemList[i] = item;
    }
    // Potion creation
    for (int i = 0; i < pCurrentSize; i++)
    {
        do
        {
            x = 1 + (rand() % (mapSide - 2)); // Generates an x coordinate inside the playable area
            y = 1 + (rand() % (mapSide - 2)); // Generates an y coordinate inside the playable area
        } while (isRepeated(CoordPairs, coordsCounter, x, y));
        coordsCounter++;
        CoordPairs[i + 1][0] = x;
        CoordPairs[i + 1][1] = y;
        Potion potion(x, y);
        potionList[i] = potion;
        //cout << itemList[i].GetX() << " " << itemList[i].GetY() << endl; // --Testing--
    }
    for (int i = 0; i < mCurrentSize; i++)
    {
        do
        {
            x = 1 + (rand() % (mapSide - 2)); // Generates an x coordinate inside the playable area
            y = 1 + (rand() % (mapSide - 2)); // Generates an y coordinate inside the playable area
        } while (isRepeated(CoordPairs, coordsCounter, x, y));
        coordsCounter++;

        CoordPairs[i + iCurrentSize + 1][0] = x;
        CoordPairs[i + iCurrentSize + 1][1] = y;

        // Randomize Monster Type
        int type = rand() % 3;

        switch (type)
        {
        case 0:
            monsterList[i] = new WaterMonster(x, y, i);
            break;
        case 1:
            monsterList[i] = new FireMonster(x, y, i);
            break;
        case 2:
            monsterList[i] = new GrassMonster(x, y, i);
            break;
        }
    }
}

int Map::GetEntityCount() const
{
    return entities;
}

int Map::GetPlayerMonCount() const
{
    return AshKetchup.GetMonsterCount();
}

void Map::Print()
{
    char map[mapSide][mapSide]; // map[x][y]

    // Initialize all the map to
    for (int i = 0; i < mapSide; i++)
        for (int j = 0; j < mapSide; j++)
            map[i][j] = '.';

    // Add Player to map
    map[AshKetchup.GetX()][AshKetchup.GetY()] = 'P';
    //cout << "Player coord: " << AshKetchup.GetX() << " " << AshKetchup.GetY() << endl;

    // Add Items to map
    for (int i = 0; i < iCurrentSize; i++)
        map[itemList[i].GetX()][itemList[i].GetY()] = 'I';

    // Add Potions to map
    for (int i = 0; i < pCurrentSize; i++)
        map[potionList[i].GetX()][potionList[i].GetY()] = 'H';

    // Add Monsters to map
    for (int i = 0; i < mCurrentSize; i++)
        map[monsterList[i]->GetX()][monsterList[i]->GetY()] = 'M';

    // Print map
    for (int j = 0; j < mapSide; j++)
    {
        for (int i = 0; i < mapSide; i++)
        {
            if (i == 0 || i == (mapSide - 1)) // Top and Bottom boundaries
                cout << "# ";
            else if (j == 0 || j == (mapSide - 1)) // Left and Right boundaries
                cout << "# ";
            else
                cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

bool Map::isRepeated(int CoordPairs[][2], int coordsCounter, int x, int y)
{
    for (int j = 0; j < coordsCounter; j++)
        if ((x == CoordPairs[j][0]) && (y == CoordPairs[j][1]))
            return true;
    return false;
}

Map::~Map()
{
    delete itemList;
    delete potionList;
    delete[] monsterList;
}

void Map::MovePlayer()
{
    PrintMoveMenu();
    AshKetchup.MovePlayer(GetMoveCommand(), mapSide);
    PositionCheck();
}

void Map::PositionCheck()
{
    //cout << iCurrentSize;
    for (int i = 0; i < mCurrentSize; i++)
    {
        if ((monsterList[i]->GetX() == AshKetchup.GetX()) && (monsterList[i]->GetY() == AshKetchup.GetY()))
        {
            cout << "You encountered a monster!\n";
            Battle(monsterList[i]);
            AshKetchup.PrintMonList();
            if(monsterList[i]->GetHealth() <= 0 || monsterCaught == true)
                RemoveMonster(i);
        }
    }
    for (int i = 0; i < iCurrentSize; i++)
    {
        if ((itemList[i].GetX() == AshKetchup.GetX()) && (itemList[i].GetY() == AshKetchup.GetY()))
        {
            cout << "You collected a coin.\n";
            AshKetchup.AddCoin();
            RemoveCoin(i);
        }
    }
    for (int i = 0; i < pCurrentSize; i++)
    {
        if ((potionList[i].GetX() == AshKetchup.GetX()) && (potionList[i].GetY() == AshKetchup.GetY()))
        {
            cout << "You collected a potion.\n";
            AshKetchup.AddPotion();
            RemovePotion(i);
        }
    }
    
    return;
}

void Map::RemovePotion(int index)
{
    for(int i = index + 1; i < pCurrentSize; i++)
    {
        potionList[i - 1] = potionList[i];
    }
    pCurrentSize--;
    entities--;
}

void Map::RemoveCoin(int index)
{
    for(int i = index + 1; i < iCurrentSize; i++)
    {
        itemList[i - 1] = itemList[i];
    }

    iCurrentSize--;
    entities--;
}

void Map::RemoveMonster(int index)
{

    delete monsterList[index];
    for(int i = index + 1; i < mCurrentSize; i++)
    {
        monsterList[i - 1] = monsterList[i];
    }
    monsterList[mCurrentSize - 1] = NULL;

    mCurrentSize--;
    entities--;
}

void Map::Battle(Monster* wildMon)
{
    bool playerMonAlive = true;
    monsterCaught = false;
    int index;
    char potionChoice;

    cout << "Wild monster encountered!\n";
    wildMon->PrintMonsterData();
    cout << '\n';

    if (AshKetchup.GetMonsterCount() != 0) {
        index = ChooseMonster();
        cout << "You chose: \n";
        AshKetchup.PrintMonData(index); 
    }
    else {
        cout << "All player's monsters are defeated. GAME OVER \n";
        return;
    }

    
    do
    {
        cout << "Your mon's max hp: " << AshKetchup.GetPlayerMon(index)->GetMaxHealth() << '\n';
        cout << "Your mon's current hp: " << AshKetchup.GetPlayerMon(index)->GetHealth() << '\n';
        if(AshKetchup.GetPotionCount() > 1 && (AshKetchup.GetPlayerMon(index)->GetHealth() < AshKetchup.GetPlayerMon(index)->GetMaxHealth()))
        {
            cout << "You have " << AshKetchup.GetPotionCount() << " potions.\n";
            cout << "Would you like to use a potion? (Does not consume your turn)\n'Y' for Yes, 'N' for No. ";
            potionChoice = GetPotionCommand();
            if(potionChoice == 'Y')
            {
                // We check the size and health of the monster
                // If monster size is big, GetSize returns true, small returns false
                // Big monsters have a max of 120 health, small monsters have a max of 80 health
                // This became very spaghetti-looking after merging code. We can talk about making it not spaghetti on Monday
                if((AshKetchup.GetPlayerMon(index)->GetHealth() < AshKetchup.GetPlayerMon(index)->GetMaxHealth()))
                {
                    cout << "Using a potion on the current monster. It gained 20 health!\n";
                    AshKetchup.GetPlayerMon(index)->DrinkPotion();
                    AshKetchup.RemovePotion();
                    AshKetchup.GetPlayerMon(index)->PrintMonsterData();
                }
                else
                {
                    cout << "Health is too high, can't use a potion!\n";
                }
            }
        }

        PrintBattleMenu();

        switch(GetBattleCommand())
        {
            case 'W':
            {
                cout << "Waiting...\n";
                break;
            }
            case 'P':
            {
                playerMonAlive = AshKetchup.PlayerMonPhysAtk(index, wildMon);
                cout << "Wild monster health after physical attack: " << wildMon->GetHealth() << endl;
                break;
            }
            case 'S':
            {
                playerMonAlive = AshKetchup.PlayerMonSpAtk(index, wildMon);
                cout << "Wild monster health after special attack: " << wildMon->GetHealth() << endl;
                break;
            }
            case 'R':
            {
                int randomMove = rand() % 4;
                switch(randomMove)
                {
                    case 0:
                        AshKetchup.MovePlayer('W', mapSide);
                        break;
                    case 1:
                        AshKetchup.MovePlayer('A', mapSide);
                        break;
                    case 2:
                        AshKetchup.MovePlayer('D', mapSide);
                        break;
                    case 3:
                        AshKetchup.MovePlayer('S', mapSide);
                        break;
                }
                return;
            }
            case 'C':
            {
                cout << "You attempted to catch a monster.\n";
                monsterCaught = CatchAttempt(wildMon);
                if(monsterCaught)
                {
                    cout << "You succeeded!\n";
                    AshKetchup.AddMonster(wildMon);
                    return;
                }
                else
                {
                    cout << "You failed!\n";
                    break;
                }
            }
        }
        if(wildMon->GetHealth() <= 0)
            return;
        
        // Handles enemy monster's attacks
        int monRandomMove = rand() % 2;
        // Make a temporary pointer to a monster so that damage is passed correctly without
        // the use of setters
        Monster* mon = AshKetchup.GetPlayerMon(index);
        switch(monRandomMove)
        {
            case 0:
                cout << "Wild monster did a physical attack\n";
                wildMon->PhysicalAttack(mon);
                break;
            case 1:
                cout << "Wild monster did a special attack\n";
                wildMon->SpecialAttack(mon);
                break;
        }
        if(mon->GetHealth() <= 0)
        {
            cout << "Your monster is defeated!\n";
            
            AshKetchup.RemoveMonster(index);
            if (AshKetchup.GetMonsterCount() != 0){
                index = ChooseMonster();
                cout << "You chose: \n";
                AshKetchup.PrintMonData(index);
            }
            else {
                cout << "All player's monsters are defeated. GAME OVER \n";
                return;
            }
            
        }
    cout << "Your monster has " << mon->GetHealth() << " health remaining.\n\n";
    } while(AshKetchup.GetMonsterCount() > 0);
}

int Map::ChooseMonster()
{
    cout << "Choose your monster.\n";
    AshKetchup.PrintMonList();
    int input;
    cout << "Enter your monster choice: ";
    cin >> input;
    while(!((input >= 0) && (input < AshKetchup.GetMonsterCount())))
    {
        cout << "Try again. " << endl;
        cin >> input;
    }
    return (input);
}

bool Map::CatchAttempt(const Monster* wildMonster)
{
    bool isCaught = false;
    // Store the monster's health and max health in doubles to get percentages
    double monsterHealth = wildMonster->GetHealth();
    double monsterMaxHealth = wildMonster->GetMaxHealth();
    // Use this for getting the proper capture chance
    double healthPercent = monsterHealth / monsterMaxHealth;

    //cout << "Health percent is %" << healthPercent * 100 << '\n';
    int tempCaught = rand();

    if(healthPercent == 1)
    {
        //cout << "Catch chance is 1%\n";
        if((tempCaught % 100) == 50)
            isCaught = true;
    }
    else if((healthPercent <= .99) && (healthPercent >= .90))
    {
        //cout << "Catch chance is 25%\n";
        if((tempCaught % 20) == 10)
            isCaught = true;
    }
    else if((healthPercent <= .90) && (healthPercent >= .25))
    {
        //cout << "Catch chance is 33%\n";
        if((tempCaught % 3) == 0)
            isCaught = true;
    }
    else if((healthPercent <= .25) && (healthPercent >= .10))
    {
        //cout << "Catch chance is 66%\n";
        if((tempCaught % 3) != 0)
            isCaught = true;
    }
    else if((healthPercent <= .10) && (healthPercent > 0))
    {
        //cout << "Catch chance is 100%\n";
        isCaught = true;
    }

    return isCaught;
}

int Map::GetPlayerCoinCount() const
{
    return AshKetchup.GetCoinCount();
}

void PrintBattleMenu()
{
    cout << "'W' for wait.\n";
    cout << "'P' to use a Physical Attack.\n";
    cout << "'S' to use a Special Attack.\n";
    cout << "'R' to run from the current battle.\n";
    cout << "'C' to try and capture the wild monster.\n";
}

void PrintMoveMenu()
{
    cout << "'W' to move Up.\n";
    cout << "'A' to move Left.\n";
    cout << "'S' to move Down.\n";
    cout << "'D' to move Right.\n";
}

char GetPotionCommand(){
    char command = GetChar();
    while (!LegalPotion(command)){//if the input is illegal, ask for user input again
        cout << endl
             << "Illegal selection, please try again." << endl;
        PrintBattleMenu();
        command = GetChar();
    }
    return command;
}

//returns a menu command as a char
char GetBattleCommand(){
    char command = GetChar();

    while (!LegalBattle(command)){//if the input is illegal, ask for user input again
        cout << endl
             << "Illegal selection, please try again." << endl;
        
        PrintBattleMenu();
        command = GetChar();
    }
    return command;
}

char GetMoveCommand(){
    char command = GetChar();

    while (!LegalMove(command)){//if the input is illegal, ask for user input again
        cout << endl
             << "Illegal selection, please try again." << endl;
        PrintMoveMenu();
        command = GetChar();
    }
    return command;
}

//ask for user input for a menu command
char GetChar(){
    char selection;
    cout << "Type your selection, followed by <Enter> ";
    cin >> selection;
    selection = toupper(selection);
    cin.get();
    return selection;
}

char LegalPotion(char c)
{
    return ((c == 'Y') || (c == 'N'));
}

char LegalBattle(char c){
    return ((c == 'W') || (c == 'P') || (c == 'S') || (c == 'R') || (c == 'C'));
}

char LegalMove(char c)
{
    return ((c == 'W') || (c == 'A') || (c == 'S') || (c == 'D'));
}