#include "Terrain.h"

Terrain::Terrain(const uint& tS): terrainSize(tS)
{
  tiles = new Tile*[terrainSize];
  for (int i = 0; i < terrainSize; i++)
    tiles[i] = new Tile[terrainSize];
  cout << "A Terrain has been constructed!\n";
}


Terrain::~Terrain(void)
{
  for (int i = 0; i < terrainSize; i++)
    delete[] tiles[i];
  delete[] tiles;
  cout << "A Terrain has been destructed!\n";
}


void Terrain::print_terrain(void) const
{
  for (int i = 0; i < terrainSize; i++) {
    for (int j = 0; j < terrainSize; j++)
      cout << tiles[i][j].get_token();
    cout << endl;
  }
}


void Terrain::print_terrain_with_plants(void) const
{
  for (int i = 0; i < terrainSize; i++) {
    for (int j = 0; j < terrainSize; j++)
      if (tiles[i][j].hasPlant())
        cout << tiles[i][j].get_plant_token() << " ";
      else
        cout << tiles[i][j].get_token() << " ";
    cout << endl;
  }
}


void Terrain::print_animals(List* animals) const
{
  // for (int i = 0; i < terrainSize; i++) {
  //   for (int j = 0; j < terrainSize; j++)
  //     tiles[i][j].print_animals();
  //   cout << endl;
  // }
  animals->iterateForward();
}


void Terrain::MapGenerator(void)
{
  GenerateRiver();
  GenerateLake();
  GenerateHills();
  GenerateMeadow();
}

/* while the river is being generated, we make sure that it never reaches the borders of the tiles matrix,
   because if it did it would cut the map in more than 2 parts, which is forbidden by the pronunciation */

void Terrain::GenerateRiver(void)
{
  srand(time(NULL));
  uint pos = rand() % (terrainSize - 10) + 5;                   // choosing a random position from which the river will be generated
  uint devProb;                                                 // probability that the river deviates

  tiles[pos][0].set_token('#');                                 // by default we assume that the river starts somewhere in the 1st column of the tiles matrix

  for (int j = 1; j < terrainSize; j++) {                       // N == terrainSize
    devProb = rand() % 100;

    if (devProb < 30) {                                         // if we enter this if statement, it means the river will deviate in some way

      if (pos == terrainSize - 2) {                             // if true, the river is in the second to last row of the matrix, which means it can only deviate left (up)

        if (devProb < 15) {                                     // 50% chance the river deviates 1 tile left
          tiles[--pos][j-1].set_token('#');
        } else {                                                // 50% chance the river deviates 2 tiles left
          tiles[--pos][j-1].set_token('#');
          tiles[--pos][j-1].set_token('#');
        }

      } else if (pos == terrainSize - 3) {                      // if true, the river can deviate only 3 ways: 1 tile left, 2 tiles left, 1 tile right

        if (devProb < 10) {                                     // 33% chance the river will deviate 1 tile right (down)
          tiles[++pos][j-1].set_token('#');
        } else if (devProb < 20) {                              // 33% chance the river will deviate 1 tile left (up)
          tiles[--pos][j-1].set_token('#');
        } else {                                                // 33% chance the river will deviate 2 tiles left (up)
          tiles[--pos][j-1].set_token('#');
          tiles[--pos][j-1].set_token('#');
        }

      } else if (pos == 1) {                                    // if true, the river is in the second row of the matrix, which means it can only deviate right (down)

        if (devProb < 15) {                                     // 50% chance the river deviates 1 tile right (down)
          tiles[++pos][j-1].set_token('#');
        } else {                                                // 50% chance the river deviates 2 tiles right (down)
          tiles[++pos][j-1].set_token('#');
          tiles[++pos][j-1].set_token('#');
        }

      } else if (pos == 2) {                                    // if true, the river can deviate only 3 ways: 1 tile right, 2 tiles right, 1 tile left

        if (devProb < 10) {                                     // 33% chance the river deviates 1 tile left (up)
          tiles[--pos][j-1].set_token('#');
        } else if (devProb < 20) {                              // 33% chance the river deviates 1 tile right (down)
          tiles[++pos][j-1].set_token('#');
        } else {                                                // 33% chance the river deviates 2 tiles right (down)
          tiles[++pos][j-1].set_token('#');
          tiles[++pos][j-1].set_token('#');
        }

      } else {                                                  // if true, we are inside boundaries, and river can deviate any way we want

          if (devProb < 7) {                                    // 25-ish% chance the river deviates 1 tile left (up)
            tiles[--pos][j-1].set_token('#');
          } else if (devProb < 15) {                            // 25-ish% chance the river deviates 2 tiles left (up)
            tiles[--pos][j-1].set_token('#');
            tiles[--pos][j-1].set_token('#');
          } else if (devProb < 22) {                            // 25-ish% chance the river deviates 1 tile right (down)
            tiles[++pos][j-1].set_token('#');
          } else {                                              // 25-ish% chance the river deviates 2 tiles right (down)
            tiles[++pos][j-1].set_token('#');
            tiles[++pos][j-1].set_token('#');
          }

      }

    }

    tiles[pos][j].set_token('#');
  }
}


