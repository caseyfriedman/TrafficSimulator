/**

Created by Casey, Mikaela, and Aidan

5/5/20

This header file contains the random number generator object and its methods

Seed must be set using setSeed() at some point.

*/

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
