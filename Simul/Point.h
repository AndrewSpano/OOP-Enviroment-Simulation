#ifndef __POINT__
#define __POINT__

typedef unsigned int uint;

class Point {     // TRY MAKING A NAME SPACE LATER

  private:
    uint x;
    uint y;

  public:
    Point(uint _x, uint _y): x(_x), y(_y) { }         // default constructor
    Point(const Point& a): x(a.x), y(a.y) { }         // copy constructor
    ~Point() { }                                      // destructor

    uint getx(void) const { return x; }               // accessors
    uint gety(void) const { return y; }

    void setx(uint _x) { x = _x; }
    void sety(uint _y) { y = _y; }

    void print(void) const { std::cout << "(" << x << ", " << y << ")"; }
};

#endif
