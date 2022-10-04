//definitions for classes Monster, FireMoster, 
//GrassMonster, and WaterMonster
#include<cstdlib>            
#include<ctime> 
#include "monster.h"


//***************************MONSTER IMPLEMENTATION****************************

Monster::Monster(){
        int sizeM = (rand() % 2);   //randomize number to detemine the size,
                                //health, physical and special damage
    
    switch(sizeM){
        case 0:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        case 1:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
    }
    
    
    x_coord = 0;
    y_coord = 0;
    number = 0;
    strcpy(name, "");
}
Monster::Monster(int num){
    int sizeM = (rand() % 2);   //randomize number to detemine the size,
                                //health, physical and special damage
    
    switch(sizeM){
        case 0:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        case 1:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
    }
    
    
    x_coord = 0;
    y_coord = 0;
    number = num;
    strcpy(name, "");
}

Monster::Monster(int x, int y, int num){
    int sizeM = (rand() % 2);   //randomize number to detemine the size,
                                //health, physical and special damage
    
    switch(sizeM){
        case 0:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        case 1:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
    }

    x_coord = x;
    y_coord = y;
    number = num;
    strcpy(name,"");
}

Monster::~Monster(){};

	
int Monster::GetMaxHealth() const
{
    return maxHealth;
}

bool Monster::GetSize() const
{
    return isBig;
}

Monster::Monster(const Monster& m, const bool sizeIn){
    
    switch(sizeIn){
        case 0:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
        case 1:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        
    }
    x_coord = m.x_coord;
    y_coord = m.y_coord;
    strcpy(name, m.name);
}
//*************************GRASSMONSTER IMPLEMENTATION*************************


GrassMonster::GrassMonster(int num) : Monster(num){
    strcpy(type, "Grass");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*

    strcat(name, size);
    strcat(name, type);
    strcat(name, index);
}

GrassMonster::GrassMonster(int x, int y, int num) : Monster(x, y, num){
    strcpy(type, "Grass");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);
}




GrassMonster::~GrassMonster(){
}

// Copy constructor for adding monster to the list
GrassMonster::GrassMonster(const GrassMonster& g, const bool sizeIn){

    //cout << "Grass copy constructor called, size is " << sizeIn << '\n';
    switch(sizeIn){
        case 0:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
        case 1:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        
    }

    strcpy(type, "Grass");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);

    x_coord = g.x_coord;
    y_coord = g.y_coord;
    //strcpy(name, g.name);
}

int GrassMonster::GetDamageP() const{
    return damageP;
}

int GrassMonster::GetDamageS() const{
    return damageS;
}

int GrassMonster::GetHealth() const{
    if (health <= 0){
        return 0;
    }
    else {
        return health;
    }
}

//reduce monster's hp by d
void GrassMonster::Hit(int d){
    health = health - d;
}

//deal 20 or 5 damage to the attacked monster
//damage depends on the size of the attacking monster
int GrassMonster::PhysicalAttack(Monster*& m){
    m->Hit(damageP);
    return m->GetHealth();
}

const char* GrassMonster::GetType() const{
    return type;
}

int GrassMonster::GetX() const{
    if (x_coord <= 0){
        return 0;
    }
    else {
        return x_coord;
    }
}

int GrassMonster::GetY() const{
    if (y_coord <= 0){
        return 0;
    }
    else {
        return y_coord;
    }
}

int GrassMonster::GetNumber() const{
    return number;
}

//deal 40 or 10 damage to the attacked monster
//damage depends on the size of the attacking monster
int GrassMonster::SpecialAttack(Monster*& m){
    if (strcmp(m->GetType(), "Water") == 0){
        m->Hit(damageS);
    }
    else {
        m->Hit(damageP);
    }

    return m->GetHealth();
}

void GrassMonster::DrinkPotion(){
    // Reduce health based on size until it fits the max health
    health = health + 20;
    while(GetHealth() > GetMaxHealth())
    {
        health--;
    }
}

void GrassMonster::PrintMonsterData(){
    //cout << "printing info\n";
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
}



//*************************FIREMONSTER IMPLEMENTATION**************************


FireMonster::FireMonster(int num) : Monster(num){
    strcpy(type, "Fire");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);
}

FireMonster::FireMonster(int x, int y, int num) : Monster(x, y, num){
    strcpy(type, "Fire");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);
}

FireMonster::~FireMonster(){
}

// Copy constructor for adding monster to the list
FireMonster::FireMonster(const FireMonster& f, const bool sizeIn){

    switch(sizeIn){
        case 0:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
        case 1:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        
    }

    strcpy(type, "Fire");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);

    x_coord = f.x_coord;
    y_coord = f.y_coord;
}

