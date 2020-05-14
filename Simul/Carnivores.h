#ifndef __CARNIVORES__
#define __CARNIVORES__

#include "AnimalInfo.h"
#include "Animal.h"

class Carnivores: public Animal {
  protected:
    uint attack;
    uint defence;

  private:
    const char class_token;
    static uint total_carnivores;

  public:
    Carnivores(const string name_, const uint size_, const uint attack_, const uint defence_, const Point& coordinates_, const uint speed_, const bool hibernates_, const char token_);
    virtual ~Carnivores(void);

    static uint get_total_carnivores(void);

    char get_class_token(void);
    uint get_defence(void);
};



class Fox: public Carnivores {
  private:
    static uint total_fox;

  public:
    Fox(const Point& p);
    ~Fox(void);

    void make_grown(void);

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_fox(void);
};



class Wolf: public Carnivores {
  private:
    static uint total_wolf;

  public:
    Wolf(const Point& p);
    ~Wolf(void);

    void make_grown(void);

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_wolf(void);
};



class Bear: public Carnivores {
  private:
    static uint total_bear;

  public:
    Bear(const Point& p);
    ~Bear(void);

    void make_grown(void);

    void Grow(void);
    Animal* Raise(const Point& p);
    void Eat(Tile* tile);

    static uint get_total_bear(void);
};


#endif
