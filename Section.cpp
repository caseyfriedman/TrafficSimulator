/**

Created by Casey, Mikaela, and Aidan

5/5/20

Section constructor takes in a VehicleBase pointer and holds the pointer in a member variable.
All Sections are defaulted to not be intersections, and intersections must be set.

*/

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


