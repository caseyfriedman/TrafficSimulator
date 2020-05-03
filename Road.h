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
		//
		TrafficLight nsLight;
		TrafficLight ewLight;
		vector<VehicleBase> allcars;	//might be handled by driver so could be deleted???
		int vehicleCount;
		vector<Section*> intersections;

	public:
		int roadSize;
		void setLanes();
		void advanceLanes();
		void addVehicle(VehicleBase* vehicle, Direction type);
		Road();
		Road(Parameters params);
		void setIntersections();
		void moveTraffic(int currentTime);
		int getVehicleCount(){return allcars.size();}
		
		Lane northBound;
		Lane southBound;
		Lane eastBound;
		Lane westBound;

};
#endif
