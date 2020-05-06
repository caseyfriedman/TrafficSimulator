/**

Created by Casey, Mikaela, and Aidan

5/5/20

This file contains the random number generator object and its methods.

It contains a static method that generates a random number.

*/


#include "Random.h"

std::mt19937 Random::rng; // Mersenne twister
static std::uniform_real_distribution<double> rand_double(0,1); //use range 0-1 to generate random number

//generates and returns a random number between 0 and 1
double Random::generateNum()
{
   return rand_double(rng);
}


