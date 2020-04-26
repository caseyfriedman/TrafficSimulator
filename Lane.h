#ifndef __LANE_H__
#define __LANE_H__

#include <vector>
#include <string>
#include "Section.h"
#include "TrafficLight.h"

using namespace std;

class Lane
{
    private:
        Direction type;
        int roadSize;
        int midLane;
        vector<Section*> lane;
        Lane* rigthTurnOnto;
        TrafficLight* light;
    
    public:
        Lane();
        Lane(int size, Direction type, vector<Section*> intersections, TrafficLight* light); //road is gonna tell us how much time until red
        ~Lane();
 
        void advanceLane();
        void moveForward(int index);
        void addVehicle(VehicleBase* vehicle); //maybe should be boolean and return false if there's a vehicle there?
      
        bool canMakeLight(VehicleBase vehicle);
        int timeToCross(VehicleBase vehicle);
        bool canNewCarCome();


        //TESTING

        vector<Section*> getLane() {return lane;}
    
};
#endif
