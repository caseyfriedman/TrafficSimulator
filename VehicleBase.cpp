/**

Created by Casey, Mikaela, and Aidan

5/5/20

VehicleBase constructor takes in a type and a direction.

*/

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction dir)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(dir),
      turnRight(false)
{
   //set vehicle size based on vehicle type
   switch(vehicleType)
   {
      case VehicleType::car: vehicleSize = 2; break;
      case VehicleType::suv: vehicleSize = 3; break;
      case VehicleType::truck: vehicleSize = 4; break;
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


