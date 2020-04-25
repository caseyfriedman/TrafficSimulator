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
        Lane(int size, Direction type, vector<Section*> intersections);
        ~Lane();
    
        void advanceLane();
        void makeRight();
        bool canMakeLight(VehicleBase vehicle);
        int timeToCross(VehicleBase vehicle);
        bool canNewCarCome();
};
#endif
