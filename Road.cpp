#include "Road.h"
#include <iostream>
using namespace std;


Road::Road(){

	cout<<"This is a test"<<endl;
}

Road::Road(Parameters params) : nsLight(LightDirection::NS, params),
ewLight(LightDirection::EW,params){

	setIntersections();




}


void Road::setIntersections(){
		neIntersection.setIntersection();
		nwIntersection.setIntersection();
		seIntersection.setIntersection();
		swIntersection.setIntersection();
}