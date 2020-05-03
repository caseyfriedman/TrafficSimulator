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

//determine if new cars will be added- calls Lane.canAddCar() method for all lanes
   //if true, calls another method in lane which will generate random number to determine whether that particular lane 
   //(based on its param values) should add a vehicle at that clock tick
       //adds vehicle to lane and vector of vehicles and increments vehicle count 
   //else does not add car
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

}

//maybe clock tick will occur in driver 
