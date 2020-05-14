#include "Herbivores.h"
#include "Tile.h"

Herbivores::Herbivores(const string name_, const uint size_, const uint nF, const uint eatCount_, const Point& coordinates_, const uint speed_, const bool hibernates_, const bool can_climb, const char token_) :
Animal(name_, size_, coordinates_, speed_, hibernates_, token_),
neededFood(nF),
eatCount(eatCount_),
canClimb(can_climb),
class_token('H')
{
  total_herbivores++;
  // cout << "A Herbivore Animal has been created!\n";
}


Herbivores::~Herbivores(void) { total_herbivores--; /* cout << "A Herbivore is being destructed\n"; */ }


uint Herbivores::get_total_herbivores(void) { return total_herbivores; }


char Herbivores::get_class_token(void) { return class_token; }


uint Herbivores::get_defence(void) { return 0; }





///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////      DEAR      //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Dear::Dear(const Point& p) :
Herbivores(DEAR_NAME, YOUNG_DEAR_SIZE, YOUNG_DEAR_NEEDED_FOOD, DEAR_EAT_COUNT, p, YOUNG_DEAR_SPEED, DEAR_HIBERNATES, DEAR_CAN_CLIMB, DEAR_TOKEN)
{
  number_of_places_to_move = 3;
  places_to_move = new char[3];
  places_to_move[0] = '^';
  places_to_move[1] = '"';
  places_to_move[2] = '#';

  total_dear++;
  // cout << "A Dear has been created!\n";
}


Dear::~Dear(void) { delete[] places_to_move; total_dear--; /* cout << "A Dear has died\n"; */ }


void Dear::make_grown(void)                // ONLY USED IN PLACE_ANIMALS()
{
  size = GROWN_DEAR_SIZE;
  neededFood = GROWN_DEAR_NEEDED_FOOD;
  speed = GROWN_DEAR_SPEED;
  is_grown = true;
}


void Dear::Grow(void)
{
  if (size < GROWN_DEAR_SIZE)
    size += DEAR_SIZE_GROWTH;

  if (speed < GROWN_DEAR_SPEED)
    speed += DEAR_GROWTH;

  if (neededFood < GROWN_DEAR_NEEDED_FOOD)
    neededFood += DEAR_GROWTH;

  if ((size == GROWN_DEAR_SIZE) && (speed == GROWN_DEAR_SPEED) && (neededFood == GROWN_DEAR_NEEDED_FOOD))
    is_grown = true;
}


Animal* Dear::Raise(const Point& p)
{
  Dear* tmp_dear = new Dear(p);
  return tmp_dear;
}


void Dear::Eat(Tile* tile)
{
  if (!tile->hasPlant())
    return;

  Plant* tmp_plant = tile->get_plant();
  char tok = tmp_plant->get_token();

  if (!tmp_plant->isDead()) {
    if (tok == 'G' || tok == 'A') {
      tmp_plant->LoseLife(eatCount);
      eatenFood += eatCount;
    } else {
      if (size + 4 > tmp_plant->getSize()) {
        tmp_plant->LoseLife(eatCount);
        eatenFood += eatCount;
      }
    }
  }

  if (eatenFood >= neededFood) {
    eatenFood = 0;
    hungerCount = 0;
    isHungry = false;
  }
}


