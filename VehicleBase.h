#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

#include "Parameters.h"

// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
      int         vehicleSize;
      bool        turnRight;   
 
    public:
       VehicleBase(VehicleType type, Direction originalDirection);
       VehicleBase(VehicleType type, Direction originalDirection, Parameters param);
       VehicleBase(const VehicleBase& other);
       ~VehicleBase();

       inline int getVehicleID() const { return this->vehicleID; }

       void setVehicleID(int num) {vehicleID=num;}

       inline VehicleType getVehicleType() const { return this->vehicleType; }
       inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }

       inline int getVehicleSize() {return this->vehicleSize;}
       inline bool getTurn() {return this->turnRight;}
};

#endif
