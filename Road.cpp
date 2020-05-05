#include "Road.h"
#include "Random.h"
#include <iostream>
using namespace std;


Road::Road(){

	
}

Road::Road(Parameters params) : nsLight(LightDirection::NS, params),
ewLight(LightDirection::EW,params), northBound(params, Direction::north, 
	&nsLight), southBound(params, Direction::south, &nsLight), eastBound(
	params, Direction::east, &ewLight), westBound(params, Direction::west,
	&ewLight){

	param = params; //Needed for Line 176 to compile

	setIntersections();

	setLanes();

    laneVec.push_back(northBound);
    laneVec.push_back(southBound);
    laneVec.push_back(eastBound);
    laneVec.push_back(westBound);
    
    probNewVehicle.push_back(params.get_prob_new_vehicle_northbound());
    probNewVehicle.push_back(params.get_prob_new_vehicle_southbound());
    probNewVehicle.push_back(params.get_prob_new_vehicle_eastbound());
    probNewVehicle.push_back(params.get_prob_new_vehicle_westbound());

    probVehicleType.push_back(params.get_proportion_of_cars());
    probVehicleType.push_back(params.get_proportion_of_SUVs());

}


void Road::setIntersections(){
		neIntersection.setIntersection();
		nwIntersection.setIntersection();
		seIntersection.setIntersection();
		swIntersection.setIntersection();
	
		intersections.push_back(&neIntersection);
		intersections.push_back(&nwIntersection);
		intersections.push_back(&seIntersection);
		intersections.push_back(&swIntersection);

}




void Road::setLanes(){
    
        for(int i = 0; i < 4; i++)
        {
            laneVec[i].addIntersections(intersections);
        }
		//northBound.addIntersections(intersections);
		//southBound.addIntersections(intersections);
		//eastBound.addIntersections(intersections);
		//westBound.addIntersections(intersections);

}

void Road::advanceRoad(){
   //calls advanceLane on each lane- this takes care of straight movement and will return values for lane to do right turns
	
    for(int i = 0; i < 4; i++)
    {
        laneVec[i].advanceLane();
    }
    //northBound.advanceLane();
	//southBound.advanceLane();
	//eastBound.advanceLane();
	//westBound.advanceLane();

   //call the appropriate methods for right turns to occur for all lanes- only lanes with green light should be 
   //able to turn? (are we allowing right on red?)
   if(!ewLight.getIsRed()) //if east west light is not red, these cars may be turning
   {
      cout <<"is stored vehicle null: " << (eastBound.getTurningVehicle() == nullptr) << endl;
      if (eastBound.isMakingRight())
      {
         cout <<"turning east vehicles" << endl;
         cout <<"turning vehicle: " << eastBound.getTurningVehicle()->getVehicleID() << endl;
         southBound.addAtTurnIndex(eastBound.getTurningVehicle());

         eastBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
         eastBound.setMakingRight(false);
      }
      if (westBound.getTurningVehicle() != nullptr)
      {
         cout <<"turning west vehicles" << endl;
         cout <<"turning vehicle: " << westBound.getTurningVehicle()->getVehicleID() << endl;
         northBound.addAtTurnIndex(westBound.getTurningVehicle()); 

         westBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
         westBound.setMakingRight(false);
      }
   }
   else //north south cars may be turning
   {
      if (northBound.getTurningVehicle() != nullptr)
      {
         cout <<"turning east vehicles" << endl;
         cout <<"turning vehicle: " << northBound.getTurningVehicle()->getVehicleID() << endl;
         eastBound.addAtTurnIndex(northBound.getTurningVehicle());
     
         northBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
         northBound.setMakingRight(false);
      }
      if (southBound.getTurningVehicle() != nullptr)
      {
         cout <<"turning east vehicles" << endl;
         cout <<"turning vehicle: " << southBound.getTurningVehicle()->getVehicleID() << endl;
         westBound.addAtTurnIndex(southBound.getTurningVehicle());
      
         southBound.setTurningVehicle(nullptr); //reset turning vehicle pointer
         southBound.setMakingRight(false);
      }
   }

    addNewVehicles();
    
   //determine if new cars will be added- calls Lane.canAddCar() method for all lanes
   //if (northBound.canNewCarCome())
   //{
      //if true, calls another method in lane which will generate random number to determine whether that particular lane 
      //(based on its param values) should add a vehicle at that clock tick
      //if (northBound.shouldNewCarCome())
      //{
         //somewhere need to use RNG to determine whether new vehicle will be car, SUV or truck 
         //We need to give the car params but this doesn't currently have access- we should think about how we are using params
         //northBound.addVehicle(VehicleBase (VehicleType::car, Direction::north, params)); //adds newly generated vehicle to lane and vector of vehicles and increments vehicle count
      	//                       ^^^^^^^^^^^^^^^^^^^^^^^ needs to be a pointer		
      //}
   //} //else does not add car

   ewLight.update();
   nsLight.update();
}

void Road::addNewVehicles()
{
    double randNum;
    for(int i = 0; i < 4; i ++)
    {
        randNum = Random::generateNum();
        if(laneVec[i].canNewCarCome() && (probNewVehicle[i] < randNum))
        {
            addVehicle(genNewVehicle(laneVec[i].getDirection()), laneVec[i].getDirection());
        }
    }
}

VehicleBase* Road::genNewVehicle(Direction dir)
{
    double randNum = Random::generateNum();
    VehicleType t;
    
    if(probVehicleType[1] < randNum)
    {
        t = VehicleType::car;
    }
    else if ((probVehicleType[1] = probVehicleType[2]) < randNum)
    {
        t = VehicleType::suv;
    }
    else
    {
        t = VehicleType::truck;
    }
    
    VehicleBase* v = new VehicleBase(t,dir,param); //needs to be dynamically allocated
    //                                     ^^^^^^^ params is not in scope

    return v;
}

//could just pass in the lane itself rather than the direction of the lane
void Road::addVehicle(VehicleBase* vehicle, Direction type){

	switch(type){

		case Direction::north : northBound.addVehicle(vehicle);
			break;
		case Direction::south : southBound.addVehicle(vehicle);
			break;
		case Direction::east : eastBound.addVehicle(vehicle);
			break;
		case Direction::west : westBound.addVehicle(vehicle);
			break;
	}
        
        vehicleCount++;
}



//maybe clock tick will occur in driver 
