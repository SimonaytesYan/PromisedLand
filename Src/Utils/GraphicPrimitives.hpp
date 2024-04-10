#pragma once

#include "../Constants.hpp"

#if USES_SFML
#include <SFML/Graphics.hpp>
#endif

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

  #if USES_SFML

    Point(const sf::Vector2f sf_point)
      : x (sf_point.x),
        y (sf_point.y) 
    {}

    Point(const sf::Vector2i sf_point)
      : x (sf_point.x),
        y (sf_point.y) 
    {}

    Point(const sf::Vector2u sf_point)
      : x (sf_point.x),
        y (sf_point.y) 
    {}

    operator sf::Vector2f() const
    {
        return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
    }

    operator sf::Vector2i() const
    {
        return sf::Vector2i(static_cast<int>(x), static_cast<int>(y));
    }

    operator sf::Vector2u() const
    {
        return sf::Vector2u(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
    }

  #endif

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


#if USES_SFML
    Color(const sf::Color other) :
    r (other.r),
    g (other.g),
    b (other.b),
    a (other.a)
    { }

    operator sf::Color()
    { return sf::Color(r, g, b, a); }

    operator const sf::Color() const
    { return sf::Color(r, g, b, a); }
#endif
    
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

#if USES_SFML
    // const Color Color::Black        = sf::Color::Black;
    // const Color Color::White        = sf::Color::White;
    // const Color Color::Red          = sf::Color::Red;
    // const Color Color::Green        = sf::Color::Green;
    // const Color Color::Blue         = sf::Color::Blue;
    // const Color Color::Yellow       = sf::Color::Yellow;
    // const Color Color::Magenta      = sf::Color::Magenta;
    // const Color Color::Cyan         = sf::Color::Cyan;
    // const Color Color::Transparent  = sf::Color::Transparent;
#else
    // const Color Color::Black       (0, 0, 0);
    // const Color Color::White       (255, 255, 255);
    // const Color Color::Red         (255, 0, 0);
    // const Color Color::Green       (0, 255, 0);
    // const Color Color::Blue        (0, 0, 255);
    // const Color Color::Yellow      (255, 255, 0);
    // const Color Color::Magenta     (255, 0, 255);
    // const Color Color::Cyan        (0, 255, 255);
    // const Color Color::Transparent (0, 0, 0, 0);
#endif
