/**

Created by Casey, Mikaela, and Aidan

5/5/20

Lane constructor takes in Parameters, Direction, and a pointer to a Traffic light

A Lane contains a vector of sections* and a corresponding light.

*/

#ifndef __LANE_H__
#define __LANE_H__

#include <vector>
#include <string>
#include "Section.h"
#include "TrafficLight.h"
#include "Parameters.h"
#include "Random.h"

using namespace std;

class Lane
{
    private:
        Direction type;
        int roadSize;
        int midLane;
        bool makingRight;
        double probOfNewVehicle;
        VehicleBase* vehicleTurningRight;
        vector<Section*> lane;
        TrafficLight* light;
        void removeVehicle(int i);
        void moveForwardTo(int i);
        bool canMakeLight(VehicleBase* vehicle);
        int timeToCross(VehicleBase* vehicle);
        bool determineHead(int vehicleIndex);    
    public:
        Lane();
        Lane(Parameters params, Direction type, TrafficLight* light); 
        ~Lane();
 
        void advanceLane();
        inline bool isMakingRight() {return this->makingRight;}
        inline void setMakingRight(bool myBoolean) {this->makingRight = myBoolean;}
        inline VehicleBase* getTurningVehicle() {return this->vehicleTurningRight;}
        inline void setTurningVehicle(VehicleBase* v) {this->vehicleTurningRight = v;}
        inline Direction getDirection(){return this->type;}
        void addVehicle(VehicleBase* vehicle);
        void addAtTurnIndex(VehicleBase* vehicle);     
 
        bool canNewCarCome();
        
        void addIntersections(vector<Section*> intersections);

        vector<Section*> getLane() {return lane;}

        void deletePointers();
    
};
#endif
