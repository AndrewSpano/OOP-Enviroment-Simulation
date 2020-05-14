#include "Carnivores.h"
#include "Tile.h"

Carnivores::Carnivores(const string name_, const uint size_, const uint attack_, const uint defence_, const Point& coordinates_, const uint speed_, const bool hibernates_, const char token_) :
Animal(name_, size_, coordinates_, speed_, hibernates_, token_),
attack(attack_),
defence(defence_),
class_token('C')
{
  total_carnivores++;
  // cout << "A Carnivore Animal has been created!\n";
}


Carnivores::~Carnivores(void) { total_carnivores--; /* cout << "A Carnivore is being destructed\n"; */ }


uint Carnivores::get_total_carnivores(void) { return total_carnivores; }


char Carnivores::get_class_token(void) { return class_token; }


uint Carnivores::get_defence(void) { return defence; }






///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////     FOX     //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Fox::Fox(const Point& p) :
Carnivores(FOX_NAME, YOUNG_FOX_SIZE, YOUNG_FOX_ATTACK, YOUNG_FOX_DEFENCE, p, YOUNG_FOX_SPEED, FOX_HIBERNATES, FOX_TOKEN)
{
  number_of_places_to_move = 3;
  places_to_move = new char[3];
  places_to_move[0] = '"';
  places_to_move[1] = '^';
  places_to_move[2] = '#';

  total_fox++;
  // cout << "A Fox has been created!\n";
}


Fox::~Fox(void) { delete[] places_to_move; total_fox--; /* cout << "A Fox has died\n"; */ }


void Fox::make_grown(void)            // USED IN PLACE_ANIMALS()
{
  size = GROWN_FOX_SIZE;
  speed = GROWN_FOX_SPEED;
  attack = GROWN_FOX_ATTACK;
  defence = GROWN_FOX_DEFENCE;
  is_grown = true;
}


void Fox::Grow(void)
{
  if (size < GROWN_FOX_SIZE)
    size += FOX_GROWTH;

  if (speed < GROWN_FOX_SPEED)
    speed += FOX_GROWTH;

  if (attack < GROWN_FOX_ATTACK)
    attack += FOX_GROWTH;

  if (defence < GROWN_FOX_DEFENCE)
    defence += FOX_GROWTH;

  if ((size == GROWN_FOX_SIZE) && (speed == GROWN_FOX_SPEED) && (attack == GROWN_FOX_ATTACK) && (defence == GROWN_FOX_DEFENCE))
    is_grown = true;
}


Animal* Fox::Raise(const Point& p)
{
  Fox* tmp_fox = new Fox(p);
  return tmp_fox;
}


void Fox::Eat(Tile* tile)
{
  List* animals_in_tile = tile->get_animals();
  uint total_animals_in_tile = animals_in_tile->getSize();

  Animal* tmp_animal;

  for (int i = 0; i < total_animals_in_tile; i++) {
    tmp_animal = animals_in_tile->at(i);

    if (tmp_animal->IsAlive() && (tmp_animal->get_token() != 'B' || (tmp_animal->get_token() == 'B' && !tmp_animal->isGrown()
    && attack > tmp_animal->get_defence())) && tmp_animal->get_token() != 'S') {

    // FOX LOSES TO A GROWN BEAR, SO NO POINT IN FIGHTING IT + IT DOES NOT EAT SALMON

      if (tmp_animal->get_class_token() == 'H') {           // the animal we got is a Herbivore, see if we can eat it
        if ((size >= tmp_animal->getSize()) && (speed > tmp_animal->getSpeed())) {
          tmp_animal->kill();
          hungerCount = 0;
          isHungry = false;
          return;                     // the Animal ate, now we return
        }
      } else if (hungerCount > 8) {                     // the animal we got is a Carnivore, see if we can eat it
        if ((size > tmp_animal->getSize()) || (size == tmp_animal->getSize() && attack > tmp_animal->get_defence()) && (this != tmp_animal)) {
          tmp_animal->kill();
          hungerCount = 0;
          isHungry = false;
          return;                     // the Animal ate, now we return
        }
      }

    }
  }
}


