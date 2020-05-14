#ifndef __ECOSYSTEM__
#define __ECOSYSTEM__

#include "Terrain.h"
#include "Periods.h"

class Ecosystem {

  private:
    Terrain* terrain;
    string season;
    uint dayOfYear;
    uint growthPeriodPlants;
    uint growthPeriodAnimals;
    uint breedingRepPeriodPlants;
    uint breedingRepPeriodHerb;
    uint breedingRepPeriodCarn;
    List* all_animals;

  public:
    Ecosystem(const uint& Tsize, const uint plants[], const uint animals[]);
    ~Ecosystem(void);

    void PrintSystem(void) const;
    void printPlantStatistics(void) const;
    void printAnimalStatistics(void) const;

    void RunEcosystem(const uint& days);

    void set_season_and_periods(uint& simulation_time);           // == ApplySeason()
    void set_growth_and_breeding_and_hibernation(bool& plantsGrow, bool& animalsGrow, bool& plantsBreed, bool& herbBreed, bool& carnBreed, bool& hibernationPeriod);

};

#endif
