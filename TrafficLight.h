#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include "Parameters.cpp"

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
      ~TrafficLight();
      void update();
      inline int timeUntilRed() {return this->counter;}
      bool getIsRed() {return this->isRed;}
};

#endif
