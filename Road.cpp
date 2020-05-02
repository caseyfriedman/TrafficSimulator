#include "Road.h"
#include <iostream>
using namespace std;


Road::Road(){

	
}

Road::Road(Parameters params) : nsLight(LightDirection::NS, params),
ewLight(LightDirection::EW,params), northBound(params, Direction::north, 
	&nsLight), southBound(params, Direction::south, &nsLight), eastBound(
	params, Direction::east, &ewLight), westBound(params, Direction::east,
	&ewLight){

	intersections = setIntersections();

	setLanes();









}


vector<Section*> Road::setIntersections(){
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

void Road::advanceLanes(){


	northBound.advanceLane();
	southBound.advanceLane();
	eastBound.advanceLane();
	westBound.advanceLane();

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