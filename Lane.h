#ifndef __LANE_H__
#define __LANE_H__

#include <vector>
#include <string>
#include "Section.h"
#include "TrafficLight.h"
#include "Parameters.h"

using namespace std;

class Lane
{
    private:
        Direction type;
        int roadSize;
        int midLane;
        bool makingRight;
        VehicleBase* vehicleTurningRight;
        vector<Section*> lane;
        TrafficLight* light;
    
    public:
        Lane();
        Lane(Parameters params, Direction type, TrafficLight* light); //road is gonna tell us how much time until red
        ~Lane();
 
        void advanceLane();
        inline bool isMakingRight() {return this->makingRight;}
        inline void setMakingRight(bool myBoolean) {this->makingRight = myBoolean;}
        inline VehicleBase* getTurningVehicle() {return this->vehicleTurningRight;}
        inline void setTurningVehicle(VehicleBase* v) {this->vehicleTurningRight = v;}
        void addVehicle(VehicleBase* vehicle); //maybe should be boolean and return false if there's a vehicle there?
      
        bool canMakeLight(VehicleBase vehicle);
        int timeToCross(VehicleBase vehicle);
        bool canNewCarCome();

        void addIntersections(vector<Section*> intersections);

        //TESTING

        vector<Section*> getLane() {return lane;}
    
};
#endif
