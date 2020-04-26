#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include "Section.h"
#include <vector>

Lane::Lane()
{
    //assume it is NB lane with roadSize 10
    roadSize = 10;
    //int numSections = roadSize + 6;
    int midLane = (roadSize+6)/2;
    
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

/*
intersection[0] = NE
intersection[1] = NW
intersection[2] = SE
intersection[3] = SW
*/

Lane::Lane(int size, Direction type, vector<Section*> intersections, TrafficLight* light) : light(light)
{
    roadSize = size;
    //int numSections = roadSize + 6;
    int midLane = (roadSize+6)/2;
    
    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
    
    if(type == Direction::north)
    {
        lane.push_back(intersections[0]); //NE
        lane.push_back(intersections[1]); //NW
    }
    else if(type == Direction::east)
    {
        lane.push_back(intersections[2]); //SE
        lane.push_back(intersections[0]); //NE
    }
    else if(type == Direction::south)
    {
        lane.push_back(intersections[3]); //SW
        lane.push_back(intersections[2]); //SE
    }
    else if(type == Direction::west)
    {
        lane.push_back(intersections[1]); //NW
        lane.push_back(intersections[3]); //SW
    }

    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
}

Lane::~Lane() {}

void Lane::advanceLane()
{
    int currVehicle = -1;
    bool vehicleHead = false;
    
    for(int i = lane.size() - 1; i >= 0; i--)
    {
        if(lane[i]->isOccupied())
        {
            if(lane[i]->getVehicle().getVehicleID() != currVehicle) //what's this for?
            {
                currVehicle = lane[i]->getVehicle().getVehicleID();
                vehicleHead = true;

                cout << "assigning vehicle head, this should be done at the start: curVehicle = " << currVehicle << ", newVehicle =" << lane[i]->getVehicle().getVehicleID() << endl;
            }
            
            if(i == lane.size() - 1)
            {
                lane[i]->setVehicle(nullptr);
            }
            else if(i > midLane)
            {
                //lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                //lane[i]->setVehicle(nullptr);
                moveForward(i);
            }


            /*
            else if(i == midLane()) //if we're in the intersection
            {
            
                else
                {
                    //lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    //lane[i]->setVehicle(nullptr);
                    moveForward(i);
                }
                
                continue;

            }

            */


            else if(i == midLane - 1)
            {
                if(vehicleHead) //vehicle heads should check if they can go
                {
                    if(canMakeLight(lane[i]->getVehicle())) //move if can make it
                    {
                        //lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                        //lane[i]->setVehicle(nullptr);
                        moveForward(i);
                        
                        cout << "we movin it" << endl;
                    }
                    else
                    {
                        cout << "we cannot make light" << endl;
                        continue; //cannot make light, no move 
                    }
                }
                else //is a body of car, no decisions to be made (can assume its safe to move) 
                {
                    //lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    //lane[i]->setVehicle(nullptr);
                    moveForward(i);
                    
                    cout << "we movin it" << endl;
                    //continue; // the light is red and we don't 
                }
            }
            else
            {
                if(!lane[i+1]->isOccupied())
                {
                    moveForward(i);
                    //lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    //lane[i]->setVehicle(nullptr);
                }
            }
        }
        vehicleHead = false;
    }
}


void moveForward(int index)
{
    lane[index + 1]->setVehicle(lane[index]->vehiclePtr);
    lane[index]->setVehicle(nullptr);
}

/*

void Lane::makeRight()
{
    if(type == Direction::north)
    {
        //right turn onto east
        //eastBound.lane[midLane + 2].setVehicle(lane[midLane]->getVehicle()); //individual lanes don't have acccess to other lanes
        lane[midLane]->setVehicle(nullptr);
    }
    else if(type == Direction::east)
    {
        //right turn onto south
        //southBound.lane[midLane + 2]->setVehicle(lane[midLane]->getVehicle());
        lane[midLane]->setVehicle(nullptr);
    }
    else if(type == Direction::south)
    {
        //right turn onto west
        //westBound.lane[midLane + 2].setVehicle(lane[midLane]->getVehicle());
        lane[midLane]->setVehicle(nullptr);
    }
    else if(type == Direction::west)
    {
        //right turn onto north
        ///northBound.lane[midLane + 2]->setVehicle(lane[midLane]->getVehicle());
        lane[midLane]->setVehicle(nullptr);
    }
}


*/

bool Lane::canMakeLight(VehicleBase vehicle)
<<<<<<< HEAD
{
        if(light->getIsRed()) //every lane only needs 1 traffic light
        {
            return false;
        }
=======
{   
        if(light->getIsRed()) //every lane only needs 1 traffic light
        {   
            return false;
        }
        
        cout <<"light is red " << light->getIsRed() << endl;
>>>>>>> 3c7d532b2944de63e1ab64414831ebf8fbda5692
        cout <<"time left is " << light->timeUntilRed() << endl;
        return timeToCross(vehicle) >= light->timeUntilRed();
}

int Lane::timeToCross(VehicleBase vehicle)   //should this be a pointer???
{
    int timeToCross = 2;
    
    timeToCross += vehicle.getVehicleSize();
    
    if(vehicle.getTurn())
    {
        timeToCross -= 1;
    }
    return timeToCross;
}

bool Lane::canNewCarCome()
{
    return !lane[4]->isOccupied();
}

void Lane::addVehicle(VehicleBase* vehiclePtr)
{ //might want it not to be a pointer, will wait and see
    for (int i = 3; i > 3-vehicleptr->getVehicleSize(); i--) //vehicles always added at pos 3 (first visible pos in lane)
    //truck will fill pos 3-0
    //suv will fill pos 3-1
    //car will fill pos 3-2
>>>>>>> 3c7d532b2944de63e1ab64414831ebf8fbda5692
    {
        lane[i]->setVehicle(vehicleptr);
    }
}
            
#endif
