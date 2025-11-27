#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "CustomFunctions.h"
#include "AnalyseData.h"


int main(){

    while(true)
    {
    std::cout << "what would you like to do?\n\nPress 1 to print N lines\nPress 2 to obtain N magnitudes\nPress 3 to fit a line to all data with chi^2 value\nPress 4 to do a power operation.\n\nOr press Q to quit" << std::endl;
    std:: string user_input;
    std::cin >> user_input;
    if(user_input[0] == 'Q' | user_input[0] == 'q')
    {
        break;

    }

    int N = std::stoi(user_input);

    switch (N)
    {
    case 1:
        printLines();
        break;

    case 2:
        printMags();
        break;
    case 3:
        fitLineToData();
        break;
    case 4:
        pow_recur();
        break;
    
    default:
        std::cout << "invalid choice, please select again" << std::endl;
        break;
    }
    }
    return 0;
}

float pow_recur(float x, float y)
{
    float output = recur_xy(x,y);
    std::cout << "The result is: " << output << std::endl;
    return output;
}

float pow_recur()
{  
    std::string user_input; 
    std::cout << "enter x and y as a comma separated list." << std::endl;
    std::cin >> user_input;
    float x = std::stof(user_input.substr(0, user_input.find(",")));
    float y = std::stof(user_input.substr(user_input.find(",")+1, user_input.length()));
    float output = recur_xy(x,y);
    std::cout << "The result is: " << output << std::endl;
    return output;
}

void fitLineToData()
    {
        std::ifstream datafile("input2D_float.txt");
        fit_line(datafile);

    }

int getNumLines()
{
    std::string user_input;
    std::cout << "please select a number of lines to print" << std::endl;
    std::cin >> user_input;
    int N = std::stoi(user_input);
    return N;

}

void printMags()
{
    std::string input_file = "input2D_float.txt";
    std::vector<float> mags;
    int N = getNumLines();
    std::cout << "Printing magnitudes up to line " << N << std::endl;
    mags = calculate_magnitudes(read_in_coords(input_file, N));
    print_vals(mags);
    return;

}

void printLines()
{
    std::string input_file = "input2D_float.txt";
    std::vector<float> coords;
    int N = getNumLines();
    std::cout << "Printing data file up to line " << N << std::endl;
    coords = read_in_coords(input_file, N);
    print_vals(coords,2);
    return;
}


