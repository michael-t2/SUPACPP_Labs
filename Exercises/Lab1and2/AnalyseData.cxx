#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "CustomFunctions.h"


int main(){

    std::cout << "How mnay lines to read in?" << std::endl;
    std:: string user_input;
    std::cin >> user_input;
    int N = std::stoi(user_input);

    std::string input_file = "input2D_float.txt";
    std::ifstream datafile(input_file);
    std::vector<float> coords;
    std::vector<float> mags;

    std::cout << "Printing data file up to line " << N << std::endl;
    coords = read_in_coords(input_file, N);
    std::cout << "Printing magnitudes up to line " << N << std::endl;
    
    mags = calculate_magnitudes(coords);
    print_vals(mags);

    fit_line(datafile);

    float output = recur_xy(2,0.5);
    std::cout << output << std::endl;

    return 0;
}
