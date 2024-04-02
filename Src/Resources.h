#pragma once

struct Resources
{
    Resources(long int food, long int water, long int wood, long int population) :
    food      (food),
    water     (water),
    wood      (wood),
    population(population)
    { }

    long int food;
    long int water;
    long int wood;
    long int population;
};