uint Dear::get_total_dear(void) { return total_dear; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////      RABBIT      /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(const Point& p) :
Herbivores(RABBIT_NAME, YOUNG_RABBIT_SIZE, YOUNG_RABBIT_NEEDED_FOOD, RABBIT_EAT_COUNT, p, YOUNG_RABBIT_SPEED, RABBIT_HIBERNATES, RABBIT_CAN_CLIMB, RABBIT_TOKEN)
{
  number_of_places_to_move = 2;
  places_to_move = new char[2];
  places_to_move[0] = '"';
  places_to_move[1] = '#';

  total_rabbit++;
  // cout << "A Rabbit has been created!\n";
}


Rabbit::~Rabbit(void) { delete[] places_to_move; total_rabbit--; /* cout << "A Rabbit has died\n"; */ }


void Rabbit::make_grown(void)                // ONLY USED IN PLACE_ANIMALS()
{
  size = GROWN_RABBIT_SIZE;
  neededFood = GROWN_RABBIT_NEEDED_FOOD;
  speed = GROWN_RABBIT_SPEED;
  is_grown = true;
}


void Rabbit::Grow(void)
{
  if (size < GROWN_RABBIT_SIZE)
    size += RABBIT_SIZE_GROWTH;

  if (speed < GROWN_RABBIT_SPEED)
    speed += RABBIT_GROWTH;

  if (neededFood < GROWN_RABBIT_NEEDED_FOOD)
    neededFood += RABBIT_GROWTH;

  if ((size == GROWN_RABBIT_SIZE) && (speed == GROWN_RABBIT_SPEED) && (neededFood == GROWN_RABBIT_NEEDED_FOOD))
    is_grown = true;
}


Animal* Rabbit::Raise(const Point& p)
{
  Rabbit* tmp_rabbit = new Rabbit(p);
  return tmp_rabbit;
}


void Rabbit::Eat(Tile* tile)
{
  if (!tile->hasPlant())
    return;

  Plant* tmp_plant = tile->get_plant();
  char tok = tmp_plant->get_token();

  if (!tmp_plant->isDead()) {
    if (tok == 'G') {
      tmp_plant->LoseLife(eatCount);
      eatenFood += eatCount;
    } else if (tok == 'M' || tok == 'O' || tok == 'P') {
      if (size >= tmp_plant->getSize()) {
        tmp_plant->LoseLife(eatCount);
        eatenFood += eatCount;
      }
    }
  }

  if (eatenFood >= neededFood) {
    eatenFood = 0;
    hungerCount = 0;
    isHungry = false;
  }

}


uint Rabbit::get_total_rabbit(void) { return total_rabbit; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////      GROUNDHOG      ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Groundhog::Groundhog(const Point& p) :
Herbivores(GROUNDHOG_NAME, YOUNG_GROUNDHOG_SIZE, YOUNG_GROUNDHOG_NEEDED_FOOD, GROUNDHOG_EAT_COUNT, p, YOUNG_GROUNDHOG_SPEED, GROUNDHOG_HIBERNATES, GROUNDHOG_CAN_CLIMB, GROUNDHOG_TOKEN)
{
  number_of_places_to_move = 2;
  places_to_move = new char[2];
  places_to_move[0] = '^';
  places_to_move[1] = '"';

  total_groundhog++;
  // cout << "A Groundhog has been created!\n";
}


Groundhog::~Groundhog(void) { delete[] places_to_move; total_groundhog--; /* cout << "A Groundhog has died\n"; */ }


void Groundhog::make_grown(void)           // ONLY USED IN PLACE_ANIMALS()
{
  size = GROWN_GROUNDHOG_SIZE;
  neededFood = GROWN_GROUNDHOG_NEEDED_FOOD;
  speed = GROWN_GROUNDHOG_SPEED;
  is_grown = true;
}


void Groundhog::Grow(void)
{
  if (size < GROWN_GROUNDHOG_SIZE)
    size += GROUNDHOG_GROWTH;

  if (speed < GROWN_GROUNDHOG_SPEED)
    speed += GROUNDHOG_GROWTH;

  if (neededFood < GROWN_GROUNDHOG_NEEDED_FOOD)
    neededFood += GROUNDHOG_GROWTH;

  if ((size == GROWN_GROUNDHOG_SIZE) && (speed == GROWN_GROUNDHOG_SPEED) && (neededFood == GROWN_GROUNDHOG_NEEDED_FOOD))
    is_grown = true;
}


Animal* Groundhog::Raise(const Point& p)
{
  Groundhog* tmp_groundhog = new Groundhog(p);
  return tmp_groundhog;
}


void Groundhog::Eat(Tile* tile)
{
  if (!tile->hasPlant())
    return;

  Plant* tmp_plant = tile->get_plant();
  char tok = tmp_plant->get_token();

  if (!tmp_plant->isDead()) {
    if (tok == 'G') {
      tmp_plant->LoseLife(eatCount);
      eatenFood += eatCount;
    } else if (tok == 'M' || tok == 'O' || tok == 'P') {
      if ( (size >= tmp_plant->getSize()) || (is_grown && canClimb && (3*size >= tmp_plant->getSize())) ) {
        tmp_plant->LoseLife(eatCount);
        eatenFood += eatCount;
      }
    }
  }

  if (eatenFood >= neededFood) {
    eatenFood = 0;
    hungerCount = 0;
    isHungry = false;
  }

}


uint Groundhog::get_total_groundhog(void) { return total_groundhog; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////      SALMON      ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Salmon::Salmon(const Point& p) :
Herbivores(SALMON_NAME, SALMON_SIZE, SALMON_NEEDED_FOOD, SALMON_EAT_COUNT, p, SALMON_SPEED, SALMON_HIBERNATES, SALMON_CAN_CLIMB, SALMON_TOKEN)
{
  number_of_places_to_move = 1;
  places_to_move = new char;
  places_to_move[0] = '#';

  total_salmon++;
  // cout << "A Salmon has been created!\n";
}


Salmon::~Salmon(void) { delete places_to_move; total_salmon--; /* cout << "A Salmon has died\n"; */ }


void Salmon::make_grown(void) { is_grown = true; }


void Salmon::Grow(void) { is_grown = true; }


Animal* Salmon::Raise(const Point& p)
{
  Salmon* tmp_salmon = new Salmon(p);
  return tmp_salmon;
}


void Salmon::Eat(Tile* tile)
{
  if (!tile->hasPlant())
    return;

  Plant* tmp_plant = tile->get_plant();
  tmp_plant->LoseLife(eatCount);
  eatenFood += eatCount;

  if (eatenFood >= neededFood) {
    eatenFood = 0;
    hungerCount = 0;
    isHungry = false;
  }

}


uint Salmon::get_total_salmon(void) { return total_salmon; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
