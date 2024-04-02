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

    long int food;
    long int water;
    long int wood;
    long int population;
};

const Resources kStartResources = {0, 0, 0, 0};