void Terrain::GenerateLake(void)
{
  const uint lakeSize = terrainSize / 4;                      // change here the size of the lake

  const uint random_x = rand() % (terrainSize - (lakeSize + 1));
  const uint random_y = rand() % (terrainSize - (lakeSize + 1));
  for (int i = random_x; i <= random_x + lakeSize; i++)
    for (int j = random_y; j <= random_y + lakeSize; j++)
      tiles[i][j].set_token('#');
}


void Terrain::GenerateHills(void)
{
  const uint hills = terrainSize / 5;
  uint random_size, random_x, random_y, count;

  for (int i = 0; i < hills; i++) {
    random_size = rand() % 3 + 2;
    count = 0;                                // count is a variable used to "determine" whether there are any spots left in the map for the hill
    random_x = rand() % (terrainSize - (random_size + 1));
    random_y = rand() % (terrainSize - (random_size + 1));

    while (hill_does_not_fit(random_x, random_y, random_size) && count < terrainSize*terrainSize) {   // MAY CAUSE INFINITE LOOP!!!!!!!!!!!
      random_x = rand() % (terrainSize - (random_size + 1));
      random_y = rand() % (terrainSize - (random_size + 1));
      count++;
    }

    /* if we randomly search terrainSize*terrainSize points in the tiles matrix, chances are
       that we will find a spot for the hill. If we don't, probably there isn't one so we break */

    if (count >= terrainSize*terrainSize)
      break;

    for (int i = random_x; i < random_x + random_size; i++)
      for (int j =  random_y; j < random_y + random_size; j++)
        tiles[i][j].set_token('^');
  }
}


bool Terrain::hill_does_not_fit(const uint& random_x, const uint& random_y, const uint& random_size) const
{
  for (int i = random_x; i < random_x + random_size; i++)
    for (int j =  random_y; j < random_y + random_size; j++)
      if (tiles[i][j].get_token() != '-')
        return true;

  return false;
}


void Terrain::GenerateMeadow(void)
{
  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++)
      if (tiles[i][j].get_token() == '-')
        tiles[i][j].set_token('"');
}


