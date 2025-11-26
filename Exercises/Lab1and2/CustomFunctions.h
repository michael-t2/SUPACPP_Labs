#pragma once

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
float mag_2d(float x, float y);
void print_vals(std::vector<std::string> values);
void print_vals(std::vector<float> values);
std::vector<float> calculate_magnitudes(std::vector<float> coords);
std::vector<float> read_in_coords(std::string Path, int num_to_read);
std::vector<float> read_in_coords(std::ifstream &datafile);
void fit_line(std::ifstream &file);
float chi_2_ndof(std::vector<float> coords,std::vector<float> errors, float grad, float c);
float recur_xy(float x, float y);