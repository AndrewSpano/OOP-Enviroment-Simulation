#ifndef __TILE__
#define __TILE__

#include "Seeded.h"
#include "Seedless.h"
#include "List.h"
#include "Herbivores.h"
#include "Carnivores.h"

class Tile {

  private:
    char token;
    bool has_plant;
    Plant* plant;
    int numberOfAnimals;
    List* animals;

  public:
    Tile(void);
    ~Tile(void);


    void set_token(const char t);
    void set_plant(Plant* plantPtr);
    void set_animal(Animal* animalPtr);

    char get_token(void) const;
    char get_plant_token(void) const;
    bool hasPlant(void) const;
    Plant* get_plant(void) const;
    List* get_animals(void) const;

    void growPlant(void);
    void BreedPlant(void);

    void AnimalBreeding(List* all_animals, const Point& p);

    Animal* get_animal_that_can_move(void);

    void AnimalEating(List* all_animals);
    void CheckDeadEntities(List* all_animals);

    void print_animals(void) const;

};

#endif
