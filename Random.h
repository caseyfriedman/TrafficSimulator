#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>

class Random
{
   private:
      static std::mt19937 rng;

   public:
      inline static void setSeed(int seed){rng.seed(seed);}

     // generate a uniform(0,1) psuedo-random number
     static double generateNum();
};

#endif
