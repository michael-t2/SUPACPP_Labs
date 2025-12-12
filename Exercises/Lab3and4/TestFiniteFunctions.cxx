#include <iostream>
#include <fstream>
#include <vector> 
#include "FiniteFunctions.h"
#include "TestFiniteFunctions.h"



// int main(){
    
//     std::vector<double> mysData = readInData("./Outputs/data/MysteryData11045.txt");
//     mysData = normaliseData(mysData);
//     //printDataVals(mysData);
//     plot_data_vs_sqinv(mysData);

//     return 0;
// }

std::vector<double> normaliseData(std::vector<double> data){
    double sum=0;
    for(int i=0; i < data.size();i++){
        sum += data[i];
    }
    for(int i=0; i < data.size();i++){
        data[i]/sum;
    }
    return data;

}

void plot_data_vs_sqinv(std::vector<double> &data){
    FiniteFunction fitFunc = FiniteFunction();
    fitFunc.setRangeMin(-10);
    fitFunc.setRangeMax(10);
    fitFunc.plotFunction();
    fitFunc.plotData(data, 50);
    return;
}

std::vector<double> readInData(std::string Path){
    std::ifstream datafile(Path);
    std::string datavalue;
    std::vector<double> input_vals;
    while(std::getline(datafile,datavalue)) 
    {
        input_vals.push_back(std::stod(datavalue));
    }
    std::cout << input_vals.size() << std::endl;
    return input_vals;
}

void printDataVals(std::vector<double> &data){
    std::cout << data.size() << std::endl;
    for(int i=0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }
}