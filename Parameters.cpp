/**

Created by Casey, Mikaela, and Aidan

5/5/20

Parameter constructor takes in the file name.

Parameters parameters("input_file_format.txt");

*/


#include "Parameters.h"


Parameters::Parameters()
{
}


Parameters::Parameters(string filename)
{
    ifstream infile {filename};
    if (!infile)
    {
        error("Unable to open file: ", filename);

    }

    string next;
    string param;

    while(!infile.eof())
    {
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

int Parameters::get_max_simulated_time()
{

    return stoi(params[0]);
}

int Parameters::get_number_of_sections_before_intersection()
{


    return stoi(params[1]);

}

int Parameters::get_green_north_south()
{

    return stoi(params[2]);
}

int Parameters::get_yellow_north_south()
{

    return stoi(params[3]);

}

int Parameters::get_green_east_west()
{

    return stoi(params[4]);

}

int Parameters::get_yellow_east_west()
{

    return stoi(params[5]);

}

double Parameters::get_prob_new_vehicle_northbound()
{

    return stod(params[6]);

}


double Parameters::get_prob_new_vehicle_southbound()
{

    return stod(params[7]);

}


double Parameters::get_prob_new_vehicle_eastbound()
{

    return stod(params[8]);

}

double Parameters::get_prob_new_vehicle_westbound()
{

    return stod(params[9]);

}


double Parameters::get_proportion_of_cars()
{
    return stod(params[10]);
}

double Parameters::get_proportion_of_SUVs()
{
    return stod(params[11]);
}

double Parameters::get_proportion_right_turn_cars()
{
    return stod(params[12]);
}

double Parameters::get_proportion_left_turn_cars()
{
    return stod(params[13]);
}

double Parameters::get_proportion_right_turn_SUVs()
{
    return stod(params[14]);
}

double Parameters::get_proportion_left_turn_SUVs()
{
    return stod(params[15]);
}

double Parameters::get_proportion_right_turn_trucks()
{
    return stod(params[16]);
}

double Parameters::get_proportion_left_turn_trucks()
{
    return stod(params[17]);
}


int Parameters::compute_total_size()
{
    int sections_before_intersection = stoi(params[1]);

    int total_sections = (sections_before_intersection * 2) + 6;

    return total_sections;

}


void Parameters::error(std::string msg, string filename)
{
    std::cerr << msg << filename << std::endl;
    exit(0);
}







