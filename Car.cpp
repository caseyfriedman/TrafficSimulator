#include "Car.h"



using namespace std;

Car::Car(int probTurnRight) : Vehicle(probTurnRight) {


	sectionsOccupied = 2;


}

int main(){

	Car tester(324);
	return 0;
}
