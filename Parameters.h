/**

Created by Casey, Mikaela, and Aidan

5/5/20

Parameter constructor takes in the file name.

Parameters parameters("input_file_format.txt");

*/

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Parameters
{

private:
    vector<string> params;
public:
    Parameters();
    Parameters(string filename);

    int get_max_simulated_time();

    int get_number_of_sections_before_intersection();

    int get_green_north_south();

    int get_yellow_north_south();

    int get_green_east_west();

    int get_yellow_east_west();

    double get_prob_new_vehicle_northbound();

    double get_prob_new_vehicle_southbound();

    double get_prob_new_vehicle_eastbound();

    double get_prob_new_vehicle_westbound();

    double get_proportion_of_cars();

    double get_proportion_of_SUVs();

    double get_proportion_right_turn_cars();

    double get_proportion_left_turn_cars();

    double get_proportion_right_turn_SUVs();

    double get_proportion_left_turn_SUVs();

    double get_proportion_right_turn_trucks();

    double get_proportion_left_turn_trucks();

    int compute_total_size();

    void error(std::string msg, string filename);

};

#endif





