#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include "Section.h"
#include <vector>

Lane::Lane()
{
    //assume it is NB lane with roadSize 10
    roadSize = 10;
    int numSections = roadSize + 6;
    
    for(int i = 0; i < numSections/2; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
    
        lane.push_back(nullptr);
        lane.push_back(nullptr);
    
    for(int i = 0; i < numSections/2; i++)
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
    int numSections = roadSize + 6;
    
    for(int i = 0; i < numSections/2; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
    
    if(type == Direction::north)
    {
        lane.push_back(intersections[2]); //SE
        lane.push_back(intersections[0]); //SW
    }
    else if(type == Direction::east)
    {
        lane.push_back(intersections[1]); //NW
        lane.push_back(intersections[0]); //NE
    }
    else if(type == Direction::south)
    {
        lane.push_back(intersections[0]); //NW
        lane.push_back(intersections[3]); //SW
    }
    else if(type == Direction::west)
    {
        lane.push_back(intersections[2]); //SE
        lane.push_back(intersections[3]); //SW
    }

    for(int i = 0; i < numSections/2; i++)
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
            else if(i > lane.size()/2)
            {
                lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                lane[i]->setVehicle(nullptr);
            }


            /*
            else if(i == lane.size()/2) //if we're in the intersection
            {
            
                else
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
                }
                
                continue;

            }

            */


            else if(i == lane.size()/2 - 1)
            {
                if(vehicleHead) //vehicle heads should check if they can go
                {
                    if(canMakeLight(lane[i]->getVehicle())) //move if can make it
                    {
                        lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                        lane[i]->setVehicle(nullptr);

                        cout << "we movin it" << endl;
                    }
                    else
                    {
                        continue; //cannot make light, no move 
                    }
                }
                else //is a body of car, no decisions to be made (can assume its safe to move) 
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);

                    cout << "we movin it" << endl;
                    //continue; // the light is red and we don't 
                }
            }
            else
            {
                if(!lane[i+1]->isOccupied())
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
                }
            }
        }
        vehicleHead = false;
    }

}


/*

void Lane::makeRight()
{
    if(type == Direction::north)
    {
        //right turn onto east
        //eastBound.lane[lane.size()/2 + 2].setVehicle(lane[lane.size()/2]->getVehicle()); //individual lanes don't have acccess to other lanes
        lane[lane.size()/2]->setVehicle(nullptr);
    }
    else if(type == Direction::east)
    {
        //right turn onto south
        //southBound.lane[lane.size()/2 + 2]->setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
    else if(type == Direction::south)
    {
        //right turn onto west
        //westBound.lane[lane.size()/2 + 2].setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
    else if(type == Direction::west)
    {
        //right turn onto north
        ///northBound.lane[lane.size()/2 + 2]->setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
}


*/

bool Lane::canMakeLight(VehicleBase vehicle)
{
    
        if(light->getIsRed()) //every lane only needs 1 traffic light
        {

    
            return false;
        }

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


void Lane::addVehicle(VehicleBase* vehicleptr)
{ //might want it not to be a pointer, will wait and see
    for (int i = 0; i < vehicleptr->getVehicleSize(); i++)
    {
	lane[i]->setVehicle(vehicleptr);
    }
}
            
#endif
