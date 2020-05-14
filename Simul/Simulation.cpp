#include <iostream>
#include <cstdlib>

#include "Ecosystem.h"

using namespace std;

int main(int argc, char* argv[])
{
  uint terrainSize, plants[5], animals[7], days;

  cout << "Give the size of the Terrain\n";
  cin >> terrainSize;

  cout << "Give the number of Grass, Algae, Maple, Oat and Pine\n";
  cin >> plants[0] >> plants[1] >> plants[2] >> plants[3] >> plants[4];

  cout << "Give the number of Dear, Rabbit, Groundhog, Salmon, Fox, Wolf and Bear\n";
  cin >> animals[0] >> animals[1] >> animals[2] >> animals[3] >> animals[4] >> animals[5] >> animals[6];

  Ecosystem yourMOM(terrainSize, plants, animals);

  cout << "Give the number of days you want the simulate the Ecosystem: ";
  cin >> days;

  yourMOM.RunEcosystem(days);

  return 0;
}
