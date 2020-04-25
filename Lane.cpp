#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include "Section.h"
#include <vector>

//int Lane::roadSize;
//vector<Section*> Lane::lane;

Lane::Lane()
{
    //assume it is NB lane with roadSize 10
    roadSize = 10;
    int numSections = roadSize + 6;
    
    for(int i = 0; i < numSections/2; i++)
    {
        Section* sec = new See3ction();
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
Lane::Lane(int size, Direction type, vector<Section*> intersections)
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
        lane.push_back(intersections[2]);//SE //double check that the order is right
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
            if(lane[i]->getVehicle().getVehicleID() != currVehicle)
            {
                currVehicle = lane[i]->getVehicle().getVehicleID();
                vehicleHead = true;
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
            else if(i == lane.size()/2)
            {
                if(lane[i]->getVehicle().getTurn())
                {
                    makeRight();
                }
                else
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
                }
            }
            else if(i == lane.size()/2 - 1)
            {
                if(vehicleHead && canMakeLight(lane[i]->getVehicle()))
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
                }
                else
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
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

void Lane::makeRight()
{
    if(type == Direction::north)
    {
        //right turn onto east
        eastBound.lane[lane.size()/2 + 2].setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
    else if(type == Direction::east)
    {
        //right turn onto south
        southBound.lane[lane.size()/2 + 2]->setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
    else if(type == Direction::south)
    {
        //right turn onto west
        westBound.lane[lane.size()/2 + 2].setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
    else if(type == Direction::west)
    {
        //right turn onto north
        northBound.lane[lane.size()/2 + 2]->setVehicle(lane[lane.size()/2]->getVehicle());
        lane[lane.size()/2]->setVehicle(nullptr);
    }
}

bool Lane::canMakeLight(VehicleBase vehicle)
{
    if((type == Direction::north) || (type == Direction::south))
    {
        if(trafficLightNS.getIsRed())
        {
            return false;
        }
        return timeToCross(vehicle) >= trafficLightNS.timeUntilRed();
    }
    else
    {
        if(trafficLightEW.getIsRed())
        {
            return false;
        }
        return timeToCross(vehicle) >= trafficLightNS.timeUntilRed();
    }
}

int Lane::timeToCross(VehicleBase vehicle)
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
            
#endif
