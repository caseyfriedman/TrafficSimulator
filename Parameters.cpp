#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Parameters{


	public:
		vector<string> params;	



Parameters(std::ifstream &infile){

string next;
string param;
	while(!infile.eof()){
		
	infile >> next;
	infile >> param;
	params.push_back(param);

	}

	/**
	string param;
	string next;

	infile >> maximum_simulated_time;
	infile >> next;
	infile >> green_north_south;
*/
}

int get_max_simulated_time(){

	return stoi(params[0]);
}

int get_number_of_sections_before_intersection(){

	
	return stoi(params[1]);

}

int get_green_north_south(){

	return stoi(params[2]);
}

int get_yellow_north_south(){

	return stoi(params[3]);

}

int get_green_east_west(){
	
	return stoi(params[4]);

}

int get_yellow_east_west(){

	return stoi(params[5]);

}

double get_prob_new_vehicle_northbound(){

	return stod(params[6]);

}


double get_prob_new_vehicle_southbound(){

	return stod(params[7]);

}


double get_prob_new_vehicle_eastbound(){

	return stod(params[8]);
		
}

double get_prob_new_vehicle_westbound(){

	return stod(params[9]);

}


double get_proportion_of_cars(){
	return stod(params[10]);
}

double get_proportion_of_SUVs(){
	return stod(params[11]);
}

double get_proportion_right_turn_cars(){
	return stod(params[12]);
}

double get_proportion_left_turn_cars(){
	return stod(params[13]);
}

double get_proportion_right_turn_SUVs(){
	return stod(params[14]);
}

double get_proportion_left_turn_SUVs(){
	return stod(params[15]);
}

double get_proportion_right_turn_trucks(){
	return stod(params[16]);
}

double get_proportion_left_turn_trucks(){
	return stod(params[17]);
}

};

int main(int argc, char *argv[])
{

	
ifstream infile {argv[1]};

Parameters parameters(infile);

cout << parameters.get_proportion_left_turn_SUVs() << endl;

return 0;
}







