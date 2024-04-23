#pragma once

struct Point 
{
public:
    Point()
      : x (0),
        y (0) 
    {}

    Point(const double _x, const double _y)
      : x (_x),
        y (_y) 
    {}

public:
    double x;
    double y;
};

struct Color
{
    Color(const unsigned char r,
          const unsigned char g,
          const unsigned char b,
          const unsigned char a = 255) : 
    r (r),
    g (g),
    b (b),
    a (a)
    { }
    
    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};
