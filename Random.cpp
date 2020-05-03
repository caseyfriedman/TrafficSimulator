#ifndef __RANDOM_CPP__
#define __RANDOM_CPP__

#include <iostream>
#include <random>
#include "Random.h"

std::mt19937 Random::rng; // Mersenne twister
static std::uniform_real_distribution<double> rand_double(0,1); //use range 0-1 to generate random number

double Random::generateNum()
{
   return rand_double(rng);
}

#endif

