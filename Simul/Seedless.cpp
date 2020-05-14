#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Seedless.h"

using namespace std;

Seedless::Seedless(const string n, const Point& p, const char c, const uint breedP, const uint illP, const uint l, const uint lF, const uint ml) :
Plant(n, p, c, breedP, illP, l, lF, ml)
{
  total_seedless++;
  // cout << "A Seedless Plant has been created!\n";
}


Seedless::~Seedless(void) { total_seedless--; /* cout << "A Seedless plant will die\n"; */ }


uint Seedless::get_total_seedless(void) { return total_seedless; }


void Seedless::LoseLife(const uint& damage) { life -= damage; }


void Seedless::Grow(void)
{
  srand(time(NULL));
  uint random = rand() % 100;
  if (random < illnessProb)
    life -= lifeFactor;
  else
    life += lifeFactor;
}


uint Seedless::getSize(void) { cout << "THIS FUNCTION SHOULD HAVE NEVER BEEN CALLED\n"; return 69; }



///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////      GRASS      //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Grass::Grass(const Point& p) :
Seedless(GRASS_NAME, p, GRASS_TOKEN, GRASS_BREEDING_PROB, GRASS_ILLNESS_PROB, GRASS_LIFE, GRASS_LIFE_FACTOR, GRASS_MAX_LIFE)
{
  number_of_places_it_can_grow = 1;
  places_it_can_grow = new char;
  places_it_can_grow[0] = '"';

  total_grass++;
  // cout << "A new Grass was created!\n";
}


Grass::~Grass(void)
{
  delete places_it_can_grow;
  total_grass--;
  // cout << "A Grass will be destroyed!\n";
}


Plant* Grass::Breed(const Point& p)
{
  Grass* tmp_grass = new Grass(p);
  return tmp_grass;
}


uint Grass::get_total_grass(void) { return total_grass; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////      ALGAE      //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Algae::Algae(const Point& p) :
Seedless(ALGAE_NAME, p, ALGAE_TOKEN, ALGAE_BREEDING_PROB, ALGAE_ILLNESS_PROB, ALGAE_LIFE, ALGAE_LIFE_FACTOR, ALGAE_MAX_LIFE)
{
  number_of_places_it_can_grow = 1;
  places_it_can_grow = new char;
  places_it_can_grow[0] = '#';

  total_algae++;
  // cout << "A new Algae was created!\n";
}


Algae::~Algae(void)
{
  delete places_it_can_grow;
  total_algae--;
  // cout << "An Algae will be destroyed!\n";
}


Plant* Algae::Breed(const Point& p)
{
  Algae* tmp_algae = new Algae(p);
  return tmp_algae;
}


uint Algae::get_total_algae(void) { return total_algae; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
