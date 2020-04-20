#ifndef __RANDOM_CPP__
#define __RANDOM_CPP__

#include <iostream>
#include <random>
#include "Random.h"

std::mt19937 Random::rng; // Mersenne twister

Random::Random()
{
   //static std::mt19937 rng; // Mersenne twister
   //static std::uniform_real_distribution<double> rand_double(0,1);
   
   rng.seed(391);
   // double num = rand_double(rng);
}
  
Random::Random(int seed)
{
   rng.seed(seed);
}

Random::~Random(){};

double Random::generateNum()
{
   static std::uniform_real_distribution<double> rand_double(0,1);

   return rand_double(rng);
}

#endif

