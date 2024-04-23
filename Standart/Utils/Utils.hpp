#pragma once

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

bool bernoulliTrial(const double p);

size_t getRandFromInterval(const size_t left, const size_t right);

void mPrint(FILE* ostream, const char* const fmt, ...);

#define PRINT_ON_ERROR(expr, ostream, err_str, args...)     \
{                                                            \
    if (expr)                                                 \
    {                                                          \
        mPrint(ostream, err_str, args);                         \
    }                                                            \
}
