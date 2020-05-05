#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Parameters.h"
#include "TrafficLight.h"

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
    while (i <= params.get_maximum_simulation_time())
    {
       road.advanceRoad();
       for(int i=3; i < road.eastBound.getLane().size() - 3; i++){
       eastbound[i-3] = road.eastBound.getLane()[i]->getVehicle();
       westbound[i-3] = road.westBound.getLane()[i]->getVehicle();
       northbound[i-3] = road.northBound.getLane()[i]->getVehicle();
       southbound[i-3] = road.southBound.getLane()[i]->getVehicle();
       }
       //ask road to generate cars
       //ask road to move each lane
       //increment light and increment simulation time (i)
    }

    for (; i < 4; i++)
    {
        eastbound[10+i] = eastbound[11+i] = &vb1;
        eastbound[6+i] = eastbound[7+i] = eastbound[8+i] = &vb2;
        eastbound[0+i] = eastbound[1+i] = eastbound[2+i] = eastbound[3+i] = &vb3;

        westbound[9+i] = westbound[10+i] = &vb4;
        westbound[6+i] = westbound[7+i] = westbound[8+i] = &vb5;
        westbound[0+i] = westbound[1+i] = westbound[2+i] = westbound[3+i] = &vb6;

        southbound[12+j] = southbound[13+j] = &vb7;
        southbound[5+j] = southbound[6+j] = southbound[7+j] = &vb8;
        southbound[0+j] = southbound[1+j] = southbound[2+j] = southbound[3+j] = &vb9;

        northbound[12+j] = northbound[13+j] = &vb10;
        northbound[5+j] = northbound[6+j] = northbound[7+j] = &vb11;
//        northbound[0+j] = northbound[1+j] = northbound[2+j] = northbound[3+j] = &vb12;
        northbound[0+j] = northbound[1+j] = northbound[2+j] = northbound[3+j] = &vb13;

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        anim.draw(i);
        std::cin.get(dummy);

        southbound.assign(halfSize * 2 + 2, nullptr); // reset vector
        northbound.assign(halfSize * 2 + 2, nullptr); // reset
        eastbound.assign(halfSize * 2 + 2, nullptr); // reset
        westbound.assign(halfSize * 2 + 2, nullptr); // reset

        if (i == 1) anim.setLightEastWest(LightColor::yellow);
    }

    anim.setLightNorthSouth(LightColor::green);
    anim.setLightEastWest(LightColor::red);

    for (; j < 5; j++)
    {
        eastbound[10+i] = eastbound[11+i] = &vb1;
        eastbound[6+i] = eastbound[7+i] = eastbound[8+i] = &vb2;
        eastbound[0+i] = eastbound[1+i] = eastbound[2+i] = eastbound[3+i] = &vb3;

        westbound[9+i] = westbound[10+i] = &vb4;
        westbound[6+i] = westbound[7+i] = westbound[8+i] = &vb5;
        westbound[0+i] = westbound[1+i] = westbound[2+i] = westbound[3+i] = &vb6;

        southbound[12+j] = southbound[13+j] = &vb7;
        southbound[5+j] = southbound[6+j] = southbound[7+j] = &vb8;
        southbound[0+j] = southbound[1+j] = southbound[2+j] = southbound[3+j] = &vb9;

        northbound[12+j] = northbound[13+j] = &vb10;
        northbound[5+j] = northbound[6+j] = northbound[7+j] = &vb11;
//        northbound[0+j] = northbound[1+j] = northbound[2+j] = northbound[3+j] = &vb12;
        northbound[0+j] = northbound[1+j] = northbound[2+j] = northbound[3+j] = &vb13;

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        anim.draw(i+j);
        std::cin.get(dummy);

        southbound.assign(halfSize * 2 + 2, nullptr); // reset
        northbound.assign(halfSize * 2 + 2, nullptr); // reset
        eastbound.assign(halfSize * 2 + 2, nullptr); // reset
        westbound.assign(halfSize * 2 + 2, nullptr); // reset

        if (j == 2) anim.setLightNorthSouth(LightColor::yellow);
    }
}
