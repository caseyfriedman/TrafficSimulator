/**

Created by Casey, Mikaela, and Aidan

5/5/20

Road constructor takes in Parameters, and it creates and holds TrafficLights, Lanes, and the intersections.
Road handles random vehicle generation.

*/

#include "Road.h"

Road::Road()
{


}

Road::Road(Parameters params) : nsLight(LightDirection::NS, params),
    ewLight(LightDirection::EW, params), northBound(params, Direction::north,
            &nsLight), southBound(params, Direction::south, &nsLight), eastBound(
                params, Direction::east, &ewLight), westBound(params, Direction::west,
                        &ewLight)
{
    roadSize = params.compute_total_size();

    createVectors(params);

    setIntersections();

    setLanes();
}

void Road::setIntersections()
{
    neIntersection.setIntersection();
    nwIntersection.setIntersection();
    seIntersection.setIntersection();
    swIntersection.setIntersection();

    intersections.push_back(&neIntersection);
    intersections.push_back(&nwIntersection);
    intersections.push_back(&seIntersection);
    intersections.push_back(&swIntersection);
}

void Road::setLanes()
{
    for(int i = 0; i < 4; i++)
    {
        laneVec[i]->addIntersections(intersections);
    }
}

void Road::advanceRoad()
{
    //calls advanceLane on each lane- this takes care of straight movement and will return values for lane to do right turns

    for(int i = 0; i < 4; i++)
    {
        laneVec[i]->advanceLane();
    }

    //call the appropriate methods for right turns to occur for all lanes- only lanes with green light should be
    if(!ewLight.getIsRed()) //if east west light is not red, these cars may be turning
    {
        if (eastBound.getTurningVehicle())
        {
            southBound.addAtTurnIndex(eastBound.getTurningVehicle());

            eastBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
            eastBound.setMakingRight(false);
        }
        if (westBound.getTurningVehicle())
        {
            northBound.addAtTurnIndex(westBound.getTurningVehicle());

            westBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
            westBound.setMakingRight(false);
        }
    }
    else //north south cars may be turning
    {
        if (northBound.getTurningVehicle())
        {
            eastBound.addAtTurnIndex(northBound.getTurningVehicle());

            northBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
            northBound.setMakingRight(false);
        }
        if (southBound.getTurningVehicle())
        {
            westBound.addAtTurnIndex(southBound.getTurningVehicle());

            southBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
            southBound.setMakingRight(false);
        }
    }

    addNewVehicles();

    ewLight.update();
    nsLight.update();
}


void Road::addNewVehicles()
{
    double randNum;
    for(int i = 0; i < 4; i ++)
    {
        randNum = Random::generateNum();
        if(laneVec[i]->canNewCarCome() && (probNewVehicle[i] > randNum))
        {
            laneVec[i]->addVehicle(genNewVehicle(laneVec[i]->getDirection()));
        }
    }
}

VehicleBase* Road::genNewVehicle(Direction dir)
{
    double randNum = Random::generateNum();
    VehicleType t;

    //determines whether vehicle should be car, suv, or truck based on parameter values
    if(probVehicleType[0] > randNum) 
    {
        t = VehicleType::car;
    }
    else if ((probVehicleType[0] + probVehicleType[1]) > randNum)
    {
        t = VehicleType::suv;
    }
    else
    {
        t = VehicleType::truck;
    }

    VehicleBase* v = new VehicleBase(t, dir); //needs to be dynamically allocated

    randNum = Random::generateNum();

    //determines whether a vehicle should turn right based on type
    switch(t)
    {
    case VehicleType::car:
    {
        if (probRightTurn[0] >= randNum)
        {
            v->setRightTurn();
        }
        break;
    }
    case VehicleType::suv:
    {
        if (probRightTurn[1] >= randNum)
        {
            v->setRightTurn();
        }
        break;
    }
    case VehicleType::truck:
    {
        if (probRightTurn[2] >= randNum)
        {
            v->setRightTurn();
        }
        break;
    }
    }

    return v;
}


void Road::createVectors(Parameters params)
{

    probNewVehicle.push_back(params.get_prob_new_vehicle_northbound());
    probNewVehicle.push_back(params.get_prob_new_vehicle_southbound());
    probNewVehicle.push_back(params.get_prob_new_vehicle_eastbound());
    probNewVehicle.push_back(params.get_prob_new_vehicle_westbound());


    probVehicleType.push_back(params.get_proportion_of_cars());
    probVehicleType.push_back(params.get_proportion_of_SUVs());


    probRightTurn.push_back(params.get_proportion_right_turn_cars());
    probRightTurn.push_back(params.get_proportion_right_turn_SUVs());
    probRightTurn.push_back(params.get_proportion_right_turn_trucks());


    laneVec.push_back(&northBound);
    laneVec.push_back(&southBound);
    laneVec.push_back(&eastBound);
    laneVec.push_back(&westBound);

}


void Road::deletePointers(){
    for(int i=0;i<4;i++){
        laneVec[i]->deletePointers();   
    }


}



