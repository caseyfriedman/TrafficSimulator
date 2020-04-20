#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>

class Random
{
   public:
      static std::mt19937 rng;

   public:
      Random();
      Random(int seed);
      ~Random();

     // generate a uniform(0,1) psuedo-random number
     static double generateNum();
};

#endif
