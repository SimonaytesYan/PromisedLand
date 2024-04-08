#include "Utils.hpp"

void mPrint(FILE* ostream, const char* const fmt, ...) 
{
    va_list args;
    va_start(args, fmt);

    vfprintf(ostream, fmt, args);

    va_end(args);
}