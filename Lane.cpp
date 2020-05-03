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
    roadSize = (params.get_number_of_sections_before_intersection() * 2);  //*2 because there are 2 sides, +2 because of the intersection

    //I thought we should add 2 to the roadsize but that messes up the total count

    type = t; 
    //roadSize = size;
    int numSections = roadSize + 6;
    midLane = (numSections)/2;
    cout <<"Total number of sections is" << numSections << "Middle" << midLane << endl;    

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
                moveForward(i);
            }
            else if ((i == midLane + 1) && !light->getIsRed())
            {
                moveForward(i);
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
                    
                    moveForward(i);
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

    cout << lane[midLane] << endl;

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

void Lane::moveForward(int i){

     lane[i + 1]->setVehicle(lane[i]->vehiclePtr);
     lane[i]->setVehicle(nullptr);
} 
    

}



#endif
