#pragma once

typedef unsigned long long Bitmask;

const Bitmask kMaxBitmask = (1ULL << 64) - 1; 

inline bool getBit(const Bitmask mask, const unsigned char bit_number)
{
    return (mask & (1LL >> bit_number)) << bit_number;
}
