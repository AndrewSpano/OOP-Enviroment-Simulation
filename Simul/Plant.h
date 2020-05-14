#ifndef __PLANT__
#define __PLANT__

#include <iostream>
#include <cstdlib>

#include "Point.h"

using namespace std;

class Plant {

  protected:
    const string name;
    Point* coordinates;
    const char token;
    const uint breedingProb;
    const uint illnessProb;
    int life;
    const int lifeFactor;
    const uint max_life;
    uint number_of_places_it_can_grow;
    char* places_it_can_grow;
    bool canBreed;                      // a variable used in the breeding process of plants, so that no newborn plants can breed

  private:
    static uint total_plants;

  public:
    Plant(const string n, const Point& p, const char c, const uint breedP, const uint illP, const uint l, const uint lF, const uint ml) :
    name(n), token(c), breedingProb(breedP), illnessProb(illP), life(l), lifeFactor(lF), max_life(ml), canBreed(false)
    {
      coordinates = new Point(p);
      total_plants++;
      // cout << "A Plant has been created!" << endl;
    }

    virtual ~Plant(void)
    {
      delete coordinates;
      total_plants--;
      // cout << "Plant has been destructed" << endl;
    }

    static uint get_total_plants(void) { return total_plants; }

    char get_token(void) const { return token; }

    void setBreed(void) { canBreed = true; }

    bool isDead(void) { return life <= 0; }

    virtual void Grow(void) = 0;
    virtual Plant* Breed(const Point& p) = 0;
    virtual uint getSize(void) = 0;
    virtual void LoseLife(const uint& damage) = 0;

    bool can_be_placed(const char& tok) const
    {
      for (int i = 0; i < number_of_places_it_can_grow; i++)
        if (tok == places_it_can_grow[i])
          return true;
      return false;
    }

    bool can_breed(void)
    {
      uint my_rand = rand() % 100;
      return (my_rand > breedingProb) && canBreed;
    }                                         // LATER WRITE: return rand() % 100 < breedingProb, and check if works

};

#endif
