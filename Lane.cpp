/**

Created by Casey, Mikaela, and Aidan

5/5/20

Lane constructor takes in Parameters, Direction, and a pointer to a Traffic light

A Lane contains a vector of sections* and a corresponding light.

*/
#include "Lane.h"


Lane::Lane()
{
    roadSize = 10;

    midLane = (roadSize + 6) / 2;

    for(int i = 0; i < midLane; i++)
    {
        Section *sec = new Section();
        lane.push_back(sec);
    }

    lane.push_back(nullptr);
    lane.push_back(nullptr);

    for(int i = 0; i < midLane; i++)
    {
        Section *sec = new Section();
        lane.push_back(sec);
    }
}

Lane::Lane(Parameters params, Direction t, TrafficLight *light) : light(light)
{

    type = t;

    roadSize = params.compute_total_size();
    midLane = (roadSize) / 2;

    for(int i = 0; i < midLane; i++) //creates the first half of the sections
    {
        Section *sec = new Section();
        lane.push_back(sec);
    }


    lane.push_back(nullptr); //the intersections are created by Road but aren't available at initialization
    lane.push_back(nullptr); //so we need to add in placeholders


    for(int i = 0; i < midLane; i++)  //create the second half of the sections
    {
        Section *sec = new Section();
        lane.push_back(sec);
    }

}

Lane::~Lane() {}

/**

Advances Lane starting from the last index. 
The method moves vehicle pointers from section to section.
 
*/
void Lane::advanceLane()
{
    int currVehicle = -1;
    bool vehicleHead = false;
    setTurningVehicle(nullptr);
    setMakingRight(false);



    for(int i = lane.size() - 1; i >= 0; i--)//starting from the final index
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
                removeVehicle(i);
                continue;
            }
            else if(i > midLane + 1)
            {
                moveForwardTo(i);
                continue;
            }
            else if ((i == midLane + 1) && !light->getIsRed())
            {
                moveForwardTo(i);
                continue;
            }
            else if(i == midLane && !light->getIsRed()) //if we're in the intersection
            {

                if(lane[i]->getVehicle()->getTurn())
                {

                    setMakingRight(true); //indicate a vehicle is making a right
                    setTurningVehicle(lane[i]->getVehicle()); //store vehicle that is making a right

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

                    if(canMakeLight(lane[i]->getVehicle())) //move if can make it
                    {

                        moveForwardTo(i);
                        continue;
                    }
                    else
                    {
                        continue; //cannot make light, don't move
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
                if(i < midLane && !lane[i + 1]->isOccupied()) //if you are before the intersection and the next space is available
                {
                    moveForwardTo(i);
                }
            }
        }
        vehicleHead = false;
    }
}

void Lane::addVehicle(VehicleBase *vehiclePtr)
{
    for (int i = 3; i > 3 - vehiclePtr->getVehicleSize(); i--) //vehicles always added at pos 3 (first visible pos in lane)
        //truck will fill pos 3-0
        //suv will fill pos 3-1
        //car will fill pos 3-2
    {
        lane[i]->setVehicle(vehiclePtr);
    }
}

bool Lane::canMakeLight(VehicleBase *vehicle)
{
    if(light->getIsRed())
    {
        return false;
    }

    return timeToCross(vehicle) <= light->timeUntilRed();
}

int Lane::timeToCross(VehicleBase *vehicle)
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


void Lane::addIntersections(vector<Section *> intersections)
{
    /*
    intersection[0] = NW
    intersection[1] = SW
    intersection[2] = NE
    intersection[3] = SE
    */
    if(type == Direction::north)
    {
        lane[midLane] = intersections[2]; //NE
        lane[midLane + 1] = intersections[0]; //NW
    }
    else if(type == Direction::east)
    {
        lane[midLane] = intersections[3]; //SE
        lane[midLane + 1] = intersections[2]; //NE
    }
    else if(type == Direction::south)
    {
        lane[midLane] = intersections[1]; //SW
        lane[midLane + 1] = intersections[3]; //SE
    }
    else if(type == Direction::west)
    {
        lane[midLane] = intersections[0]; //NW
        lane[midLane + 1] = intersections[1]; //SW
    }

}


void Lane::moveForwardTo(int i)
{
    lane[i + 1]->setVehicle(lane[i]->getVehicle());
    lane[i]->setVehicle(nullptr);
}

void Lane::addAtTurnIndex(VehicleBase *vehicle)
{
    lane[midLane + 2]->setVehicle(vehicle);
}


bool Lane::determineHead(int vehicleIndex)
{
    //compute vehicleID and size of vehicle to save on calculations
    int vehicleID = lane[vehicleIndex]->getVehicle()->getVehicleID();
    int count = lane[vehicleIndex]->getVehicle()->getVehicleSize();

    //determine whether vehicle section at vehicleIndex is a head of vehicle
    int i = 1;  //initialize i to 1 because we want to check index, 1 to (vehicle size-1) before it

    //if null pointer directly behind, it is not a head
    if (!lane[vehicleIndex - i]->getVehicle())
    {
        return false;
    }
    //if index ahead is not a nullptr and is the same vehicle, it is not a head
    if (lane[vehicleIndex + 1]->getVehicle() && vehicleID == lane[vehicleIndex + 1]->getVehicle()->getVehicleID())
    {
        return false;
    }
    //while null pointers are not found and we have not iterated for size of vehicle,
    //if any index 1 before to (vehicle size-1) before vehicleIndex is not same vehicle
    //then it is not head
    while (lane[vehicleIndex - i]->getVehicle() && i < count)
    {

        if (vehicleID != lane[vehicleIndex - i]->getVehicle()->getVehicleID())
        {
            return false;
        }
        i++;
    }
    //if exited loop early due to null ptr, it is not a head
    if (i < count)
    {
        return false;
    }
    //if all of the above conditions are not met, then it is head
    return true;
}

void Lane::removeVehicle(int i)
{
    VehicleBase *vehicle = lane[i]->getVehicle();
    for(int x = i; x > (roadSize) - (vehicle->getVehicleSize() - 1); x--) //iterate backwards and delete all the parts
    {
        lane[x]->setVehicle(nullptr);
    }

    delete vehicle;
}


void Lane::deletePointers(){
    for(int i=0;i < roadSize - 1; i++){
        if(!lane[i]->isIntersection()){
            delete lane[i];
        }
    }
}


