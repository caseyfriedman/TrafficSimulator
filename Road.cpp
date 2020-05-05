#include "Road.h"
#include <iostream>
using namespace std;


Road::Road(){

	
}

Road::Road(Parameters params) : nsLight(LightDirection::NS, params),
ewLight(LightDirection::EW,params), northBound(params, Direction::north, 
	&nsLight), southBound(params, Direction::south, &nsLight), eastBound(
	params, Direction::east, &ewLight), westBound(params, Direction::west,
	&ewLight){

        probNewVehicle.push_back(params.get_prob_new_vehicle_northbound());
        probNewVehicle.push_back(params.get_prob_new_vehicle_southbound());
        probNewVehicle.push_back(params.get_prob_new_vehicle_eastbound());
        probNewVehicle.push_back(params.get_prob_new_vehicle_westbound());

        probVehicleType.push_back(params.get_proportion_of_cars());
        probVehicleType.push_back(params.get_proportion_of_SUVs());

        probRightTurn.push_back(params.get_proportion_right_turn_cars());
        probRightTurn.push_back(params.get_proportion_right_turn_SUVs());
        probRightTurn.push_back(params.get_proportion_right_turn_trucks());

        setIntersections();

        laneVec.push_back(&northBound);
        laneVec.push_back(&southBound);
        laneVec.push_back(&eastBound);
        laneVec.push_back(&westBound);

	setLanes();

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

		northBound.addIntersections(intersections);
		southBound.addIntersections(intersections);
		eastBound.addIntersections(intersections);
		westBound.addIntersections(intersections);

}

void Road::advanceRoad(){
   //calls advanceLane on each lane- this takes care of straight movement and will return values for lane to do right turns
	northBound.advanceLane();
	southBound.advanceLane();
	eastBound.advanceLane();
	westBound.advanceLane();

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

   //determine if new cars will be added- calls Lane.canAddCar() method for all lanes
   addNewVehicles();

   ewLight.update();
   nsLight.update();
}

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

void Road::addNewVehicles()
{
    double randNum;
    for(int i = 0; i < 4; i ++)
    {
        randNum = Random::generateNum();
        if(laneVec[i]->canNewCarCome() && (probNewVehicle[i] < randNum))
        {
            laneVec[i]->addVehicle(genNewVehicle(laneVec[i]->getDirection()));
        }
    }
}

VehicleBase* Road::genNewVehicle(Direction dir)
{
    double randNum = Random::generateNum();
    VehicleType t;

    if(probVehicleType[0] < randNum)
    {
        t = VehicleType::car;
    }
    else if ((probVehicleType[0] = probVehicleType[1]) < randNum)
    {
        t = VehicleType::suv;
    }
    else
    {
        t = VehicleType::truck;
    }

    VehicleBase* v = new VehicleBase(t, dir); //needs to be dynamically allocated
    
    randNum = Random::generateNum();
    switch(t)
    {
       case VehicleType::car: 
         {
            if (probRightTurn[0] <= randNum)
            {
               v->setRightTurn();
            }
            break;
         }
       case VehicleType::suv: 
         {
            if (probRightTurn[1] <= randNum)
            {
               v->setRightTurn();
            }
            break;
         }
       case VehicleType::truck: 
         {
            if (probRightTurn[2] <= randNum)
            {
               v->setRightTurn();
            }
            break;
         }
    }    

    return v;
}


//maybe clock tick will occur in driver 
