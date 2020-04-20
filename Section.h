#ifndef __SECTION_H__
#define __SECTION_H__

#import "VehicleBase.h"

class Section
{
   public:
      VehicleBase* vehiclePtr;

   private:
      bool         intersection;
      static int   numOfSecs;

   public:
      Section();
      Section(VehicleBase* vehicle);
      ~Section();

      void setIntersection() {intersection = true;}

      inline bool isOccupied() {return (vehiclePtr != nullptr);}
      inline bool isIntersection() {return this->intersection;}

      inline VehicleBase getVehicle() {return *vehiclePtr;}

      inline int getNumOfSecs() {return numOfSecs;}
};

#endif
