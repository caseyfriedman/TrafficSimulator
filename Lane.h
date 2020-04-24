#ifndef __LANE_H__
#define __LANE_H__

#include <vector>
#include <string>

using namespace std;

class Lane
{
    private:
        string type;
        int roadSize;
        vector<Section> lane;
    
    public:
        Lane();
        Lane(int size, string type);
        ~Lane();
    
        void advanceLane();
        void turnRight();
        bool canMakeLight();
        int timeToCross();
        bool canNewCarCome();
};
#endif
