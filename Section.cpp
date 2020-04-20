#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"
#include "VehicleBase.h"
#include <iostream>

int Section::numOfSecs = 0;

Section::Section(VehicleBase* vehicle)
    : vehiclePtr(vehicle),
      intersection(false)  //default to all normal sections
{
   numOfSecs++;
}

Section::Section()
    : vehiclePtr(nullptr),
      intersection(false)  //default to all normal sections
{
   numOfSecs++;
}

Section::~Section() {}

#endif
