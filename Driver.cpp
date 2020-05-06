/**

Created by Casey, Mikaela, and Aidan

5/5/20

Driver runs the Traffic Intersection Simulation. It takes in command line arguments
[input file] [seed number].

*/

#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Parameters.h"
#include "TrafficLight.h"
#include "Random.h"
#include "Road.h"
using namespace std;

int main(int argc, char *argv[])
{
    //Animator::MAX_VEHICLE_COUNT = 9999;  // vehicles will be displayed with four digits
    Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    //Animator::MAX_VEHICLE_COUNT = 99;  // vehicles will be displayed with two digits

    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <ParameterFile> <seed number>" << std::endl;
        exit(0);
    }
    
    //Read and store parameters
    Parameters params(argv[1]);

    Random::setSeed(atoi(argv[2]));

    int halfSize = params.get_number_of_sections_before_intersection();  // number of sections before intersection

    Animator anim(halfSize);

    //Create instance of Road, which will create the Sections and Lanes
    Road road(params);

    //construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase *> westbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase *> eastbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase *> southbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase *> northbound(halfSize * 2 + 2, nullptr);

    char dummy;

    //set initial colors for animated traffic light
    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);

    int i = 0;
    //while max simulation time is not met
    while (i <= params.get_max_simulated_time())
    {
        road.advanceRoad();

        //syncs the lane with vehiclebase vector
        for(int i = 3; i < road.getRoadsize() - 3; i++)
        {
            northbound[i - 3] = road.getNB().getLane()[i]->getVehicle();
            southbound[i - 3] = road.getSB().getLane()[i]->getVehicle();
            eastbound[i - 3] = road.getEB().getLane()[i]->getVehicle();
            westbound[i - 3] = road.getWB().getLane()[i]->getVehicle();
        }
        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        anim.setVehiclesWestbound(westbound);

        anim.setLightNorthSouth(road.getNsLight().getColor());
        anim.setLightEastWest(road.getEwLight().getColor());

        anim.draw(i++);
        std::cin.get(dummy);
    }

    road.deletePointers();

    return 0;

}
