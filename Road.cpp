#include "Road.h"
#include <iostream>
using namespace std;


Road::Road(){

	cout<<"This is a test"<<endl;
}

Road::Road(Parameters params){

	nsLight.setValues(LightDirection::NS, params);

}
