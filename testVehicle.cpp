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
#include "Lane.h"
#include <string>
#include "Road.h"
#include "Random.h"

int main ()
{
   std::cout << "Parameter read in" << std::endl;
   Parameters params("inputFile.txt");
   std::cout << "Prop. of turn cars:" << params.get_proportion_right_turn_cars() << std::endl;
   std::cout << "Prop. of turn SUVs:" << params.get_proportion_right_turn_SUVs() << std::endl;
   std::cout << "Prop. of turn trucks:" << params.get_proportion_right_turn_trucks() << std::endl;

   //set initial seed for RNG
   Random::setSeed(1);

   std::cout << "Testing VehicleBase" << std::endl;
   std::cout << "Creating objects...   " << std::endl;
   VehicleBase v1(VehicleType::car, Direction::east, params);
   VehicleBase v2(VehicleType::suv, Direction::west, params);
   VehicleBase v3(VehicleType::truck, Direction::east, params);

   v1.getVehicleType();
   v2.getVehicleOriginalDirection();
   std::cout << "Vehicle count:" << v1.vehicleCount << std::endl;

   std::cout << "Vehicle size (car): " << v1.getVehicleSize() << std::endl;
   std::cout << "Vehicle size (suv): " << v2.getVehicleSize() << std::endl;
   std::cout << "Vehicle size (truck): " << v3.getVehicleSize() << std::endl;

   std::cout << "Vehicle turn (car): " << v1.getTurn() << std::endl;
   std::cout << "Vehicle turn (suv): " << v2.getTurn() << std::endl;
   std::cout << "Vehicle turn (truck): " << v3.getTurn() << std::endl;
 
   std::cout << "Testing Section" << std::endl;  


   Section sec1(&v1);
   Section sec2(&v2);
   Section sec3(&v3);


   std::cout << "Section count:" << sec1.getNumOfSecs() << std::endl;
   std::cout << "Is section intersection: " << sec1.isIntersection() << std::endl;
   sec1.setIntersection();
   std::cout << "Is section intersection: " << sec1.isIntersection() << std::endl;

   std::cout << "Testing TrafficLight" << std::endl;
   TrafficLight lightEW(LightDirection::EW, params);
   TrafficLight lightNS(LightDirection::NS, params);
   std::cout << "Is light EW red: " << lightEW.getIsRed() << std::endl;
   std::cout << "Is light NS red: " << lightNS.getIsRed() << std::endl;
   for (int i=0; i<=20; i++)
   {
      lightEW.update();
      //lightNS.update();
      std::cout << "EW light" << lightEW.getIsRed() << std::endl;
      //std::cout << "NS light" << lightNS.getIsRed() << std::endl;
   }

   std::cout << "Testing Lane" << std::endl;
   vector<Section*> intersections;

   Section intersec0;
   Section intersec1;
   Section intersec2;
   Section intersec3;

   intersec0.setIntersection(); 
   intersec1.setIntersection();
   intersec2.setIntersection();
   intersec3.setIntersection();

/*
intersection[0] = NE
intersection[1] = NW;
intersection[2] = SE
intersection[3] = SW
*/
   intersections.push_back(&intersec0); 
   intersections.push_back(&intersec1);
   intersections.push_back(&intersec2);
   intersections.push_back(&intersec3);

//lightEW.setTimeUntilRed(7);
Lane testLaneEast(params, Direction::north,&lightEW);
testLaneEast.addIntersections(intersections);

v1.setVehicleID(420);
std::cout << v1.getVehicleID() << std::endl;

Lane testLaneNorth(params, Direction::north, &lightNS);
testLaneNorth.addIntersections(intersections);

//add vehicles
testLaneNorth.addVehicle(&v1);
testLaneEast.addVehicle(&v2);

vector<Section*> laneE = testLaneEast.getLane();
//vector<Section*> laneN = testLaneNorth.getLane();

//check that the vehichles initial poisitioning and size is correct
for (int i=0; i < laneE.size();i++)
{
   std::cout << "The value in section " << i << " is" << laneE[i]->isOccupied() << std::endl;
}
/*
for (int i=0; i < laneN.size();i++)
{
   std::cout << "The value in section " << i << " is" << laneN[i]->isOccupied() << std::endl;
}
*/
//move the vehicle through lane
for (int i=0; i<9; i++)
{
   testLaneEast.advanceLane();
   lightEW.update();
   //lightNS.update();
}

//determine behavior here- vehicles do not seem to be moving correctly
for (int i=0; i < laneE.size();i++)
{
   std::cout << "The value in section " << i << " is" << laneE[i]->isOccupied() << std::endl;
}
//check they all share the ID correctly
//std::cout << "The ID in section " << 8 << " is" << laneE[8]->getVehicle().getVehicleID() << std::endl;
//std::cout << "The ID in section " << 9 << " is" << laneE[9]->getVehicle().getVehicleID() << std::endl;
//std::cout << "The ID in section " << 10 << " is" << laneE[10]->getVehicle().getVehicleID() << std::endl;

//check if new vehicle is allowed, add it
   std::cout << "Can new car come: " << testLaneEast.canNewCarCome() << std::endl;

   testLaneEast.addVehicle(&v3);

//new truck should be in first few spots
for (int i=0; i < laneE.size();i++)
{
   std::cout << "The value in section " << i << " is" << laneE[i]->isOccupied() << std::endl;
}
//check they all share the ID correctly
//std::cout << "The ID in section " << 0 << " is" << laneE[0]->getVehicle().getVehicleID() << std::endl;
//std::cout << "The ID in section " << 1 << " is" << laneE[1]->getVehicle().getVehicleID() << std::endl;
//std::cout << "The ID in section " << 2 << " is" << laneE[2]->getVehicle().getVehicleID() << std::endl;
//std::cout << "The ID in section " << 3 << " is" << laneE[3]->getVehicle().getVehicleID() << std::endl;

//lightEW.setTimeUntilRed(3);
//move 2 vehicles
for (int i=0; i<10; i++)
{
   testLaneEast.advanceLane();
   lightEW.update();
   //lightNS.update();
}

for (int i=0; i < laneE.size();i++)
{
   std::cout << "The value in section " << i << " is" << laneE[i]->isOccupied() << std::endl;
}

std::cout << "************* VISIUAL BREAKUP AFTER LANE TESTS *************" << std::endl;

   std::cout << "Testing Road" << std::endl;

   Road testRoad(params); //can't do default constructor for road 


//testRoad.addVehicle(&v3, Direction::north);
  testRoad.addVehicle(&v3, Direction::east);
  // testRoad.addVehicle(&v, Direction::west);
   //testRoad.addVehicle(&v2, Direction::south);


  // std::cout << "ew light " << testRoad.ewLight.getIsRed() << std::endl;
  // std::cout << "ns light " << testRoad.nsLight.getIsRed() << std::endl;
  // testRoad.addVehicle(&v1, Direction::north);
   testRoad.addVehicle(&v3, Direction::east);
   //testRoad.addVehicle(&v1, Direction::east);

for (int i=0; i<7; i++){
   testRoad.advanceRoad();
} 
for (int i=0; i < testRoad.northBound.getLane().size();i++)
{

   std::cout << "The value in section of N " << i << " is" << testRoad.northBound.getLane()[i]->isOccupied() << std::endl;
}
     
  for (int i=0; i < testRoad.eastBound.getLane().size();i++)
{

   std::cout << "The value in section of E" << i << " is" << testRoad.eastBound.getLane()[i]->isOccupied() << std::endl;
}

 for (int i=0; i < testRoad.southBound.getLane().size();i++)
{

   std::cout << "The value in section of S" << i << " is" << testRoad.southBound.getLane()[i]->isOccupied() << std::endl;
}

for (int i=0; i < testRoad.westBound.getLane().size();i++)
{

   std::cout << "The value in section of W" << i << " is" << testRoad.westBound.getLane()[i]->isOccupied() << std::endl;
}

testRoad.addVehicle(&v1, Direction::east);

for (int i=0; i<7; i++){
   testRoad.advanceRoad();
}
for (int i=0; i < testRoad.northBound.getLane().size();i++)
{

   std::cout << "The value in section of N " << i << " is" << testRoad.northBound.getLane()[i]->isOccupied() << std::endl;
}

  for (int i=0; i < testRoad.eastBound.getLane().size();i++)
{

   std::cout << "The value in section of E" << i << " is" << testRoad.eastBound.getLane()[i]->isOccupied() << std::endl;
}

 for (int i=0; i < testRoad.southBound.getLane().size();i++)
{

   std::cout << "The value in section of S" << i << " is" << testRoad.southBound.getLane()[i]->isOccupied() << std::endl;
}

for (int i=0; i < testRoad.westBound.getLane().size();i++)
{

   std::cout << "The value in section of W" << i << " is" << testRoad.westBound.getLane()[i]->isOccupied() << std::endl;
}
 


   /*

   for (int i=0; i<testRoad.northBound.getLane().size();i++){

      if(testRoad.northBound.getLane()[i]->isIntersection()){
         std::cout << "Intersection is " << testRoad.northBound.getLane()[i] << std::endl;
      }

   }
*/



   return 0;
}

