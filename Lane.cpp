#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"

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

/*
intersection[0] = NE
intersection[1] = NW
intersection[2] = SE
intersection[3] = SW
*/

Lane::Lane(Parameters params, Direction t, TrafficLight* light) : light(light)
{

    roadSize = (params.get_number_of_sections_before_intersection() * 2) + 2;  //*2 because there are 2 sides, +2 because of the intersection

    type = t; 
    //roadSize = size;
    int numSections = roadSize + 6;
    midLane = (numSections)/2;
    cout <<"Road Size" << roadSize << "Middle" << midLane << endl;    

    for(int i = 0; i < midLane; i++)
    {
        Section* sec = new Section();
        lane.push_back(sec);
    }
    

    /*
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

*/


    lane.push_back(nullptr); //the intersections are created by Road but aren't available at initialization
    lane.push_back(nullptr);


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
        setMakingRight(false);
        setTurningVehicle(nullptr);
        
        if(lane[i]->isOccupied())
        {
            if(lane[i]->getVehicle().getVehicleID() != currVehicle)
            {
                currVehicle = lane[i]->getVehicle().getVehicleID();
                vehicleHead = true;

                cout << "assigning vehicle head, this should be done at the start: curVehicle = " << currVehicle << ", newVehicle =" << lane[i]->getVehicle().getVehicleID() << endl;
            }
            if(i == lane.size() - 1)
            {
                cout <<"part of vehicle at end" << endl;
                lane[i]->setVehicle(nullptr);
            }
            else if(i > midLane + 1)
            {
                cout <<"part of vehicle past intersection, i = " << i << "  midlane = "<< midLane << endl;
                lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                lane[i]->setVehicle(nullptr);
                //moveForward(i);
            }
            else if ((i == midLane + 1) && !light->getIsRed())
            {
                    //  lane[i + 1]->setVehicle(lane[i]->vehiclePtr); //this was the line that I edited
                lane[i]->setVehicle(nullptr);
            }
            else if(i == midLane && !light->getIsRed()) //if we're in the intersection
            {
                cout <<"part of vehicle in intersection" << endl;
                if(lane[i]->getVehicle().getTurn())
                {
                    setMakingRight(true); //indicate a vehicle is making a right
                    
                    //I changed it to be vehiclePtr because that's what the other methods seemed to do
                    setTurningVehicle(lane[i]->vehiclePtr); //store vehicle that is making a right
                    //ERROR
                    
                    lane[i]->setVehicle(nullptr); //Remove vehicle and Road will add it to the appropriate lane
                }
                else
                {
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
                }
                continue;
            }
            else if(i == midLane - 1)
            {
                cout <<"part of vehicle at intersection" << endl;
                if(vehicleHead) //vehicle heads should check if they can go
                {
                    if(canMakeLight(lane[i]->getVehicle())) //move if can make it
                    {
                        lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                        lane[i]->setVehicle(nullptr);
                        //moveForward(i);
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
                    lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
                    lane[i]->setVehicle(nullptr);
                    //moveForward(i);
                    
                    cout << "we movin it" << endl;
                    //continue; // the light is red and we don't 
                }
            }
            else
            {
                if(!lane[i+1]->isOccupied())
                {
                    //moveForward(i);
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

bool Lane::canMakeLight(VehicleBase vehicle)
{
    if(light->getIsRed()) //every lane only needs 1 traffic light
    {
        cout <<"light is red. do not enter intersection " << endl;
        return false;
    }
    
    cout <<"light is red " << light->getIsRed() << endl;
    cout <<"time left is " << light->timeUntilRed() << endl;
    return timeToCross(vehicle) <= light->timeUntilRed();
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


void Lane::addIntersections(vector<Section*> intersections){


    cout << lane[midLane] << endl;

    if(type == Direction::north)
    {
        cout << "NorthBoundLane created" << endl;
        lane[midLane] = intersections[2]; //SE
        lane[midLane + 1] = intersections[1]; //NE
    }
    else if(type == Direction::east)
    {
         cout << "EastBoundLane created" << endl;
        lane[midLane] = intersections[3]; //SW
        lane[midLane + 1] = intersections[2]; //SE
    }
    else if(type == Direction::south)
    {
         cout << "SouthBoundLane created" << endl;
        lane[midLane] = intersections[1]; //NW
        lane[midLane + 1] = intersections[3]; //SW
    }
    else if(type == Direction::west)
    {
         cout << "WestBoundLane created" << endl;
        lane[midLane] = intersections[0]; //NE
        lane[midLane + 1] = intersections[1]; //NW
    }

    
        //cout << lane[midLane] << endl;

        cout << intersections[0] << endl;
        cout << intersections[1] << endl;
        cout << intersections[2] << endl;
        cout << intersections[3] << endl;
}

#endif
