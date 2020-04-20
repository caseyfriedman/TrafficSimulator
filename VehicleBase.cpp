#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction)
{
   switch(vehicleType)
   {
      case VehicleType::car: vehicleSize = 2; break;
      case VehicleType::suv: vehicleSize = 3; break;
      case VehicleType::truck: vehicleSize = 4; break;
   }
   
   //call random number generator- work in progress
   double randNum = Random::generateNum();
   //double randNum = 0.5;

   if (randNum < 0.4) //replace with input file values
   {
      turnRight = true;
   }
   else
   {
      turnRight = false;
   }
}

VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      vehicleSize(other.vehicleSize),
      turnRight(other.turnRight)
{}

VehicleBase::~VehicleBase() {}

#endif
