#ifndef ROAD_H
#define ROAD_H

#include "Section.h"
#include "Lane.h"
#include "Parameters.h"
#include "TrafficLight.h"
#include "Random.h"
#include <vector>
using namespace std;

class Road
{
	private:
		Section neIntersection;
		Section nwIntersection;
		Section seIntersection;
		Section swIntersection;
		Parameters param;

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
		int getVehicleCount(){return allcars.size();}
		TrafficLight nsLight;
		TrafficLight ewLight;
		TrafficLight getNsLight(){return nsLight;}
		TrafficLight getEwLight(){return ewLight;}
		Lane northBound;
		Lane southBound;
		Lane eastBound;
		Lane westBound;
                vector<Lane*> laneVec;
                vector<double> probNewVehicle;
                vector<double> probVehicleType;
                vector<double> probRightTurn;
                VehicleBase* genNewVehicle(Direction dir);
                       void addNewVehicles();


};
#endif
