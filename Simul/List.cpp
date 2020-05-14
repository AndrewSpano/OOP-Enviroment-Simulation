#include "List.h"

List::List(void): size(0), head(NULL), tail(NULL)
{
  // cout << "A List has been created!\n";
}


List::~List(void)
{
  list_destroy();
  // cout << "A List has been destroyed!\n";
}


bool List::isEmpty(void) const
{
  return size == 0;
}


bool List::isFull(void) const
{
  return size == MAX_SIZE;
}


uint List::getSize(void) const
{
  return size;
}


void List::subError()
{
  cout << "ERROR: Subscript out of range.\n";
  exit(EXIT_FAILURE);
}


Animal* List::at(const size_t position)
{
    NodePtr temp = head;
    if (position < 0 || size <= position) {
      cout << "\n\nCall from List::at()\n";
      cout << "position = " << position << "\nsize = " << size << "\n";
      subError();
    } else
        for (size_t i = 0; i < position; i++)
          temp = temp->next;

    return temp->animal;
}


// Animal* List::operator[](const size_t position)
// {
//   return at(position);
// }


void List::insertFront(Animal* tmp)
{
  head = new node(tmp, head, NULL);
  if (!tail)                            // list was empty
    tail = head;
  else                                  // list was not empty
    head->next->prev = head;

  size++;
}


void List::insertLast(Animal* tmp)
{
  tail = new node(tmp, NULL, tail);
  if (!head)                            // list was empty
    head = tail;
  else                                  // list was not empty
    tail->prev->next = tail;
  size++;
}


Animal* List::remove(const size_t n)
{
  NodePtr temp = head;
  if (n < 0 || size <= n) {
    cout << "\n\nCall from List::remove()\n";
    cout << "n = " << n << "\nsize = " << size << "\n";
    subError();
  } else
      for (size_t i = 0; i < n; i++)
        temp = temp->next;

  Animal* animal_tmp = temp->animal;
  if (size == 1) {
    head = tail = NULL;
  } else  if (n == 0) {
    head = head->next;
    head->prev = NULL;
  } else if (n == size - 1) {
    tail = tail->prev;
    tail->next = NULL;
  } else {
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
  }

  delete temp;
  size--;
  return animal_tmp;
}


void List::list_destroy(void)
{
  for (int i = 0; i < size; i++)
    if (at(i) != NULL)
      delete at(i);
  
  while (size)
    remove(0);
  head = tail = NULL;
}


void List::iterateForward(void)
{
  NodePtr tmp = head;
  while (tmp) {
    tmp->animal->print();
    tmp = tmp->next;
  }
}


void List::iterateBackward(void)
{
  NodePtr tmp = tail;
  while (tmp) {
    tmp->animal->print();
    tmp = tmp->prev;
  }
}


Animal* List::get_animal_that_can_move(void)
{
  if (size == 0) {
    cout << "\n\nCall from List::get_animal_that_has_not_moved)\n";
    cout << "size = " << size << "\n";
    subError();
  }

  uint pos = 0;
  NodePtr temp = head;

  while (temp) {
    if (!temp->animal->hasMoved() && !temp->animal->isInHibernation())
      return remove(pos);
    temp = temp->next;
    pos++;
  }

  return NULL;                      // no animals that hadn't moved were found
}


void List::set_movement(void)
{
  NodePtr temp = head;
  while (temp) {
    temp->animal->make_able_to_move();
    temp = temp->next;
  }
}


void List::delete_dead_animals(void)
{
  if (size == 0)
    return;
  while (!head->animal->IsAlive()) {
    delete remove(0);
    if (head == NULL)
      return;
  }

  NodePtr temp = head;
  uint pos = 1;
  while (temp->next) {
    if (!temp->next->animal->IsAlive()) {
      delete remove(pos);
    } else {
      temp = temp->next;
      pos++;
    }
  }

}


void List::set_stats(const bool animalsGrow, const bool herbBreed, const bool carnBreed, const bool hibernationPeriod)
{
  NodePtr tmp = head;
  while (tmp) {
    tmp->animal->set_stats(animalsGrow, herbBreed, carnBreed, hibernationPeriod);
    tmp = tmp->next;
  }
}
