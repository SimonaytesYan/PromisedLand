#pragma once

#include "GameObject.hpp"

struct Resources : GameObject 
{
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

    Resources& operator+=(const Resources& other){
        food            += other.food;
        water           += other.water;
        wood            += other.wood;
        population      += other.population;
        free_population += other.free_population;

        return *this;
    }

    Resources& operator-=(const Resources& other){
        food            -= other.food;
        water           -= other.water;
        wood            -= other.wood;
        population      -= other.population;
        free_population -= other.free_population;

        return *this;
    }

    auto operator<=>(const Resources& other) const
    {
        if (auto compare_result = food <=> other.food; compare_result != 0)
            return compare_result;
        if (auto compare_result = water <=> other.water; compare_result != 0)
            return compare_result;
        if (auto compare_result = wood <=> other.wood; compare_result != 0)
            return compare_result;
        if (auto compare_result = population <=> other.population; compare_result != 0)
            return compare_result;
        return free_population <=> other.free_population;
    }

    long int food;
    long int water;
    long int wood;
    long int population;
    long int free_population;
};

static const Resources kZeroResources  = {0, 0, 0, 0, 0};
static const Resources kStartResources = {100, 100, 100, 0, 0};