int FireMonster::GetDamageP() const{
    return damageP;
}

int FireMonster::GetDamageS() const{
    return damageS;
}

int FireMonster::GetHealth() const{
    if (health <= 0){
        return 0;
    }
    else {
        return health;
    }
}

const char* FireMonster::GetType() const{
    return type;
}

int FireMonster::GetX() const{
    if (x_coord <= 0){
        return 0;
    }
    else {
        return x_coord;
    }
}

int FireMonster::GetY() const{
    if (y_coord <= 0){
        return 0;
    }
    else {
        return y_coord;
    }
}

int FireMonster::GetNumber() const{
    return number;
}

//reduce monster's hp by d
void FireMonster::Hit(int d){
    health = health - d;
}

//deal 20 or 5 damage to the attacked monster
//damage depends on the size of the attacking monster
int FireMonster::PhysicalAttack(Monster*& m){
    m->Hit(damageP);
    return m->GetHealth();
}

//deal 40 or 10 damage to the attacked monster
//damage depends on the size of the attacking monster
int FireMonster::SpecialAttack(Monster*& m){
    if (strcmp(m->GetType(), "Grass") == 0){
        m->Hit(damageS);
    }
    else {
        m->Hit(damageP);
    }

    return m->GetHealth();
}

void FireMonster::DrinkPotion(){
    // Reduce health based on size until it fits the max health
    health = health + 20;
    while(GetHealth() > GetMaxHealth())
    {
        health--;
    }
}

void FireMonster::PrintMonsterData(){
    //cout << "printing info\n";
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
}


//*************************WATERMONSTER IMPLEMENTATION*************************


WaterMonster::WaterMonster(int num) : Monster(num){
    strcpy(type, "Water");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);
}

WaterMonster::WaterMonster(int x, int y, int num) : Monster(x, y, num){
    strcpy(type, "Water");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);
}

WaterMonster::~WaterMonster(){
}

// Copy constructor for adding monster to the list
WaterMonster::WaterMonster(const WaterMonster& w, const bool sizeIn){

    //cout << "Water copy constructor called, size is " << sizeIn << '\n';
    switch(sizeIn){
        case 0:
        {
            isBig = false;
            health = 80;
            maxHealth = 80;
            damageP = 5;
            damageS = 10;
            break;
        }
        case 1:
        {
            isBig = true;
            health = 120;
            maxHealth = 120;
            damageP = 20;
            damageS = 40;
            break;
        }
        
    }

    strcpy(type, "Water");

    char size[6];
    if (isBig){
        strcpy(size, "Big");
    }
    else {
        strcpy(size, "Small");
    }

    char index[2];
    sprintf(index, "%d", number);   //convert int to char*
    strcat(name, size);
    strcat(name, type);
    strcat(name, index);

    x_coord = w.x_coord;
    y_coord = w.y_coord;
    //strcpy(name, w.name);
}

int WaterMonster::GetDamageP() const{
    return damageP;
}

int WaterMonster::GetDamageS() const{
    return damageS;
}

int WaterMonster::GetHealth() const{
    if (health <= 0){
        return 0;
    }
    else {
        return health;
    }
}

const char* WaterMonster::GetType() const{
    return type;
}

int WaterMonster::GetX() const{
    if (x_coord <= 0){
        return 0;
    }
    else {
        return x_coord;
    }
}

int WaterMonster::GetY() const{
    if (y_coord <= 0){
        return 0;
    }
    else {
        return y_coord;
    }
}

int WaterMonster::GetNumber() const{
    return number;
}

//reduce monster's hp by d
void WaterMonster::Hit(int d){
    health = health - d;
}

//deal 20 or 5 damage to the attacked monster
//damage depends on the size of the attacking monster
int WaterMonster::PhysicalAttack(Monster*& m){
    m->Hit(damageP);
    return m->GetHealth();
}

//deal 40 or 10 damage to the attacked monster
//damage depends on the size of the attacking monster
int WaterMonster::SpecialAttack(Monster*& m){
    if (strcmp(m->GetType(), "Fire") == 0){
        m->Hit(damageS);
    }
    else {
        m->Hit(damageP);
    }

    return m->GetHealth();
}

void WaterMonster::DrinkPotion(){
    // Reduce health based on size until it fits the max health
    health = health + 20;
    while(GetHealth() > GetMaxHealth())
    {
        health--;
    }
}

void WaterMonster::PrintMonsterData(){   
    cout << "Name: " << name << endl;
    cout << "Health: " << GetHealth() << endl;
}