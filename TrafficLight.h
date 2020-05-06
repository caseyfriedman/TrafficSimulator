/**

Created by Casey, Mikaela, and Aidan

5/5/20

This header file contains information about the TrafficLight and its methods

*/

#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include "Parameters.h"
#include "Animator.h"
#include <iostream>

enum class LightDirection   {EW, NS};

class TrafficLight
{
private:
    int counter;
    int timeGreen;
    int timeYellow;
    int timeRed;
    bool isRed;

public:
    TrafficLight(LightDirection lightDir, Parameters params);
    TrafficLight();
    ~TrafficLight();
    void update();

    inline int timeUntilRed()
    {
        return this->counter;
    }
    bool getIsRed()
    {
        return this->isRed;
    }
    LightColor getColor();
};

#endif
