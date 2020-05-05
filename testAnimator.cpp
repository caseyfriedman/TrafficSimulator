#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Parameters.h"
#include "TrafficLight.h"
#include "Road.h"

int main()
{
    //Read and store parameters
    Parameters params("inputFile.txt");

    //Animator::MAX_VEHICLE_COUNT = 9999;  // vehicles will be displayed with four digits
    Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    //Animator::MAX_VEHICLE_COUNT = 99;  // vehicles will be displayed with two digits   
 
    int halfSize = params.get_number_of_sections_before_intersection();  // number of sections before intersection

    Animator anim(halfSize);

    //Create instance of Road, which will create the Sections and Lanes
    Road road(params);

    //construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase*> westbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> eastbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> southbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> northbound(halfSize * 2 + 2, nullptr);

/*

syncs the lanes with the VehicleBase vectors

*/

 for(int i=3; i < road.eastBound.getLane().size() - 3; i++){

       eastbound[i-3] = road.eastBound.getLane()[i]->getVehicle();
       westbound[i-3] = road.westBound.getLane()[i]->getVehicle();
       northbound[i-3] = road.northBound.getLane()[i]->getVehicle();
       southbound[i-3] = road.southBound.getLane()[i]->getVehicle();
    } 

    char dummy;

    //set initial colors for animated traffic light
    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);

    int i = 0;
    //while max simulation time is not met
    while (i <= params.get_max_simulated_time())
    {
       road.advanceRoad();
       for(int i=3; i < road.eastBound.getLane().size() - 3; i++){
       eastbound[i-3] = road.eastBound.getLane()[i]->getVehicle();
       westbound[i-3] = road.westBound.getLane()[i]->getVehicle();
       northbound[i-3] = road.northBound.getLane()[i]->getVehicle();
       southbound[i-3] = road.southBound.getLane()[i]->getVehicle();
       }
       anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesSouthbound(southbound);
         anim.setVehiclesEastbound(eastbound);
          anim.setVehiclesWestbound(westbound);



       anim.setLightNorthSouth(road.getNsLight().getColor());
       anim.setLightEastWest(road.getEwLight().getColor());



       anim.draw(i++);
    }

    

   
}
