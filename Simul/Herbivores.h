#ifndef __HERBIVORES__
#define __HERBIVORES__

#include "AnimalInfo.h"
#include "Animal.h"

class Herbivores: public Animal {

  protected:
    uint neededFood;
    const uint eatCount;
    const bool canClimb;

  private:
    const char class_token;
    static uint total_herbivores;


  public:
    Herbivores(const string name_, const uint size_, const uint nF, const uint eatCount_, const Point& coordinates_, const uint speed_, const bool hibernates_, const bool can_climb, const char token_);
    virtual ~Herbivores(void);

    static uint get_total_herbivores(void);

    char get_class_token(void);

    uint get_defence(void);

};



class Dear: public Herbivores {
  private:
    static uint total_dear;

  public:
    Dear(const Point& p);
    ~Dear(void);

    void make_grown(void);                // ONLY USED IN PLACE_ANIMALS()

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_dear(void);
};



class Rabbit: public Herbivores {
  private:
    static uint total_rabbit;

  public:
    Rabbit(const Point& p);
    ~Rabbit(void);

    void make_grown(void);                // ONLY USED IN PLACE_ANIMALS()

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_rabbit(void);
};



class Groundhog: public Herbivores {
  private:
    static uint total_groundhog;

  public:
    Groundhog(const Point& p);
    ~Groundhog(void);

    void make_grown(void);                // ONLY USED IN PLACE_ANIMALS()

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_groundhog(void);
};



class Salmon: public Herbivores {
  private:
    static uint total_salmon;

  public:
    Salmon(const Point& p);
    ~Salmon(void);

    void make_grown(void);

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_salmon(void);
};


#endif
