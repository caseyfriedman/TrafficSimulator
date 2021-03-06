/**

Created by Casey, Mikaela, and Aidan

5/5/20

Section constructor takes in a VehicleBase pointer. 
Sections store Vehicle pointers and compose a lane. 

*/

#ifndef __SECTION_H__
#define __SECTION_H__

#include "VehicleBase.h"
#include <iostream>
class Section
{

private:
    bool         intersection;
    static int   numOfSecs;
    VehicleBase* vehiclePtr;
public:
    Section();
    Section(VehicleBase* vehicle);
    ~Section();

    void setIntersection()
    {
        intersection = true;
    }

    inline void setVehicle(VehicleBase* obj)
    {
        vehiclePtr = obj;
    }

    inline bool isOccupied()
    {
        return (vehiclePtr != nullptr);
    }
    inline bool isIntersection()
    {
        return this->intersection;
    }

    inline VehicleBase* getVehicle()
    {
        return vehiclePtr;
    }

    inline int getNumOfSecs()
    {
        return numOfSecs;
    }
};

#endif
