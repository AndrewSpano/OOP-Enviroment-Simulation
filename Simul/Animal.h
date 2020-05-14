#ifndef __ANIMAL__
#define __ANIMAL__

#include <iostream>
#include <cstdlib>
#include <ctime>

class Tile;

#include "Point.h"


using namespace std;

class Animal {

  protected:
    const string name;
    uint size;
    uint hungerCount;
    uint eatenFood;
    Point* coordinates;
    bool isAlive;
    bool isHungry;
    bool inHeat;
    uint speed;
    const bool hibernates;
    bool inHibernation;
    bool is_grown;
    const char token;
    int number_of_places_to_move;
    char* places_to_move;
    bool has_moved;                 // a variable used in AnimalMovement() to make sure we don't move the same animal twice

  private:
    static uint total_animals;

  public:
    Animal(const string name_, const uint size_, const Point& coordinates_, const uint speed_, const bool hibernates_, const char token_);
    virtual ~Animal(void);


    static uint get_total_animals(void);

    void print() const;

    uint getSpeed(void) const;
    char get_token(void) const;
    uint getSize(void) const;
    bool isGrown(void) const;
    bool isInHeat(void) const;
    bool hasMoved(void) const;
    bool isInHibernation(void) const;
    bool IsAlive(void) const;
    bool IsHungry(void) const;

    bool can_move(const char& tok) const;

    void set_stats(const bool animalsGrow, const bool herbBreed, const bool carnBreed, const bool hibernationPeriod);

    void Hibernate(void);
    void Wake(void);
    void make_able_to_move(void);
    void kill(void);

    void Move(const Point& p);

    virtual char get_class_token(void) = 0;
    virtual uint get_defence(void) = 0;
    virtual Animal* Raise(const Point& p) = 0;
    virtual void Eat(Tile* tile) = 0;
    virtual void Grow(void) = 0;

};

#endif
