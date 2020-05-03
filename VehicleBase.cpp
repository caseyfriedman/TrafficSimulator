#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"
#include "Random.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction)
{
   //set vehicle size based on vehicle type
   switch(vehicleType)
   {
      case VehicleType::car: vehicleSize = 2; break;
      case VehicleType::suv: vehicleSize = 3; break;
      case VehicleType::truck: vehicleSize = 4; break;
   }
   
   //call random number generator
   double randNum = Random::generateNum();

   //determine whether vehicle will turn
   if (randNum < 0.4)
   {
      turnRight = true;
   }
   else
   {
      turnRight = false;
   }
}

VehicleBase::VehicleBase(VehicleType type, Direction direction, Parameters param)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction)
{
   //set vehicle size based on vehicle type
   switch(vehicleType)
   {
      case VehicleType::car: 
           {
              vehicleSize = 2; 
              
              double randNum = Random::generateNum();
              if (randNum < param.get_proportion_right_turn_cars()) 
              {
                 turnRight = true;
              }
              else
              {
                  turnRight = false;
              }
              break;
           }
      case VehicleType::suv:
           {
              vehicleSize = 3;

              double randNum = Random::generateNum();
              if (randNum < param.get_proportion_right_turn_SUVs())
              {
                 turnRight = true;
              }
              else
              {
                  turnRight = false;
              }
              break;
           }
      case VehicleType::truck:
           {
              vehicleSize = 4;

              double randNum = Random::generateNum();
              if (randNum < param.get_proportion_right_turn_trucks())
              {
                 turnRight = true;
              }
              else
              {
                  turnRight = false;
              }
              break;
           }
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
