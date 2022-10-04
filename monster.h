//declarations for class Monster and its derived classes
//class Monster has 3 directly derived subclasses:
//FireMonster, GrassMonster, and WaterMonster

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <cstring>
#include <cstdio>   //for sprintf function


using namespace std;

class Monster{
    public:
        virtual void PrintMonsterData()=0;  //print out monster's name and hp

        virtual void Hit(int d)=0;  //reduce monster's hp by d
        //deal phycical attack damage to the attacked monster
        virtual int PhysicalAttack(Monster*& m) =0; 
        //deal special attack damage to the attacked monster
        virtual int SpecialAttack(Monster*& m) =0;

        //monster drink a potion and its health increases by 20 hp
        virtual void DrinkPotion() =0;

        virtual int GetDamageP() const =0;
        virtual int GetDamageS() const =0;
        virtual int GetHealth() const =0;

        virtual const char* GetType() const =0;

        virtual int GetMaxHealth() const;

        virtual int GetX() const =0;
        virtual int GetY() const =0;

        virtual int GetNumber() const =0;

        virtual bool GetSize() const;

        virtual ~Monster();


    protected:
        Monster();
        Monster(const Monster & m, const bool);
        Monster(int num);
        Monster(int x, int y, int num);

        bool isBig; //identify if the monster big or small
        int health;
        int maxHealth;
        int x_coord,
            y_coord;
        int number; //what order the monster was generated on the map
        int damageP,    //physical attack damage
            damageS;    //special attack damage
        char name[30];  //name of the monster <type><size><number>
};

class GrassMonster: public Monster{
    public:
        
        GrassMonster(const GrassMonster& g, const bool);
        GrassMonster(int num);
        GrassMonster(int x, int y, int num);
        void PrintMonsterData();
        ~GrassMonster();

        int GetDamageP() const;
        int GetDamageS() const;

        int GetHealth() const;

        const char* GetType() const;

        int GetX() const;
        int GetY() const;

        int GetNumber() const;

        int PhysicalAttack(Monster*& m);

        int SpecialAttack(Monster*& m);

        void DrinkPotion();

    private:
        void Hit(int d);
        char type[6];
};

class FireMonster: public Monster{
    public:
        FireMonster(int num);
        FireMonster(int x, int y, int num);
        FireMonster(const FireMonster& g, const bool);
        void PrintMonsterData();
        ~FireMonster();

        int GetHealth() const;

        int GetDamageP() const;
        int GetDamageS() const;

        const char* GetType() const;

        int GetX() const;
        int GetY() const;

        int GetNumber() const;

        int PhysicalAttack(Monster*& m);
        int SpecialAttack(Monster*& m);

        void DrinkPotion();

    private:
        void Hit(int d);
        char type[6];
};

class WaterMonster: public Monster{
    public:
        WaterMonster(const WaterMonster& g, const bool);
        WaterMonster(int num);
        WaterMonster(int x, int y, int num);
        void PrintMonsterData();
        ~WaterMonster();

        int GetDamageP() const;
        int GetDamageS() const;

        int GetHealth() const;

        const char* GetType() const;

        int GetX() const;
        int GetY() const;

        int GetNumber() const;

        int PhysicalAttack(Monster*& m);
        int SpecialAttack(Monster*& m);

        void DrinkPotion();

    private:
        void Hit(int d);

        char type[6];
};

#endif