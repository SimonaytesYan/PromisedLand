#pragma once

#include "GameObject.hpp"

struct Resources : GameObject 
{
public:

    Resources() :
    food            (0),
    water           (0),
    wood            (0),
    population      (0),
    free_population (0)
    { }

    Resources(const long int food, const long int water, const long int wood, const long int population, const long int free_population) :
    food            (food),
    water           (water),
    wood            (wood),
    population      (population),
    free_population (free_population)
    { }

    Resources& operator+=(const Resources& other)
    {
        food            += other.food;
        water           += other.water;
        wood            += other.wood;
        population      += other.population;
        free_population += other.free_population;

        return *this;
    }

    Resources& operator-=(const Resources& other)
    {
        food            -= other.food;
        water           -= other.water;
        wood            -= other.wood;
        population      -= other.population;
        free_population -= other.free_population;

        return *this;
    }

    Resources& operator*=(const double value)
    {
        food            *= value;
        water           *= value;
        wood            *= value;
        population      *= value;
        free_population *= value;

        return *this;
    }

    Resources operator-(const Resources& other)
    {
        Resources res = *this;
        res -= other;

        return res;
    }

    Resources operator+(const Resources& other) const 
    {
        Resources res = *this;
        res += other;

        return res;
    }

    Resources operator*(const double value) const 
    {
        Resources res = *this;
        res *= value;

        return res;
    }

    Resources operator-() const 
    {
        return {-food, -water, -wood, -population, -free_population};
    }

    bool operator<(const Resources& other) const
    {
        return food            < other.food       ||
               water           < other.water      ||
               wood            < other.wood       ||
               population      < other.population ||
               free_population < other.free_population;
    }

    static Resources absNegative(Resources to_change)
    {
        Resources result;

        result.food            = absNegative(to_change.food);
        result.water           = absNegative(to_change.water);
        result.wood            = absNegative(to_change.wood);
        result.population      = absNegative(to_change.population);
        result.free_population = absNegative(to_change.free_population);

        return result;
    }

private:

    static long int absNegative(long int other)
    {
        return other < 0 ? (-1 * other) : 0;
    }

public:

    long int food;
    long int water;
    long int wood;
    long int population;
    long int free_population;
};

static const Resources kZeroResources  = {0, 0, 0, 0, 0};
static const Resources kStartResources = {100, 100, 100, 0, 0};