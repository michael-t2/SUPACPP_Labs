#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "CustomFunctions.h"

float mag_2d(float x, float y){

    return sqrt(pow(x,2) + pow(y,2));
}

std::vector<float> read_in_coords(std::string Path, int num_to_read){
    std::vector<float> coords;
    std::string delim = ",";
    std::ifstream datafile(Path);
    std::string datavalue;

    for(int i=0; i < num_to_read+1; i++ ){
        std::string datavalue;
        std::string delim = ",";
        float x;
        float y;
        datafile >> datavalue;
        if(i == 0){
            continue;
        }
        std::cout << datavalue << std::endl; 
        x = std::stof(datavalue.substr(0, datavalue.find(delim)));
        y = std::stof(datavalue.substr(datavalue.find(delim)+1, datavalue.length()));
        coords.push_back(x);
        coords.push_back(y);
    }
    return coords;
}

std::vector<float> read_in_coords(std::ifstream &datafile){
    std::vector<float> coords;
    std::string delim = ",";
    std::string datavalue;
    int count = 0;
    int skip_rows =1;
    while(std::getline(datafile,datavalue))
    {
        if (count < skip_rows)
        {
            count++;
            continue;
        }
        coords.push_back(std::stof(datavalue.substr(0, datavalue.find(delim))));
        coords.push_back(std::stof(datavalue.substr(datavalue.find(delim)+1, datavalue.length())));
    }
    return coords;

}

void print_vals(std::vector<std::string> values){
    for(int i=0; i < values.size(); i++){
        std::cout << values[i] << std::endl;
    }
    return;
}

void print_vals(std::vector<float> values){
    for(int i=0; i < values.size(); i++){
        std::cout << values[i] << std::endl;
    }
    return;
}

std::vector<float> calculate_magnitudes(std::vector<float> coords)
{
    std::vector<float> mags;
    int N = coords.size();
    for(int i=0; i<N; i += 2){
    mags.push_back(mag_2d(coords[i], coords[i+1]));
    }
    return mags;
}

void fit_line(std::ifstream &file){

    std::vector<float> coords = read_in_coords(file);
    std::vector<float> x;
    std::vector<float> y;
    float s_xi = 0;
    float s_yi = 0;
    float s_xyi = 0;
    float s_xi2 = 0;
    int N = coords.size()/2;
    std::string outfile = "equation.txt";
    std::string errorPath = "error2D_float.txt";
    std::ifstream errorFile(errorPath);


    for(int i=0; i < coords.size(); i++){
        if(i %2 == 0){
            s_xi += coords[i];
            s_xi2 += pow(coords[i],2);
            s_xyi += coords[i] * coords[i+1];

        }
        else{
            s_yi += coords[i];
        }
    }
    float grad = (N*s_xyi - s_xi*s_yi)/(N*s_xi2 - pow(s_xi,2));
    float c = (s_xi2*s_yi - s_xyi*s_xi)/(N*s_xi2 - pow(s_xi,2));

    std::vector<float> errors = read_in_coords(errorFile);
    std::cout << "y = " << grad << "x + " << c << std::endl;
    float chi_2 = chi_2_ndof( coords, errors, grad, c);

    std::cout << "x_2 =  " << chi_2 << std::endl;
    std::ofstream outStream;
    outStream.open(outfile, std::ios::app);
    outStream << "y = " << grad << "x + " << c << std::endl;
    outStream << "x_2 =  " << chi_2 << std::endl;
    outStream.close();
    return;
}

float chi_2_ndof(std::vector<float> coords,std::vector<float> errors, float grad, float c)
{
        float chi_2 = 0;
        for(int i=0; i < coords.size(); i+= 2){
            float expec = grad*coords[i] + c;
            float err = pow(errors[i]+ errors[i+1],2);
            chi_2 += pow(coords[i+1]- expec, 2)/err;
            std::cout << pow(coords[i+1]- expec, 2)/err << std::endl;
    }

    return chi_2/(coords.size()/2 - 2);


}

std::vector<float> xpowy(std::vector<float> coords){
    std::vector<float> output;
    for(int i=0; i<coords.size(); i+=2){
        output.push_back(recur_xy(coords[i], coords[i+1]));
    }
    return output;
}

float recur_xy(float x, float y){
    if (y <= 1)
    {
        if(y < 0.5){
            return 1;
        }
        return x;
    }
    else{
        return x*recur_xy(x, y-1);
    }
}
