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
      void setValues(LightDirection lightDir, Parameters params); //this might be unnecessary and can probably be deleted 
      inline int timeUntilRed() {return this->counter;}
      bool getIsRed() {return this->isRed;}
      LightColor getColor();

      void setTimeUntilRed(int time) {counter = time;}



};

#endif
