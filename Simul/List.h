#ifndef __LIST__
#define __LIST__

#define MAX_SIZE 10

#include "Animal.h"

using namespace std;

typedef struct node *NodePtr;

struct node {
  Animal* animal;
  NodePtr next;
  NodePtr prev;

  node(Animal* elementPtr, NodePtr next_node, NodePtr prev_node): animal(elementPtr), next(next_node), prev(prev_node)
  { /* cout << "A node has been constructed!\n"; */ }

  ~node(void) { /* cout << "A node has been destructed!\n"; */ }
};

class List {

  private:
    uint size;
    NodePtr head;
    NodePtr tail;
    void subError();

  public:
    List(void);
    ~List(void);
    bool isEmpty(void) const;
    bool isFull(void) const;
    uint getSize(void) const;

    // accessors
    Animal* at(const size_t position);
    // Animal* operator[](const size_t position);

    // mutators
    void insertFront(Animal* tmp);
    void insertLast(Animal* tmp);
    Animal* remove(const size_t n);
    void list_destroy(void);

    void iterateForward(void);
    void iterateBackward(void);

    Animal* get_animal_that_can_move(void);
    void set_movement(void);

    void delete_dead_animals(void);

    void set_stats(const bool animalsGrow, const bool herbBreed, const bool carnBreed, const bool hibernationPeriod);

};


#endif
