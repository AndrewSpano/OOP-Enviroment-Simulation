#ifndef __SEEDLESS__
#define __SEEDLESS__

#include "Plant.h"
#include "PlantInfo.h"

class Seedless: public Plant {
  private:
    static uint total_seedless;

  public:
    Seedless(const string n, const Point& p, const char c, const uint breedP, const uint illP, const uint l, const uint lF, const uint ml);
    virtual ~Seedless(void);

    static uint get_total_seedless(void);

    void LoseLife(const uint& damage);
    void Grow(void);
    uint getSize(void);
};


class Grass: public Seedless {

  private:
    static uint total_grass;

  public:
    Grass(const Point& p);
    ~Grass(void);

    Plant* Breed(const Point& p);

    static uint get_total_grass(void);
};


class Algae: public Seedless {

  private:
    static uint total_algae;

  public:
    Algae(const Point& p);
    ~Algae(void);

    Plant* Breed(const Point& p);

    static uint get_total_algae(void);
};


#endif