void Terrain::PlacePlants(const uint plants[])
{

  for (int i = 0; i < plants[0]; i++) {                   // place Grass

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].hasPlant() || tiles[x][y].get_token() != '"') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Grass* tmp_grass = new Grass(temp_point);
    tmp_grass->setBreed();
    tiles[x][y].set_plant(tmp_grass);

  }

  for (int i = 0; i < plants[1]; i++) {           // Place Algae

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].hasPlant() || tiles[x][y].get_token() != '#') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place ALgae
      break;

    Point temp_point(x, y);
    Algae* tmp_algae = new Algae(temp_point);
    tmp_algae->setBreed();
    tiles[x][y].set_plant(tmp_algae);

  }

  for (int i = 0; i < plants[2]; i++) {          // place Maples

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].hasPlant() || tiles[x][y].get_token() == '#') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Maple
      break;

    Point temp_point(x, y);
    Maple* tmp_maple = new Maple(temp_point);
    tmp_maple->setBreed();
    tiles[x][y].set_plant(tmp_maple);

  }

  for (int i = 0; i < plants[3]; i++) {          // place Oaks

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].hasPlant() || tiles[x][y].get_token() != '"') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Oaks
      break;

    Point temp_point(x ,y);
    Oak* tmp_oak = new Oak(temp_point);
    tmp_oak->setBreed();
    tiles[x][y].set_plant(tmp_oak);

  }

  for (int i = 0; i < plants[4]; i++) {                                          // place Pines

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].hasPlant() || tiles[x][y].get_token() != '^') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Pines
      break;

    Point temp_point(x, y);
    Pine* tmp_pine = new Pine(temp_point);
    tmp_pine->setBreed();
    tiles[x][y].set_plant(tmp_pine);

  }

}


void Terrain::PlaceAnimals(const uint animals[], List* all_animals)
{
  for (int i = 0; i < animals[0]; i++) {                   // place Dear

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() != '"') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Dear* tmp_dear = new Dear(temp_point);
    tmp_dear->make_grown();                         // Animals are fully grown when placed in simulation
    tiles[x][y].set_animal(tmp_dear);
    all_animals->insertLast(tmp_dear);

  }


  for (int i = 0; i < animals[1]; i++) {                   // place Rabbit

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() != '"') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Rabbit* tmp_rabbit = new Rabbit(temp_point);
    tmp_rabbit->make_grown();                         // Animals are fully grown when placed in simulation
    tiles[x][y].set_animal(tmp_rabbit);
    all_animals->insertLast(tmp_rabbit);

  }


  for (int i = 0; i < animals[2]; i++) {                   // place Groundhog

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() != '"') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Groundhog* tmp_groundhog = new Groundhog(temp_point);
    tmp_groundhog->make_grown();                         // Animals are fully grown when placed in simulation
    tiles[x][y].set_animal(tmp_groundhog);
    all_animals->insertLast(tmp_groundhog);

  }


  for (int i = 0; i < animals[3]; i++) {                   // place Salmon

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() != '#') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Salmon* tmp_salmon = new Salmon(temp_point);
    tmp_salmon->make_grown();
    tiles[x][y].set_animal(tmp_salmon);
    all_animals->insertLast(tmp_salmon);

  }


  for (int i = 0; i < animals[4]; i++) {                   // place Fox

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() != '"') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Fox* tmp_fox = new Fox(temp_point);
    tmp_fox->make_grown();                         // Animals are fully grown when placed in simulation
    tiles[x][y].set_animal(tmp_fox);
    all_animals->insertLast(tmp_fox);

  }


  for (int i = 0; i < animals[5]; i++) {                   // place Wolf

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() == '#') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Wolf* tmp_wolf = new Wolf(temp_point);
    tmp_wolf->make_grown();                         // Animals are fully grown when placed in simulation
    tiles[x][y].set_animal(tmp_wolf);
    all_animals->insertLast(tmp_wolf);

  }


  for (int i = 0; i < animals[6]; i++) {                   // place Bear

    uint count = 0;
    uint x = rand() % terrainSize;
    uint y = rand() % terrainSize;

    while ((tiles[x][y].get_token() != '^') && (count < terrainSize*terrainSize)) {
      x = rand() % terrainSize;
      y = rand() % terrainSize;
      count++;
    }

    if (count == terrainSize*terrainSize)           // if true, after many trials we did not find a suitable tile in the simulation terrain to place Grass
      break;

    Point temp_point(x, y);
    Bear* tmp_bear = new Bear(temp_point);
    tmp_bear->make_grown();                         // Animals are fully grown when placed in simulation
    tiles[x][y].set_animal(tmp_bear);
    all_animals->insertLast(tmp_bear);

  }

}



