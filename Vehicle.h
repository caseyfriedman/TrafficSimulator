#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle{

	public:
		Vehicle();
		Vehicle(int prob);
		int sectionsOccupied;
		int probTurnRight;
	private:
		void advance();
		void turnRight();
	



};
#endif
