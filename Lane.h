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
        vector<Section> lane;
    
    public:
        Lane();
        Lane(int size, Direction type);
        ~Lane();
    
        void advanceLane();
        void turnRight();
        bool canMakeLight();
        int timeToCross();
        bool canNewCarCome();
};
#endif