void Terrain::DailyReset(List* all_animals, const bool& plantsGrow, const bool& animalsGrow, const bool& plantsBreed, const bool& herbBreed, const bool& carnBreed, const bool& hibernationPeriod)
{
  all_animals->set_stats(animalsGrow, herbBreed, carnBreed, hibernationPeriod);
  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++)
      tiles[i][j].CheckDeadEntities(all_animals);

  if (herbBreed || carnBreed)
    AnimalBreeding(all_animals);

  if (plantsGrow)
    PlantGrowing();

  if (plantsBreed)
    PlantBreeding();
}



void Terrain::AnimalBreeding(List* all_animals)
{
  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++) {
      Point tmp_point(i, j);
      tiles[i][j].AnimalBreeding(all_animals, tmp_point);
    }
}



void Terrain::PlantGrowing(void)
{
  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++)
      if (tiles[i][j].hasPlant())
        tiles[i][j].growPlant();
}



void Terrain::PlantBreeding(void)
{
  uint free_tile;
  Plant* tmp_plant;

  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++)
      if (tiles[i][j].hasPlant()) {

        tmp_plant = tiles[i][j].get_plant();
        free_tile = FindFreeTile(i, j, tmp_plant);

        if (tmp_plant->can_breed() && free_tile != 0) {

          if (free_tile == 1) {
            Point tmp_point(i, j - 1);
            Plant* new_plant = tmp_plant->Breed(tmp_point);
            tiles[i][j - 1].set_plant(new_plant);

          } else if (free_tile == 2) {
            Point tmp_point(i, j + 1);
            Plant* new_plant = tmp_plant->Breed(tmp_point);
            tiles[i][j + 1].set_plant(new_plant);

          } else if (free_tile == 3) {
            Point tmp_point(i + 1, j);
            Plant* new_plant = tmp_plant->Breed(tmp_point);
            tiles[i + 1][j].set_plant(new_plant);

          } else {
            Point tmp_point(i - 1, j);
            Plant* new_plant = tmp_plant->Breed(tmp_point);
            tiles[i - 1][j].set_plant(new_plant);
          }

        }
      }

  for (int i = 0; i < terrainSize; i++)           // newborn plants could not breed, but after they are placed we make the able to breed
    for (int j = 0; j < terrainSize; j++)
      if (tiles[i][j].hasPlant())
        tiles[i][j].get_plant()->setBreed();
}


/* FindFreeTile() returns 1 if the plant can be placed left, return 2 if it can be placed right,
   returns 3 if it can be placed down, returns 4 if it can be placed up and 0 if it can't be placed */


