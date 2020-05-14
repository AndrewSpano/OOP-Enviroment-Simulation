#ifndef __SEEDED__
#define __SEEDED__

#include "Plant.h"
#include "PlantInfo.h"

// In Seeded Plants we assume that life = seeds + foliage

class Seeded: public Plant {
  private:
    static uint total_seeded;

  protected:
    int size;
    int foliage;
    int seeds;

  public:
    Seeded(const string n, const Point& p, const char c, const uint breedP, const uint illP, const uint l, const uint lF, const uint ml, const int sz, const int fol, const int see);
    virtual ~Seeded(void);

    static uint get_total_seeded(void);

    void LoseLife(const uint& damage);
    void Grow(void);
    uint getSize(void);
};


class Maple: public Seeded {
  private:
    static uint total_maple;

  public:
    Maple(const Point& p);
    ~Maple(void);

    Plant* Breed(const Point& p);

    static uint get_total_maple(void);
};


class Oak: public Seeded {
  private:
    static uint total_oak;

  public:
    Oak(const Point& p);
    ~Oak(void);

    Plant* Breed(const Point& p);

    static uint get_total_oak(void);
};


class Pine: public Seeded {
  private:
    static uint total_pine;

  public:
    Pine(const Point& p);
    ~Pine(void);

    Plant* Breed(const Point& p);

    static uint get_total_pine(void);
};

#endif
