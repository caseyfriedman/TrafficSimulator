# cmsc240_s2020_final_juliet

This is a traffic simulator that simulates a 4 way traffic light. 
Created by Aidan Bond, Casey Friedman, Mikaela Rosen
5/5/20

## Usage

To compile, run the command:
% make


To run this file, use:
% ./Driver [input file] [initial seed]

where [input file] is a txt file with 18 lines, two columns each. The second column must be numbers.


[initial seed] can be any number and is used for the mersenne twister random number generator.


## Design

Vehicles are all type VehicleBase. The only difference between types is the size, which is set in the constructor.

Sections contain VehicleBase pointers if occupied, and null pointers if empty. Certain sections are intersections if
they are contained in two lanes.

Lanes consist of Sections. Each lane contains a vector of Section pointers and a pointer to a corresponding TrafficLight.
Lanes have a series of methods to advance vehicles in sections once per clock tick.
Lane is responsible for vehicles going straight and stores a pointer to vehicles that are turning right to be used by road.
Intersections are pointers so they can be shared between lanes.

Road consists of Lanes and TrafficLights. The Road creates and holds the intersections for the Lanes.
Road advances by advancing each lane. Road handles right turns for the lanes and determines whether new
vehicles can be made, what type of vehicle they should be, and whether or not vehicles should turn right. 

TrafficLight has a counter that determines whether vehicles can enter the intersection.
The counter keeps track of the total time until red. It is set by the Parameters.

The Driver class runs the simulation. It is responsible for reading in the file and creating a parameter object
to be used by the other classes. It holds the instance of Road and interfaces with the Animator.