uint Terrain::FindFreeTile(const uint& x, const uint& y, Plant* plant)
{
  if ((x > 0) && (x < terrainSize - 1) && (y > 0) && (y < terrainSize - 1)) {

    if (plant->can_be_placed(tiles[x][y - 1].get_token()) && !tiles[x][y - 1].hasPlant()) {
      return 1;
    } else if (plant->can_be_placed(tiles[x][y + 1].get_token()) && !tiles[x][y + 1].hasPlant()) {
      return 2;
    } else if (plant->can_be_placed(tiles[x + 1][y].get_token()) && !tiles[x + 1][y].hasPlant()) {
      return 3;
    } else if (plant->can_be_placed(tiles[x - 1][y].get_token()) && !tiles[x - 1][y].hasPlant()) {
      return 4;
    } else {
      return 0;
    }

  } else if (x == 0 && y == 0) {

    if (plant->can_be_placed(tiles[x][y + 1].get_token()) && !tiles[x][y + 1].hasPlant()) {
      return 2;
    } else if (plant->can_be_placed(tiles[x + 1][y].get_token()) && !tiles[x + 1][y].hasPlant()) {
      return 3;
    } else {
      return 0;
    }

  } else if (x == 0 && y == terrainSize - 1) {

    if (plant->can_be_placed(tiles[x][y - 1].get_token()) && !tiles[x][y - 1].hasPlant()) {
      return 1;
    } else if (plant->can_be_placed(tiles[x + 1][y].get_token()) && !tiles[x + 1][y].hasPlant()) {
      return 3;
    } else {
      return 0;
    }

  } else if (y == 0 && x == terrainSize - 1) {

    if (plant->can_be_placed(tiles[x][y + 1].get_token()) && !tiles[x][y + 1].hasPlant()) {
      return 2;
    } else if (plant->can_be_placed(tiles[x - 1][y].get_token()) && !tiles[x - 1][y].hasPlant()) {
      return 4;
    } else {
      return 0;
    }

  } else if (y == terrainSize - 1 && x == terrainSize - 1) {

    if (plant->can_be_placed(tiles[x][y - 1].get_token()) && !tiles[x][y - 1].hasPlant()) {
      return 1;
    } else if (plant->can_be_placed(tiles[x - 1][y].get_token()) && !tiles[x - 1][y].hasPlant()) {
      return 4;
    } else {
      return 0;
    }

  } else if (x == 0) {

    if (plant->can_be_placed(tiles[x][y - 1].get_token()) && !tiles[x][y - 1].hasPlant()) {
      return 1;
    } else if (plant->can_be_placed(tiles[x][y + 1].get_token()) && !tiles[x][y + 1].hasPlant()) {
      return 2;
    } else if (plant->can_be_placed(tiles[x + 1][y].get_token()) && !tiles[x + 1][y].hasPlant()) {
      return 3;
    } else {
      return 0;
    }

  } else if (x == terrainSize - 1) {

    if (plant->can_be_placed(tiles[x][y - 1].get_token()) && !tiles[x][y - 1].hasPlant()) {
      return 1;
    } else if (plant->can_be_placed(tiles[x][y + 1].get_token()) && !tiles[x][y + 1].hasPlant()) {
      return 2;
    } else if (plant->can_be_placed(tiles[x - 1][y].get_token()) && !tiles[x - 1][y].hasPlant()) {
      return 4;
    } else {
      return 0;
    }

  } else if (y == 0) {

    if (plant->can_be_placed(tiles[x][y + 1].get_token()) && !tiles[x][y + 1].hasPlant()) {
      return 2;
    } else if (plant->can_be_placed(tiles[x + 1][y].get_token()) && !tiles[x + 1][y].hasPlant()) {
      return 3;
    } else if (plant->can_be_placed(tiles[x - 1][y].get_token()) && !tiles[x - 1][y].hasPlant()) {
      return 4;
    } else {
      return 0;
    }

  } else {

    if (plant->can_be_placed(tiles[x][y - 1].get_token()) && !tiles[x][y - 1].hasPlant()) {
      return 1;
    } else if (plant->can_be_placed(tiles[x + 1][y].get_token()) && !tiles[x + 1][y].hasPlant()) {
      return 3;
    } else if (plant->can_be_placed(tiles[x - 1][y].get_token()) && !tiles[x - 1][y].hasPlant()) {
      return 4;
    } else {
      return 0;
    }

  }
}



void Terrain::AnimalMovement(List* all_animals)
{
  Animal* tmp_animal;
  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++)
      while (tmp_animal = tiles[i][j].get_animal_that_can_move()) {
        uint random_speed = rand() % tmp_animal->getSpeed();
        move_random_tiles(tmp_animal, random_speed, i, j);
      }

  all_animals->set_movement();
}



void Terrain::move_random_tiles(Animal* tmp_animal, const uint& random_speed, const uint& current_x, const uint& current_y)
{
  uint x = current_x;
  uint y = current_y;

  for (int i = 0; i < random_speed; i++) {

    uint random_direction = FindTiletoMove(tmp_animal, x, y);
    // Again, 1 == left, 2 == right, 3 == down and 4 == up

    if (random_direction == 0) {
      break;
    } else if (random_direction == 1) {
      y--;
    } else if (random_direction == 2) {
      y++;
    } else if (random_direction == 3) {
      x++;
    } else {
      x--;
    }

  }

  Point tmp_point(x, y);
  tmp_animal->Move(tmp_point);
  tiles[x][y].set_animal(tmp_animal);
}



