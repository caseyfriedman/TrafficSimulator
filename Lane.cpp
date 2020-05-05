#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include "Random.h"

Lane::Lane()
{
    //assume it is NB lane with roadSize 10
    roadSize = 10;
    //int numSections = roadSize + 6;
    midLane = (roadSize+6)/2;
    
    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
    
    lane.push_back(nullptr);
    lane.push_back(nullptr);
    
    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
}



Lane::Lane(Parameters params, Direction t, TrafficLight* light) : light(light)
{
   
  //  vehicleTurningRight = nullptr;   

    type = t; 

    roadSize = params.compute_total_size();
    midLane = (roadSize)/2;

    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
    

    lane.push_back(nullptr); //the intersections are created by Road but aren't available at initialization
    lane.push_back(nullptr);


    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }

    //read and store the probabilties for new vehicles for each lane
    switch(this->type)
    {
       case Direction::north: probOfNewVehicle = params.get_prob_new_vehicle_northbound(); break;
       case Direction::south: probOfNewVehicle = params.get_prob_new_vehicle_southbound(); break;
       case Direction::east: probOfNewVehicle = params.get_prob_new_vehicle_eastbound(); break;
       case Direction::west: probOfNewVehicle = params.get_prob_new_vehicle_westbound(); break;
    }
}

Lane::~Lane() {}

void Lane::advanceLane() //return a vehicle id?
{
    int currVehicle = -1;
    bool vehicleHead = false;
    setTurningVehicle(nullptr);
    setMakingRight(false);
    
    for(int i = lane.size() - 1; i >= 0; i--)
    {
        if(lane[i]->isOccupied())
        {
            if(lane[i]->getVehicle()->getVehicleID() != currVehicle)
            {
                currVehicle = lane[i]->getVehicle()->getVehicleID();
                vehicleHead = true;

            }

            if(i == lane.size() - 1) // vehicle is at the end
            {
                
                 
                //lane[i]->setVehicle(nullptr);
                removeVehicle(i);
                continue;
            }
            else if(i > midLane + 1)
            {
                moveForwardTo(i);
                continue;
            }
            else if ((i == midLane + 1) && !light->getIsRed()) //what if it's turning
            {
                moveForwardTo(i);
                continue;
            }
            else if(i == midLane && !light->getIsRed()) //if we're in the intersection
            {

                if(lane[i]->getVehicle()->getTurn())
                {
                    //cout << "The Vehicle ID that is turning right is " << lane[i]->getVehicle()->getVehicleID() << endl;
                    //cout << "And the vehicle is in " << lane[i]->getVehicle()->getVehicleOriginalDirection() << endl;
                    setMakingRight(true); //indicate a vehicle is making a right
                    
                    //I changed it to be vehiclePtr because that's what the other methods seemed to do
                    setTurningVehicle(lane[i]->vehiclePtr); //store vehicle that is making a right
                    //ERROR
                   
  
                    lane[i]->setVehicle(nullptr); //Remove vehicle and Road will add it to the appropriate lane
                }
                else
                {
                    moveForwardTo(i);
                    continue;
                }
                continue;
            }
            else if(i == midLane - 1)
            {
                if(vehicleHead && determineHead(i)) //vehicle heads should check if they can go
                {
                    //cout << "determineHead = "<< determineHead(i) << endl;
                    if(canMakeLight(lane[i]->getVehicle())) //move if can make it
                    {
                    
                        moveForwardTo(i);
                        continue;
                    }
                    else
                    {
                        continue; //cannot make light, no move 
                    }
                }
                else //is a body of car, no decisions to be made (can assume its safe to move) 
                {
                    
                    moveForwardTo(i);
                    
                    continue; 
                }
            }
            else
            {
                if(i < midLane && !lane[i+1]->isOccupied()) // and the light isn't red
                {
                    moveForwardTo(i);
                }
            }
        }
        vehicleHead = false;
    }
}

void Lane::addVehicle(VehicleBase* vehiclePtr)
{ //might want it not to be a pointer, will wait and see
    for (int i = 3; i > 3-vehiclePtr->getVehicleSize(); i--) //vehicles always added at pos 3 (first visible pos in lane)
    //truck will fill pos 3-0
    //suv will fill pos 3-1
    //car will fill pos 3-2
    {
        lane[i]->setVehicle(vehiclePtr);
    }
}

