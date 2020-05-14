#include "Animal.h"
#include "Tile.h"

Animal::Animal(const string name_, const uint size_, const Point& coordinates_, const uint speed_, const bool hibernates_, const char token_) :
name(name_),
size(size_),
hungerCount(0),       // when animals are created, by default we assume they are not hungry
eatenFood(0),
isAlive(true),
isHungry(false),
inHeat(false),
speed(speed_),
hibernates(hibernates_),
is_grown(false),
has_moved(false),
inHibernation(false),
token(token_)
{
  coordinates = new Point(coordinates_);
  total_animals++;
  // cout << "A new Animal has been created!\n";
}


Animal::~Animal(void) { delete coordinates; total_animals--; /* cout << "An Animal has been destroyed!\n"; */ }


uint Animal::get_total_animals(void) { return total_animals; }


void Animal::print(void) const
{
  cout << endl;
  cout << "name: " << name << endl;
  cout << "size: " << size << endl;
  cout << "hungerCount: " << hungerCount << endl;
  cout << "eatenFood: " << eatenFood << endl;
  cout << "isAlive: " << isAlive << endl;
  cout << "isHungry: " << isHungry << endl;
  cout << "inHeat: " << inHeat << endl;
  cout << "speed: " << speed << endl;
  cout << "hibernates: " << hibernates << endl;
  cout << "inHibernation: " << inHibernation << endl;
  cout << "token: " << token << endl;
  cout << "coordinates: ";
  coordinates->print();
  cout << "\n\n";
}


uint Animal::getSpeed(void) const { return speed; }


char Animal::get_token(void) const { return token; }


uint Animal::getSize(void) const { return size; }


bool Animal::isGrown(void) const { return is_grown; }


bool Animal::isInHeat(void) const { return inHeat; }


bool Animal::hasMoved(void) const { return has_moved; }


bool Animal::isInHibernation(void) const { return inHibernation; }


bool Animal::IsAlive(void) const { return isAlive; }


bool Animal::IsHungry(void) const { return isHungry; }


bool Animal::can_move(const char& tok) const
{
  for (int i = 0; i < number_of_places_to_move; i++)
    if (places_to_move[i] == tok)
      return true;

  return false;
}


void Animal::set_stats(const bool animalsGrow, const bool herbBreed, const bool carnBreed, const bool hibernationPeriod)
{

  hungerCount++;
  if (hungerCount > 10)
    isAlive = false;

  if (get_class_token() == 'H') {
    if (herbBreed)
      inHeat = true;
    else
      inHeat = false;

    if (hungerCount > 7)
      isHungry = true;

  } else {
    if (carnBreed)
      inHeat = true;
    else
      inHeat = false;

    isHungry = true;
  }


  if (hibernationPeriod && hibernates && !inHibernation)
    Hibernate();

  if (inHibernation && !hibernationPeriod)
    Wake();

  if (animalsGrow && !is_grown && !inHibernation)
    Grow();
}



void Animal::Hibernate(void) { inHibernation = true; }


void Animal::Wake(void) { inHibernation = false; }


void Animal::make_able_to_move(void) { has_moved = false; }


void Animal::kill(void) { isAlive = false; }


void Animal::Move(const Point& p)
{
  // cout << "Animal moves from: ";
  // coordinates->print();
  // cout << ", to: ";
  // p.print();
  // cout << "\n";
  coordinates->setx(p.getx());
  coordinates->sety(p.gety());
  has_moved = true;
}
