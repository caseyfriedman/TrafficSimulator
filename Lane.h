#ifndef __LANE_H__
#define __LANE_H__

#include <vector>
#include <string>
#include "Section.h"

using namespace std;

class Lane
{
    private:
        Direction type;
        int roadSize;
        vector<Section*> lane;
        Lane* rigthTurnOnto;
    
    public:
        Lane();
        Lane(int size, Direction type, vector<Section*> intersections, int timeUntilRed); //road is gonna tell us how much time until red
        ~Lane();
    
        void advanceLane();
      
        bool canMakeLight(VehicleBase vehicle);
        int timeToCross(VehicleBase vehicle);
        bool canNewCarCome();
};
#endif
