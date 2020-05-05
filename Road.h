#ifndef ROAD_H
#define ROAD_H

#include "Section.h"
#include "Lane.h"
#include "Parameters.h"
#include "TrafficLight.h"
#include "Random.h"
#include <iostream>
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


		Parameters param;
		int roadSize;
		
		vector<Section*> intersections;
		
		TrafficLight nsLight;
		TrafficLight ewLight;

		vector<Lane*> laneVec;
        vector<double> probNewVehicle;
        vector<double> probVehicleType;
        vector<double> probRightTurn;
		void createVectors(Parameters params);
		void setLanes();	
		VehicleBase* genNewVehicle(Direction dir);
		void addNewVehicles();
	public:
		
		int vehicleCount; //NOT REALLY USED OTHER THAN IN TESTS
        Road();
        Road(Parameters params);
        
		void advanceRoad();
		void addVehicle(VehicleBase* vehicle, Direction type);
		void setIntersections();
		void moveTraffic(int currentTime);
		
		
		TrafficLight getNsLight(){return nsLight;}
		TrafficLight getEwLight(){return ewLight;}

		Lane getNB(){return northBound;}
		Lane getSB(){return southBound;}
		Lane getEB(){return eastBound;}
		Lane getWB(){return westBound;}

		int getRoadsize() {return roadSize + 2;}

		
                
       	
        


};
#endif
