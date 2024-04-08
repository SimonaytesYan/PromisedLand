#pragma once

struct Resources
{
    Resources(long int food, long int water, long int wood, long int population) :
    food      (food),
    water     (water),
    wood      (wood),
    population(population)
    { }

    Resources& operator+=(const Resources& other){
        food       += other.food;
        water      += other.water;
        wood       += other.wood;
        population += other.population;

        return *this;
    }

    bool isValid()
    { return food >= 0 && water >= 0 && wood >= 0 && population >= 0; }

    long int food;
    long int water;
    long int wood;
    long int population;
};

const Resources kStartResources = {0, 0, 100, 0};
