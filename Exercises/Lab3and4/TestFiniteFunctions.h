#pragma once
#include <vector>


std::vector<double> readInData(std::string Path);
void plot_data_vs_sqinv(std::vector<double> &data);
std::vector<double> normaliseData(std::vector<double> data);
void printDataVals(std::vector<double> &data);