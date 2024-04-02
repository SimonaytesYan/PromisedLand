#pragma once

#include <cstdarg>
#include <cstdio>

void mPrint(FILE* ostream, const char* const fmt, ...);

#define PRINT_ON_ERROR(expr, ostream, err_str, args...)     \
{                                                            \
    if (expr)                                                 \
    {                                                          \
        mPrint(ostream, err_str, args);                         \
    }                                                            \
}
