#include "Tile.h"


Tile::Tile(void): token('-'), has_plant(false), plant(NULL), numberOfAnimals(0)
{
  animals = new List;
  // cout << "A Tile has been created!\n";
}



Tile::~Tile(void)
{
  if (has_plant)
    delete plant;
  delete animals;
  // cout << "A Tile has been destroyed!\n";
}



void Tile::set_token(const char t)
{
  token = t;
}



void Tile::set_plant(Plant* plantPtr)
{
  has_plant = true;
  plant = plantPtr;
}



void Tile::set_animal(Animal* animalPtr)
{
  numberOfAnimals++;
  animals->insertLast(animalPtr);
}



char Tile::get_token(void) const
{
  return token;
}



char Tile::get_plant_token(void) const { return plant->get_token(); }



bool Tile::hasPlant(void) const { return has_plant; }



Plant* Tile::get_plant(void) const { return plant; }



List* Tile::get_animals(void) const { return animals; }



void Tile::growPlant(void) { plant->Grow(); }



void Tile::AnimalBreeding(List* all_animals, const Point& p)
{
  const uint animals_before_breeding = numberOfAnimals;
  Animal* tmp_animal;
  for (int i = 0; i < animals_before_breeding; i++) {
    tmp_animal = animals->at(i);
    if (tmp_animal->isInHeat() && tmp_animal->isGrown()) {
      Animal* new_animal = tmp_animal->Raise(p);
      set_animal(new_animal);
      all_animals->insertLast(new_animal);
    }
  }
}



Animal* Tile::get_animal_that_can_move(void)
{
  if (numberOfAnimals == 0)
    return NULL;

  Animal* tmp_animal = animals->get_animal_that_can_move();
  if (tmp_animal)
    numberOfAnimals--;

  return tmp_animal;
}



void Tile::AnimalEating(List* all_animals)
{
  Animal* tmp_animal;
  for (int i = 0; i < numberOfAnimals; i++) {
    tmp_animal = animals->at(i);
    if (tmp_animal->IsAlive() && tmp_animal->IsHungry())
      tmp_animal->Eat(this);
  }

  CheckDeadEntities(all_animals);
}



void Tile::CheckDeadEntities(List* all_animals)
{
  if (has_plant) {
    if (plant->isDead()) {
      has_plant = false;
      delete plant;
      plant = NULL;
    }
  }

  int i = 0;

  while (i < numberOfAnimals) {
    if (!animals->at(i)->IsAlive()) {
      animals->remove(i);
      numberOfAnimals--;
    } else {
      i++;
    }
  }
  all_animals->delete_dead_animals();
}



void Tile::print_animals(void) const
{
  if (numberOfAnimals != 0)
    animals->iterateForward();
  else
    cout << "No animals in this tile\n";
}
