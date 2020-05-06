# cmsc240_s2020_final_juliet

This is a traffic simulator that simulates a 4 way traffic light. 
Created by Aidan Bond, Casey Friedman, Mikaela Rosen
5/5/20

CONTENTS OF THIS FILE
---------------------
* Usage Information
* Design

USAGE INFORMATION
-----------------
To compile, run the command:
% make

To run this file, use:
% ./Driver [input file] [initial seed]

[input file] is a txt file with 18 lines, two columns each. The second column must be numbers.

[initial seed] can be any number and is used for the mersenne twister random number generator.

DESIGN 
-------
All vehicles are of type VehicleBase. The only difference between each vehicle type (car, SUV and truck) is the size, which is set in the constructor. Cars are size 2, SUVs are size 3 and Trucks are size 4. The size is used to determine how much space the vehicle takes in a lane. 
Each vehicle also has ID, direction and turnRight variables that are set within the constructor. A vehicle's ID is determined based on a static vehicleCount variable. The direction corresponds to which lane it is driving and the turnRight variable corresponds to whether a vehicle is turning. The latter two values are computed and set within Road when vehicles are generated. 

Sections contain VehicleBase pointers if occupied, and null pointers if empty. Certain sections are intersections if they are contained in two lanes and must be set as intersections using a setter. 

Lanes consist of Sections. Each lane contains a vector of Section pointers and a pointer to a corresponding TrafficLight.
Lanes share intersections. Because, intersections are pointers they can be easily shared between lanes (ex: EW intersection is shared between Eastbound and Westbound lanes).
Lanes have a series of methods to advance vehicles in sections once per clock tick. Within Lanes, vehicles move section-by-section and check whether they have the ability to move. For a vehicle to move, it must have an empty section ahead of it and obey traffic laws. If the head (first portion of a given vehicle) is approaching the intersection it must check whether the light is red, and if it is not, then it is determined whether the vehicle can make it across the intersection before the light turns red. Non-head portions of cars do not need to make these decisions.
While Lane is responsible for vehicles going straight, it is not responsible for turning vehicles. Lanes are not capable of easily accessing one another so Road is responsible for the turning behavior. In Lane, if a vehicle is turning and its head is within the intersection, then its vehicle pointer is stored to be used by Road.

Road consists of Lanes and TrafficLights. The Road creates and holds the intersection objects for the Lanes.
Road advances by advancing each lane. Road handles right turns for the lanes by using the stored turning vehicles. Lane also determines whether new vehicles can be made, what type of vehicle they should be, and whether or not vehicles should turn right, based on random number generation and the parameters read in through the input file. 

TrafficLight has a counter that keeps track of the total time until red. It is set by the Parameters. 
Vehicles use the counter and methods in TrafficLight to determine whether they can enter the intersection.

The Parameters class is responsible for reading in the input file, or generating an error if the file is invalid. It provides getters for other classes to access them. The parameter object is passed into Road. 

The Random class contains an instance of a mersenne twister random number generator, a method to set the seed and a static method to generate a random number. The object of type Random is created in the driver and its seed is set based on command line input. Therefore, any methods within the simulation will be able to generate a random number with the seed already seti.  

The Driver class runs the simulation. It is responsible for reading in the file and creating a parameter object
to be used by the other classes. It holds the instance of Road and interfaces with the Animator.
