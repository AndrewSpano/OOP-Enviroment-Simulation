#include <iostream>

using namespace std;

class Player{
  private:
    const string name;

  protected:
    const string type;

  public:
    Player (const string &n)
    {
      name = n;
    }
    virtual ~Player() {}

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player)
    {
      out << type << " player " <<  name;
      return out;
    }
};


 class Greedyplayer : public Player {
  public:
    Greedyplayer(const string& n): Player(n), type("Greedy") {}
    ~Greedyplayer() {}
    const string & getType(void)
    {
      return type;
    }
    Move play(const State &s)
    {
      number_of_heaps = s.getHeaps();
      int max = s.getCoins(0);
      int pos = 0;
      for (int i = 1; i < number_of_heaps; i++)
        if (max < s.getCoins(i)) {
          max = s.getCoins(i);
          pos = i;
        }
      Move move(pos, max, 0, 0)
      return move;
    }

 };