uint Terrain::FindTiletoMove(Animal* tmp_animal, const uint& x, const uint& y)
{
  uint directions[4];
  uint total_directions_available = 0;

  if ((x > 0) && (x < terrainSize - 1) && (y > 0) && (y < terrainSize - 1)) {

    if (tmp_animal->can_move(tiles[x][y - 1].get_token()))
      directions[total_directions_available++] = 1;

    if (tmp_animal->can_move(tiles[x][y + 1].get_token()))
      directions[total_directions_available++] = 2;

    if (tmp_animal->can_move(tiles[x + 1][y].get_token()))
      directions[total_directions_available++] = 3;

    if (tmp_animal->can_move(tiles[x - 1][y].get_token()))
      directions[total_directions_available++] = 4;


  } else if (x == 0 && y == 0) {

    if (tmp_animal->can_move(tiles[x][y + 1].get_token()))
      directions[total_directions_available++] = 2;

    if (tmp_animal->can_move(tiles[x + 1][y].get_token()))
      directions[total_directions_available++] = 3;

  } else if (x == 0 && y == terrainSize - 1) {

    if (tmp_animal->can_move(tiles[x][y - 1].get_token()))
      directions[total_directions_available++] = 1;

    if (tmp_animal->can_move(tiles[x + 1][y].get_token()))
      directions[total_directions_available++] = 3;

  } else if (y == 0 && x == terrainSize - 1) {

    if (tmp_animal->can_move(tiles[x][y + 1].get_token()))
      directions[total_directions_available++] = 2;

    if (tmp_animal->can_move(tiles[x - 1][y].get_token()))
      directions[total_directions_available++] = 4;


  } else if (y == terrainSize - 1 && x == terrainSize - 1) {

    if (tmp_animal->can_move(tiles[x][y - 1].get_token()))
      directions[total_directions_available++] = 1;

    if (tmp_animal->can_move(tiles[x - 1][y].get_token()))
      directions[total_directions_available++] = 4;

  } else if (x == 0) {

    if (tmp_animal->can_move(tiles[x][y - 1].get_token()))
      directions[total_directions_available++] = 1;

    if (tmp_animal->can_move(tiles[x][y + 1].get_token()))
      directions[total_directions_available++] = 2;

    if (tmp_animal->can_move(tiles[x + 1][y].get_token()))
      directions[total_directions_available++] = 3;

  } else if (x == terrainSize - 1) {

    if (tmp_animal->can_move(tiles[x][y - 1].get_token()))
      directions[total_directions_available++] = 1;

    if (tmp_animal->can_move(tiles[x][y + 1].get_token()))
      directions[total_directions_available++] = 2;

    if (tmp_animal->can_move(tiles[x - 1][y].get_token()))
      directions[total_directions_available++] = 4;

  } else if (y == 0) {

    if (tmp_animal->can_move(tiles[x][y + 1].get_token()))
      directions[total_directions_available++] = 2;

    if (tmp_animal->can_move(tiles[x + 1][y].get_token()))
      directions[total_directions_available++] = 3;

    if (tmp_animal->can_move(tiles[x - 1][y].get_token()))
      directions[total_directions_available++] = 4;

  } else {

    if (tmp_animal->can_move(tiles[x][y - 1].get_token()))
      directions[total_directions_available++] = 1;

    if (tmp_animal->can_move(tiles[x + 1][y].get_token()))
      directions[total_directions_available++] = 3;

    if (tmp_animal->can_move(tiles[x - 1][y].get_token()))
      directions[total_directions_available++] = 4;

  }

  if (total_directions_available == 0)
    return 0;

  uint random_direction = directions[rand() % total_directions_available];
  return random_direction;
}



void Terrain::AnimalEating(List* all_animals)
{
  for (int i = 0; i < terrainSize; i++)
    for (int j = 0; j < terrainSize; j++)
      tiles[i][j].AnimalEating(all_animals);
}
