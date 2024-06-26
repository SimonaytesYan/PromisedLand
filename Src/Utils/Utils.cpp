#include "Utils.hpp"

void mPrint(FILE* ostream, const char* const fmt, ...) 
{
    va_list args;
    va_start(args, fmt);

    vfprintf(ostream, fmt, args);

    va_end(args);
}

bool bernoulliTrial(const double p)
{
    const double value = ((double)rand() / (double)RAND_MAX);
    return value < p;
}

size_t getRandFromInterval(const size_t left, const size_t right)
{
    return (rand() % (right - left)) + left;
}