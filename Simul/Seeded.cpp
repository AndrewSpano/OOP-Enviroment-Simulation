#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Seeded.h"

using namespace std;

Seeded::Seeded(const string n, const Point& p, const char c, const uint breedP, const uint illP, const uint l, const uint lF, const uint ml, const int sz, const int fol, const int see) :
Plant(n, p, c, breedP, illP, l, lF, ml), size(sz), foliage(fol), seeds(see)
{
  total_seeded++;
  // cout << "A Seeded Plant has been created!\n";
}


Seeded::~Seeded(void) { total_seeded--; /* cout << "A Seeded plant will die\n"; */ }


uint Seeded::get_total_seeded(void) { return total_seeded; }


void Seeded::LoseLife(const uint& damage)
{
  if (seeds > 0 && seeds >= damage) {
    seeds -= damage;
  } else if (seeds > 0) {
    uint difference = damage - seeds;
    seeds = 0;
    foliage -= difference;
  } else {
    foliage -= damage;
  }

  life -= damage;
}


void Seeded::Grow(void)
{
  srand(time(NULL));
  uint random = rand() % 100;
  if (random < illnessProb) {
    foliage -= lifeFactor;
    if (foliage < 0)
      foliage = 0;

    size--;
    seeds -= 2*lifeFactor;
    if (seeds < 0)
      seeds = 0;
  } else {
    foliage += lifeFactor;
    size++;
    seeds += 2*lifeFactor;
  }
  life = foliage + seeds;
}


uint Seeded::getSize(void) { return size; }



///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////      MAPLE      //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Maple::Maple(const Point& p) :
Seeded(MAPLE_NAME, p, MAPLE_TOKEN, MAPLE_BREEDING_PROB, MAPLE_ILLNESS_PROB, MAPLE_FOLIAGE + MAPLE_SEEDS, MAPLE_LIFE_FACTOR, MAPLE_MAX_LIFE, MAPLE_SIZE, MAPLE_FOLIAGE, MAPLE_SEEDS)
{
  number_of_places_it_can_grow = 2;
  places_it_can_grow = new char[2];
  places_it_can_grow[0] = '^';
  places_it_can_grow[1] = '"';

  total_maple++;
  // cout << "A Maple has been created!\n";
}

Maple::~Maple(void) { delete[] places_it_can_grow; total_maple--; /* cout << "A Maple has been destroyed\n"; */ }

Plant* Maple::Breed(const Point& p)
{
  Maple* tmp_maple = new Maple(p);
  return tmp_maple;
}

uint Maple::get_total_maple(void) { return total_maple; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////      OAK      /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Oak::Oak(const Point& p) :
Seeded(OAK_NAME, p, OAK_TOKEN, OAK_BREEDING_PROB, OAK_ILLNESS_PROB, OAK_FOLIAGE + OAK_SEEDS, OAK_LIFE_FACTOR, OAK_MAX_LIFE, OAK_SIZE, OAK_FOLIAGE, OAK_SEEDS)
{
  number_of_places_it_can_grow = 1;
  places_it_can_grow = new char;
  places_it_can_grow[0] = '"';

  total_oak++;
  // cout << "An Oak has been created!\n";
}

Oak::~Oak(void) { delete places_it_can_grow; total_oak--; /* cout << "An oat has been destructed\n"; */ }

Plant* Oak::Breed(const Point& p)
{
  Oak* tmp_oak = new Oak(p);
  return tmp_oak;
}

uint Oak::get_total_oak(void) { return total_oak; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////      PINE      //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Pine::Pine(const Point& p) :
Seeded(PINE_NAME, p, PINE_TOKEN, PINE_BREEDPING_PROB, PINE_ILLNESS_PROB, PINE_FOLIAGE + PINE_SEEDS, PINE_LIFE_FACTOR, PINE_MAX_LIFE, PINE_SIZE, PINE_FOLIAGE, PINE_SEEDS)
{
  number_of_places_it_can_grow = 2;
  places_it_can_grow = new char[2];
  places_it_can_grow[0] = '^';
  places_it_can_grow[1] = '"';

  total_pine++;
  // cout << "A Pine has been created!\n";
}

Pine::~Pine(void) { delete[] places_it_can_grow; total_pine--; /* cout << "A Pine will be destroyed\n"; */ }

Plant* Pine::Breed(const Point& p)
{
  Pine* tmp_pine = new Pine(p);
  return tmp_pine;
}

uint Pine::get_total_pine(void) { return total_pine; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
