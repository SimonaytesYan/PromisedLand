#pragma once

#include "GameObject.hpp"

struct Resources : GameObject 
{
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

    long int food;
    long int water;
    long int wood;
    long int population;
    long int free_population;
};

const Resources kStartResources = {0, 0, 0, 0, 0};