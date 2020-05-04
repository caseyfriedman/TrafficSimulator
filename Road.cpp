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

	setIntersections();

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


		cout << "Set lanes is called" << endl;
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
   if (northBound.canNewCarCome())
   {
      //if true, calls another method in lane which will generate random number to determine whether that particular lane 
      //(based on its param values) should add a vehicle at that clock tick
      if (northBound.shouldNewCarCome())
      { 
         //somewhere need to use RNG to determine whether new vehicle will be car, SUV or truck 
         //We need to give the car params but this doesn't currently have access- we should think about how we are using params
         //northBound.addVehicle(VehicleBase (VehicleType::car, Direction::north, params)); //adds newly generated vehicle to lane and vector of vehicles and increments vehicle count   
      }  
   } //else does not add car

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

//maybe clock tick will occur in driver 
