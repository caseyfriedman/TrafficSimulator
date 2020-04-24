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
        Section* sec = new Section();
        lane.push_back(&sec);
    }
    
        lane.push_back(&NEIntersection);
        lane.push_back(&NWIntersection);
    
    for(int i = 0; i < numSections/2; i++)
    {
        Section* sec = new Section();
        lane.push_back(&sec);
    }
}

Lane::Lane(int size, Direction type)
{
    roadSize = size;
    int numSections = roadSize + 6;
    
    for(int i = 0; i < numSections/2; i++)
    {
        Section* sec = new Section();
        lane.push_back(&sec);
    }
    
    if(type == Direction::north)
    {
        lane.push_back(&NEIntersection);
        lane.push_back(&NWIntersection);
    }
    else if(type == Direction::east)
    {
        lane.push_back(&SEIntersection);
        lane.push_back(&NEIntersection);
    }
    else if(type == Direction::south)
    {
        lane.push_back(&SWIntersection);
        lane.push_back(&SEIntersection);
    }
    else if(type == Direction::west)
    {
        lane.push_back(&NWIntersection);
        lane.push_back(&SWIntersection);
    }

    for(int i = 0; i < numSections/2; i++)
    {
        Section* sec = new Section();
        lane.push_back(&sec);
    }
}

Lane::~Lane() {}

void Lane::advanceLane()
{
    int currVehicle = -1;
    bool vehicleHead = false;
    
    for(int i = lane.size() - 1; i >= 0; i--)
    {
        if(lane[i].isOccupied())
        {
            if(lane[i].getVehicle().getVehicleID() != currVehicle)
            {
                currVehicle = lane[i].getVehicle().getVehicleID();
                vehicleHead = true;
            }
            
            if(i == lane.size() - 1)
            {
                lane[i].setVehicle(nullptr);
            }
            else if(i > lane.size()/2)
            {
                lane[index + 1].setVehicle(currVehicle);
                lane[i].setVehicle(nullptr);
            }
            else if(i = lane.size()/2)
            {
                if(lane[i].turnRight())
                {
                    lane[i].makeRight();
                }
                else
                {
                    lane[index + 1].setVehicle(currVehicle);
                    lane[i].setVehicle(nullptr);
                }
            }
            else if(i == lane.size()/2 - 1)
            {
                if(vehicleHead && lane[i].canMakeLight())
                {
                    lane[index + 1].setVehicle(currVehicle);
                    lane[i].setVehicle(nullptr);
                }
                else
                {
                    lane[index + 1].setVehicle(currVehicle);
                    lane[i].setVehicle(nullptr);
                }
            }
            else
            {
                if(!lane[i+1].isOccupied())
                {
                    lane[index + 1].setVehicle(currVehicle);
                    lane[i].setVehicle(nullptr);
                }
            }
        }
        vehicleHead = false;
    }
    
}

void Lane::turnRight()
{
    if(type == Direction::north)
    {
        //right turn onto east
        eastBound.lane[lane.size()/2 + 2].setVehicle(lane[i].getVehicle());
        lane[i].setVehicle(nullptr);
    }
    else if(type == Direction::east)
    {
        //right turn onto south
        southBound.lane[lane.size()/2 + 2].setVehicle(lane[i].getVehicle());
        lane[i].setVehicle(nullptr);
    }
    else if(type == Direction::south)
    {
        //right turn onto west
        westBound.lane[lane.size()/2 + 2].setVehicle(lane[i].getVehicle());
        lane[i].setVehicle(nullptr);
    }
    else if(type == Direction::west)
    {
        //right turn onto north
        northBound.lane[lane.size()/2 + 2].setVehicle(lane[i].getVehicle());
        lane[i].setVehicle(nullptr);
    }
}

bool Lane::CanMakeLight()
{
    if(type == Direction::north || Direction::south)
    {
        if(trafficLightNS.getIsRed())
        {
            return false;
        }
        return timeToCross >= trafficLightNS.timeUntilRed();
    }
    else
    {
        if(trafficLightEW.getIsRed())
        {
            return false;
        }
        return timeToCross >= trafficLightNS.timeUntilRed();
    }
}

int Lane::timeToCross()
{
    int timeToCross = 2;
    
    timeToCross += vehiclePtr.getVehicle().getSize();
    
    if(vehiclePtr.getVehicle().turnRight())
    {
        timeToCross -= 1;
    }
    return timeToCross;
}

bool Lane::canNewCarCome()
{
    return !lane[4].isOccupied();
}
            
#endif
