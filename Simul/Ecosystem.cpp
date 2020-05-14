#include "Ecosystem.h"

// UINT == UNSIGNED INT

uint Plant::total_plants = 0;

uint Seedless::total_seedless = 0;
uint Grass::total_grass = 0;
uint Algae::total_algae = 0;

uint Seeded::total_seeded = 0;
uint Maple::total_maple = 0;
uint Oak::total_oak = 0;
uint Pine::total_pine = 0;



uint Animal::total_animals = 0;

uint Herbivores::total_herbivores = 0;
uint Dear::total_dear = 0;
uint Rabbit::total_rabbit = 0;
uint Groundhog::total_groundhog = 0;
uint Salmon::total_salmon = 0;

uint Carnivores::total_carnivores = 0;
uint Fox::total_fox = 0;
uint Wolf::total_wolf = 0;
uint Bear::total_bear = 0;



Ecosystem::Ecosystem(const uint& Tsize, const uint plants[], const uint animals[]) :
dayOfYear(1), season("Winter"), growthPeriodPlants(10), growthPeriodAnimals(30), breedingRepPeriodPlants(0), breedingRepPeriodHerb(18), breedingRepPeriodCarn(10)
{
  terrain = new Terrain(Tsize);
  all_animals = new List;
  terrain->MapGenerator();
  terrain->PlacePlants(plants);
  terrain->print_terrain_with_plants();
  terrain->PlaceAnimals(animals, all_animals);
  cout << "An Ecosystem has been created!\n";
}


Ecosystem::~Ecosystem(void)
{
  delete all_animals;
  delete terrain;
  cout << "An Ecosystem is being destroyed!\n";
}


void Ecosystem::PrintSystem(void) const
{
  uint option;
  cout << "\n\nEnter 0 to proceed\n";
  cout << "Enter 1 to print the day of the Year\n";
  cout << "Enter 2 to print the terrain\n";
  cout << "Enter 3 to print the PlantStatistics\n";
  cout << "Enter 4 to print the AnimalStatistics\n\n";
  cin >> option;
 while (option) {
    switch (option) {
      case 1:
        cout << "\nDay of the Year: " << dayOfYear << endl;
        break;

      case 2:
        terrain->print_terrain_with_plants();
        break;

      case 3:
        printPlantStatistics();
        break;

      case 4:
        printAnimalStatistics();
        break;

      default:
        break;
    }
    cout << "\n\nEnter 0 to proceed\n";
    cout << "Enter 1 to print the day of the Year\n";
    cout << "Enter 2 to print the terrain\n";
    cout << "Enter 3 to print the PlantStatistics\n";
    cout << "Enter 4 to print the AnimalStatistics\n\n";
    cin >> option;
  }
}


void Ecosystem::printPlantStatistics(void) const
{
  cout << "Total Plants: " << Plant::get_total_plants() << "\n\n\n";
  cout << "Total Seedless: " << Seedless::get_total_seedless() << "\n\n";
  cout << "Total Grass: " << Grass::get_total_grass() << endl;
  cout << "Total Algae: " << Algae::get_total_algae() << "\n\n";
  cout << "Total Seeded: " << Seeded::get_total_seeded() << "\n\n";
  cout << "Total Maple: " << Maple::get_total_maple() << endl;
  cout << "Total Oak: " << Oak::get_total_oak() << endl;
  cout << "Total Pine: " << Pine::get_total_pine() << "\n\n\n";
}


void Ecosystem::printAnimalStatistics(void) const
{
  cout << "Total Animals: " << Animal::get_total_animals() << "\n\n\n";
  cout << "Total Herbivores: " << Herbivores::get_total_herbivores() << "\n\n";
  cout << "Total Dear: " << Dear::get_total_dear() << endl;
  cout << "Total Rabbit: " << Rabbit::get_total_rabbit() << endl;
  cout << "Total Groundhog: " << Groundhog::get_total_groundhog() << endl;
  cout << "Total Salmon: " << Salmon::get_total_salmon() << "\n\n";
  cout << "Toal Carnivores: " << Carnivores::get_total_carnivores() << "\n\n";
  cout << "Total Fox: " << Fox::get_total_fox() << endl;
  cout << "Total Wolf: " << Wolf::get_total_wolf() << endl;
  cout << "Total Bear: " << Bear::get_total_bear() << "\n\n\n";
}


