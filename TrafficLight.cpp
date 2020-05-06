/**

Created by Casey, Mikaela, and Aidan

5/5/20

This file contains methods for the Traffic Light. Constructor takes in a LightDirection and the Parameters.
Traffic Light is updated at every time step.

*/

#include "TrafficLight.h"


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


TrafficLight::TrafficLight() {}

TrafficLight::~TrafficLight() {}

void TrafficLight::update()
{

    if (counter == 0)
    {
        isRed = true;  //count to red finished, light is now red
        counter = timeRed + timeGreen + timeYellow - 1;   //counter reset

    }
    else if (counter == timeGreen + timeYellow)
    {
        counter--;
        isRed = false; //counter has past red portion, light is not red

    }
    else
    {
        std::cout << counter << std::endl;
        counter--;

    }
}



/**
  This method is used to get the correct color for the animator
*/
LightColor TrafficLight::getColor()
{
    if(counter >= 0 && counter < timeYellow)
    {
        return LightColor::yellow;
    }
    else if (getIsRed())
    {
        return LightColor::red;
    }

    return LightColor::green;
}


