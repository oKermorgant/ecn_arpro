#ifndef RAND_UTIL_H
#define RAND_UTIL_H

#include <tuple>

int randint(int max);

std::tuple<uint, uint> twoDifferentRandoms(int max);

double randBetween(double min, double max);

#endif // RAND_UTIL_H