void Ecosystem::RunEcosystem(const uint& days)
{
  uint simulation_time = days;
  bool plantsGrow, animalsGrow, plantsBreed, herbBreed, carnBreed, hibernationPeriod;
  set_growth_and_breeding_and_hibernation(plantsGrow, animalsGrow, plantsBreed, herbBreed, carnBreed, hibernationPeriod);

  for (dayOfYear = 1; dayOfYear  < simulation_time; dayOfYear ++) {
    set_season_and_periods(simulation_time);
    set_growth_and_breeding_and_hibernation(plantsGrow, animalsGrow, plantsBreed, herbBreed, carnBreed, hibernationPeriod);
    terrain->DailyReset(all_animals, plantsGrow, animalsGrow, plantsBreed, herbBreed, carnBreed, hibernationPeriod);
    for (int j = 0; j < 24; j++) {
      terrain->AnimalMovement(all_animals);
      terrain->AnimalEating(all_animals);
    }
    if (dayOfYear  == 59 || dayOfYear  == 60 || dayOfYear  == 149 || dayOfYear  == 150 || dayOfYear  == 239 || dayOfYear  == 240 || dayOfYear  == 329 || dayOfYear  == 330)
      PrintSystem();
  }
  terrain->print_terrain_with_plants();
}


void Ecosystem::set_season_and_periods(uint& simulation_time)
{
  if (dayOfYear  == 361) {
    dayOfYear  -= 360;
    simulation_time -=360;
  }
  if (((dayOfYear <= 60 || dayOfYear > 330) && season == "Winter") || ((dayOfYear > 60 && dayOfYear <= 150) && season == "Spring") ||
     ((dayOfYear > 150 && dayOfYear <= 240) && season == "Summer") || ((dayOfYear > 240 && dayOfYear <= 330) && season == "Autumn"))
    return;
  else {
    if (dayOfYear == 61) {
      season = "Spring";
      growthPeriodPlants = SPRING_GROWTH_PLANTS;
      growthPeriodAnimals = SPRING_GROWTH_ANIMALS;
      breedingRepPeriodPlants = SPRING_BREED_PLANTS;
      breedingRepPeriodHerb = SPRING_BREED_HERB;
      breedingRepPeriodCarn = SPRING_BREED_CARN;
    } else if (dayOfYear == 151) {
      season = "Summer";
      growthPeriodPlants = SUMMER_GROWTH_PLANTS;
      growthPeriodAnimals = SUMMER_GROWTH_ANIMALS;
      breedingRepPeriodPlants = SUMMER_BREED_PLANTS;
      breedingRepPeriodHerb = SUMMER_BREED_HERB;
      breedingRepPeriodCarn = SUMMER_BREED_CARN;
    } else if (dayOfYear == 241) {
      season = "Autumn";
      growthPeriodPlants = AUTUMN_GROWTH_PLANTS;
      growthPeriodAnimals = AUTUMN_GROWTH_ANIMALS;
      breedingRepPeriodPlants = AUTUMN_BREED_PLANTS;
      breedingRepPeriodHerb = AUTUMN_BREED_HERB;
      breedingRepPeriodCarn = AUTUMN_BREED_CARN;
    } else if (dayOfYear == 331) {
      season = "Winter";
      growthPeriodPlants = WINTER_GROWTH_PLANTS;
      growthPeriodAnimals = WINTER_GROWTH_ANIMALS;
      breedingRepPeriodPlants = WINTER_BREED_PLANTS;
      breedingRepPeriodHerb = WINTER_BREED_HERB;
      breedingRepPeriodCarn = WINTER_BREED_CARN;
    }
  }
}


void Ecosystem::set_growth_and_breeding_and_hibernation(bool& plantsGrow, bool& animalsGrow, bool& plantsBreed, bool& herbBreed, bool& carnBreed, bool& hibernationPeriod)
{
  plantsGrow = ((growthPeriodPlants) ? (dayOfYear % growthPeriodPlants == 0) : 0);
  animalsGrow = ((growthPeriodAnimals) ? (dayOfYear % growthPeriodAnimals == 0) : 0);
  plantsBreed = ((breedingRepPeriodPlants) ? (dayOfYear % breedingRepPeriodPlants == 0) : 0);
  herbBreed = ((breedingRepPeriodHerb) ? (dayOfYear % breedingRepPeriodHerb == 0) : 0);
  carnBreed = ((breedingRepPeriodCarn) ? (dayOfYear % breedingRepPeriodCarn == 0) : 0);
  hibernationPeriod = (season == "Winter");
}
