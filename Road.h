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

		vector<VehicleBase> allcars;	//might be handled by driver so could be deleted???
		int vehicleCount;
		vector<Section*> intersections;

	public:
		int roadSize;
		
        Road();
        Road(Parameters params);
        void setLanes();
		void advanceRoad();
		void addVehicle(VehicleBase* vehicle, Direction type);
		void setIntersections();
		void moveTraffic(int currentTime);
        void addNewVehicles();
        VehicleBase* genNewVehicle(Direction dir);
		int getVehicleCount(){return allcars.size();}
		TrafficLight nsLight;
		TrafficLight ewLight;
		Lane northBound;
		Lane southBound;
		Lane eastBound;
		Lane westBound;
        vector<Lane> laneVec;
        vector<double> probNewVehicle;
        vector<double> probVehicleType;

};
#endif