uint Fox::get_total_fox(void) { return total_fox; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////     WOLF     //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Wolf::Wolf(const Point& p) :
Carnivores(WOLF_NAME, YOUNG_WOLF_SIZE, YOUNG_WOLF_ATTACK, YOUNG_WOLF_DEFENCE, p, YOUNG_WOLF_SPEED, WOLF_HIBERNATES, WOLF_TOKEN)
{
  number_of_places_to_move = 3;
  places_to_move = new char[3];
  places_to_move[0] = '"';
  places_to_move[1] = '^';
  places_to_move[2] = '#';

  total_wolf++;
  // cout << "A Wolf has been created!\n";
}


Wolf::~Wolf(void) { delete[] places_to_move; total_wolf--; /* cout << "A Wolf has died\n"; */ }


void Wolf::make_grown(void)           // USED IN PLACE_ANIMALS()
{
  size = GROWN_WOLF_SIZE;
  speed = GROWN_WOLF_SPEED;
  attack = GROWN_WOLF_ATTACK;
  defence = GROWN_WOLF_DEFENCE;
  is_grown = true;
}


void Wolf::Grow(void)
{
  if (size < GROWN_WOLF_SIZE)
    size += WOLF_SIZE_GROWTH;

  if (speed < GROWN_WOLF_SPEED)
    speed += WOLF_GROWTH;

  if (attack < GROWN_WOLF_ATTACK)
    attack += WOLF_GROWTH;

  if (defence < GROWN_WOLF_DEFENCE)
    defence += WOLF_GROWTH;

  if ((size == GROWN_WOLF_SIZE) && (speed == GROWN_WOLF_SPEED) && (attack == GROWN_WOLF_ATTACK) && (defence == GROWN_WOLF_DEFENCE))
    is_grown = true;
}


Animal* Wolf::Raise(const Point& p)
{
  Wolf* tmp_wolf = new Wolf(p);
  return tmp_wolf;
}


void Wolf::Eat(Tile* tile)
{
  List* animals_in_tile = tile->get_animals();
  uint total_animals_in_tile = animals_in_tile->getSize();

  Animal* tmp_animal;

  for (int i = 0; i < total_animals_in_tile; i++) {
    tmp_animal = animals_in_tile->at(i);

    if (tmp_animal->IsAlive() && (tmp_animal->get_token() != 'B' || (tmp_animal->get_token() == 'B' && !tmp_animal->isGrown()
    && attack > tmp_animal->get_defence())) && tmp_animal->get_token() != 'S') {

    // WOLF LOSES TO A GROWN BEAR, SO NO POINT IN FIGHTING IT + IT DOES NOT EAT SALMON

      if (tmp_animal->get_class_token() == 'H') {           // the animal we got is a Herbivore, see if we can eat it
        if ((size >= tmp_animal->getSize()) && (speed > tmp_animal->getSpeed())) {
          tmp_animal->kill();
          hungerCount = 0;
          isHungry = false;
          return;                     // the Animal ate, now we return
        }
      } else if (hungerCount > 8) {                     // the animal we got is a Carnivore, see if we can eat it
        if ((size > tmp_animal->getSize()) || (size == tmp_animal->getSize() && attack > tmp_animal->get_defence()) && (this != tmp_animal)) {
          tmp_animal->kill();
          hungerCount = 0;
          isHungry = false;
          return;                     // the Animal ate, now we return
        }
      }

    }
  }
}


uint Wolf::get_total_wolf(void) { return total_wolf; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////      BEAR      /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Bear::Bear(const Point& p) :
Carnivores(BEAR_NAME, YOUNG_BEAR_SIZE, YOUNG_BEAR_ATTACK, YOUNG_BEAR_DEFENCE, p, YOUNG_BEAR_SPEED, BEAR_HIBERNATES, BEAR_TOKEN)
{
  number_of_places_to_move = 3;
  places_to_move = new char[3];
  places_to_move[0] = '"';
  places_to_move[1] = '^';
  places_to_move[2] = '#';

  total_bear++;
  // cout << "A Bear has been created!\n";
}


Bear::~Bear(void) { delete[] places_to_move; total_bear--; /* cout << "A Bear has died\n"; */ }


void Bear::make_grown(void)           // USED IN PLACE_ANIMALS()
{
  size = GROWN_BEAR_SIZE;
  speed = GROWN_BEAR_SPEED;
  attack = GROWN_BEAR_ATTACK;
  defence = GROWN_BEAR_DEFENCE;
  is_grown = true;
}


void Bear::Grow(void)
{
  if (size < GROWN_BEAR_SIZE)
    size += BEAR_GROWTH;
  if (size > GROWN_BEAR_SIZE)
    size = GROWN_BEAR_SIZE;

  if (speed < GROWN_BEAR_SPEED)
    speed += BEAR_GROWTH;

  if (attack < GROWN_BEAR_ATTACK)
    attack += BEAR_GROWTH;

  if (defence < GROWN_BEAR_DEFENCE)
    defence += BEAR_GROWTH;

  if ((size == GROWN_BEAR_SIZE) && (speed == GROWN_BEAR_SPEED) && (attack == GROWN_BEAR_ATTACK) && (defence == GROWN_BEAR_DEFENCE))
    is_grown = true;
}


Animal* Bear::Raise(const Point& p)
{
  Bear* tmp_bear = new Bear(p);
  return tmp_bear;
}


void Bear::Eat(Tile* tile)
{
  List* animals_in_tile = tile->get_animals();
  uint total_animals_in_tile = animals_in_tile->getSize();

  Animal* tmp_animal;

  for (int i = 0; i < total_animals_in_tile; i++) {

    tmp_animal = animals_in_tile->at(i);
    if (is_grown) {
      if (tmp_animal->IsAlive() && (tmp_animal->get_token() != 'B' || (tmp_animal->get_token() == 'B' && !tmp_animal->isGrown())) && (this != tmp_animal)) {  // BEAR DOES NOT EAT GROWN BEAR
            tmp_animal->kill();
            hungerCount = 0;
            isHungry = false;
            return;                     // the Animal ate, now we return
        }
    } else {
      if (attack > tmp_animal->get_defence() && (tmp_animal->get_token() != 'B' || (tmp_animal->get_token() == 'B' && !tmp_animal->isGrown())) && (this != tmp_animal)) {
        tmp_animal->kill();
        hungerCount = 0;
        isHungry = false;
        return;
      }
    }
  }
}


uint Bear::get_total_bear(void) { return total_bear; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
