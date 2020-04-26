#ifndef __TRAFFIC_LIGHT_CPP__
#define __TRAFFIC_LIGHT_CPP__

#include <iostream>
#include "TrafficLight.h"
#include "Parameters.h"

TrafficLight::TrafficLight(LightDirection lightDir, Parameters params)
{
   switch(lightDir)
   {  
      case LightDirection::EW: 
           {
              timeGreen = params.get_green_east_west();
              timeYellow = params.get_yellow_east_west();
              timeRed = params.get_green_north_south() + params.get_yellow_north_south();
              counter = timeGreen + timeYellow; 
              isRed = false;  //defaults to EW being green first
              break;
           }
      case LightDirection::NS:
           {
              timeGreen = params.get_green_north_south();
              timeYellow = params.get_yellow_north_south();
              timeRed = params.get_green_east_west() + params.get_yellow_east_west();
              counter = timeRed + timeGreen + timeYellow;
              isRed = true;  //defaults to NS being red first
              break;
           }
   } 
}

TrafficLight::~TrafficLight() {}

void TrafficLight::update()
{
   if (counter == 0)
   {
      isRed = true;  //count to red finished, light is now red
      counter = timeRed + timeGreen + timeYellow;   //counter reset
      std::cout << "Light set red" << std::endl;
   }
   else if (counter == timeGreen + timeYellow)
   {
      counter--;
      isRed = false; //counter has past red portion, light is not red
      std::cout << "Light set green" << std::endl;  
   }
   else
   {
      //counter--;
      std::cout << counter-- << std::endl;
   }
}

#endif
