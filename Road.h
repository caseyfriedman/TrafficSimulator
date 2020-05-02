#ifndef ROAD_H
#define ROAD_H

#include "Section.h"
#include "Lane.h"
#include "Parameters.h"
#include "TrafficLight.h"
#include <vector>
using namespace std;

class Road
{
	private:
		Section neIntersection;
		Section nwIntersection;
		Section seIntersection;
		Section swIntersection;
		Lane northBound;
		Lane southBound;
		Lane eastBound;
		Lane westBound;
		TrafficLight nsLight;
		TrafficLight ewLight;
		vector<VehicleBase> allcars;	
		int vehicleCount;
		vector<Section*> intersections;
	public:
		int roadSize;
		void setLanes();
		Road();
		Road(Parameters params);
		vector<Section*> setIntersections();
		void moveTraffic(int currentTime);
		int getVehicleCount(){return allcars.size();}
		


};
#endif
