/* This is a tester file for the generic LinkedList class. It uses LinkedLists of object
 * types int, Student and char to test the methods in and functionality of LinkedList.
 * Author: Mikaela Rosen
 * Date: 03.29.2020
*/

#include <iostream>
#include "VehicleBase.h"
#include "Section.h"
#include "Parameters.h"
#include "TrafficLight.h"
//#include "Lane.h"
#include <string>
#include "Road.h"

int main ()
{
   std::cout << "Parameter read in" << std::endl;
   Parameters params("inputFile.txt");
   std::cout << "Prop. of turn cars:" << params.get_proportion_right_turn_cars() << std::endl;
   std::cout << "Prop. of turn SUVs:" << params.get_proportion_right_turn_SUVs() << std::endl;
   std::cout << "Prop. of turn truckss:" << params.get_proportion_right_turn_trucks() << std::endl;

   std::cout << "Testing VehicleBase" << std::endl;
   std::cout << "Creating objects...   " << std::endl;
   VehicleBase v1(VehicleType::car, Direction::east, params);
   VehicleBase v2(VehicleType::suv, Direction::west, params);
   VehicleBase v3(VehicleType::truck, Direction::north, params);

   v1.getVehicleType();
   v2.getVehicleOriginalDirection();
   std::cout << "Vehicle count:" << v1.vehicleCount << std::endl;

   std::cout << "Vehicle size (car): " << v1.getVehicleSize() << std::endl;
   std::cout << "Vehicle size (suv): " << v2.getVehicleSize() << std::endl;
   std::cout << "Vehicle size (truck): " << v3.getVehicleSize() << std::endl;

   std::cout << "Vehicle turn (car): " << v1.getTurn() << std::endl;
   std::cout << "Vehicle turn (suv): " << v2.getTurn() << std::endl;
   std::cout << "Vehicle turn (truck): " << v3.getTurn() << std::endl;
/*
   std::cout << "Testing VehicleBase" << std::endl;
   std::cout << "Creating objects...   " << std::endl;
   VehicleBase v1(VehicleType::car, Direction::east);
   VehicleBase v2(VehicleType::suv, Direction::west);
   VehicleBase v3(VehicleType::truck, Direction::north);

   v1.getVehicleType();
   v2.getVehicleOriginalDirection();
   std::cout << "Vehicle count:" << v1.vehicleCount << std::endl;

   std::cout << "Vehicle size (car): " << v1.getVehicleSize() << std::endl;
   std::cout << "Vehicle size (suv): " << v2.getVehicleSize() << std::endl;
   std::cout << "Vehicle size (truck): " << v3.getVehicleSize() << std::endl;

   std::cout << "Vehicle turn (car): " << v1.getTurn() << std::endl;
   std::cout << "Vehicle turn (suv): " << v2.getTurn() << std::endl;
   std::cout << "Vehicle turn (truck): " << v3.getTurn() << std::endl;
*/
   Section sec1(&v1);
   Section sec2(&v2);
   Section sec3(&v3);
   std::cout << "Section count:" << sec1.getNumOfSecs() << std::endl;
   std::cout << "Is section intersection: " << sec1.isIntersection() << std::endl;
   sec1.setIntersection();
   std::cout << "Is section intersection: " << sec1.isIntersection() << std::endl;

   TrafficLight lightEW(LightDirection::EW, params);
   TrafficLight lightNS(LightDirection::NS, params);
   std::cout << "Is light EW red: " << lightEW.getIsRed() << std::endl;
   std::cout << "Is light NS red: " << lightNS.getIsRed() << std::endl;
   for (int i=0; i<=50; i++)
   {
      //lightEW.update();
      //lightNS.update();
   }

   
   vector<Section*> intersections;
   intersections.push_back(&sec1);
   Lane laneNorth(8, Direction::north, intersections);


   std::cout << "************************************************"<<std::endl;

   Road road();


   return 0;
}
