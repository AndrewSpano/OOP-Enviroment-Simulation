#ifndef __TERRAIN__
#define __TERRAIN__

#include "Tile.h"

class Terrain {

  private:
    const uint terrainSize;
    Tile** tiles;

  public:
    Terrain(const uint& tS);
    ~Terrain(void);

    void print_terrain(void) const;
    void print_terrain_with_plants(void) const;
    void print_animals(List* all_animals) const;

    void MapGenerator(void);
    void GenerateRiver(void);
    void GenerateLake(void);
    void GenerateHills(void);
    bool hill_does_not_fit(const uint& random_x, const uint& random_y, const uint& random_size) const;
    void GenerateMeadow(void);

    void PlacePlants(const uint plants[]);
    void PlaceAnimals(const uint animals[], List* all_animals);

    void DailyReset(List* all_animals, const bool& plantsGrow, const bool& animalsGrow, const bool& plantsBreed, const bool& herbBreed, const bool& carnBreed, const bool& hibernationPeriod);

    void AnimalBreeding(List* all_animals);

    void PlantGrowing(void);
    void PlantBreeding(void);
    uint FindFreeTile(const uint& x, const uint& y, Plant* plant);

    void AnimalMovement(List* all_animals);
    void move_random_tiles(Animal* tmp_animal, const uint& random_speed, const uint& current_x, const uint& current_y);
    uint FindTiletoMove(Animal* tmp_animal, const uint& x, const uint& y);

    void AnimalEating(List* all_animals);
};


#endif
