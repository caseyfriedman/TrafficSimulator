
#include "Section.h"


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