bool Lane::canMakeLight(VehicleBase* vehicle)
{
    if(light->getIsRed()) //every lane only needs 1 traffic light
    {
        return false;
    }
    
    return timeToCross(vehicle) <= light->timeUntilRed();
}

int Lane::timeToCross(VehicleBase* vehicle)   //should this be a pointer???
{
    int timeToCross = 2;
    
    timeToCross += vehicle->getVehicleSize();
    
    if(vehicle->getTurn())
    {
        timeToCross -= 1;
    }
    return timeToCross;
}

bool Lane::canNewCarCome()
{
    return !lane[4]->isOccupied();
}

bool Lane::shouldNewCarCome()
{
    //generate random number
    double randNum = Random::generateNum();

    if (randNum <= probOfNewVehicle)
    {
       return true;
    }
    return false; 
}

void Lane::addIntersections(vector<Section*> intersections){


/*
intersection[0] = NE
intersection[1] = NW
intersection[2] = SE
intersection[3] = SW
*/

    
    if(type == Direction::north)
    {
    
        lane[midLane] = intersections[2]; //SE
        lane[midLane + 1] = intersections[0]; //NE
    }
    else if(type == Direction::east)
    {
   
        lane[midLane] = intersections[3]; //SW
        lane[midLane + 1] = intersections[2]; //SE
    }
    else if(type == Direction::south)
    {
      
        lane[midLane] = intersections[1]; //NW
        lane[midLane + 1] = intersections[3]; //SW
    }
    else if(type == Direction::west)
    {
      
        lane[midLane] = intersections[0]; //NE
        lane[midLane + 1] = intersections[1]; //NW
    }

}


void Lane::moveForwardTo(int i){

     lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
     lane[i]->setVehicle(nullptr);
} 

void Lane::addAtTurnIndex(VehicleBase* vehicle)    
{
    lane[midLane + 2]->setVehicle(vehicle);
}


bool Lane::determineHead(int vehicleIndex)
{
    //compute vehicleID and size of vehicle to save on calculations
    int vehicleID = lane[vehicleIndex]->vehiclePtr->getVehicleID();
    int count = lane[vehicleIndex]->vehiclePtr->getVehicleSize();
    
    //for testing purposes, allows us to know whether vehicle section at index is truly a head
  
    //determine whether vehicle section at vehicleIndex is a head of vehicle 
    int i = 1;  //initialize i to 1 because we want to check index, 1 to (vehicle size-1) before it
    
    //if null pointer directly behind, it is not a head
    if (!lane[vehicleIndex-i]->vehiclePtr)
    {  
        return false;
    }
    //if index ahead is not a nullptr and is the same vehicle, it is not a head
    if (lane[vehicleIndex+1]->vehiclePtr && vehicleID != lane[vehicleIndex+1]->getVehicle()->getVehicleID())
    {      
           return false;
    }
    //while null pointers are not found and we have not iterated for size of vehicle,
    //if any index 1 before to (vehicle size-1) before vehicleIndex is not same vehicle
    //then it is not head
    while (lane[vehicleIndex-i]->vehiclePtr && i < count)
    {
       
       if (vehicleID != lane[vehicleIndex-i]->getVehicle()->getVehicleID())
       {  
           return false;
       }
       i++;
    }
    //if exited loop early due to null ptr, it is not a head 
    if (i<count)
    {     
           return false;
    }
    //if all of the above conditions are not met, then it is head
   
    return true;
}

void Lane::removeVehicle(int i){
    cout << "Deleting car " << lane[i]->getVehicle()->getVehicleID() << endl;
    cout << "deleting at index: " << i << endl;
    //cout << "vehicle with size: " << lane[i]->getVehicle()->getVehicleSize() <<endl; 
    VehicleBase* vehicle = lane[i]->getVehicle();
            for(int x = i;x>(roadSize - (vehicle->getVehicleSize() - 1)); x--){
                lane[x]->setVehicle(nullptr);
            }

            delete vehicle;
}
#endif
