#pragma once

#include <cstdarg>
#include <cstdio>

#include "../Constants.hpp"

#if USES_SFML
#include <SFML/Graphics.hpp>
#endif

void mPrint(FILE* ostream, const char* const fmt, ...);

#define PRINT_ON_ERROR(expr, ostream, err_str, args...)     \
{                                                            \
    if (expr)                                                 \
    {                                                          \
        mPrint(ostream, err_str, args);                         \
    }                                                            \
}

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