/**

Created by Casey

Parameter constructor takes in the file name. 

Could be command line argument later, but right now you just need to call

Parameters parameters("input_file_format.txt");

*/


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Parameters{

private:
		vector<string> params;	
public:

Parameters(string filename){


ifstream infile {filename};
if (!infile)
    {
        error("Unable to open file: ", filename);

    }


	string next;
	string param;

	while(!infile.eof()){
		
	infile >> next;
	infile >> param;
	params.push_back(param);

	}

	if (infile.fail() && !infile.eof())
    {
        std::cerr << "Error: bad file format: " << std::endl;
        std::exit(1);
    }
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



void error(std::string msg, string filename)
{
    std::cerr << msg << filename << std::endl;
    exit(0);
}

};








