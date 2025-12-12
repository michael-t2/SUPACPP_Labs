#include "FiniteFunctions.h"
#include <vector>
#pragma once

const double e = 2.71828;
const double pi = 3.14159;


class FiniteNormal : public FiniteFunction{

    public:
    FiniteNormal();
    FiniteNormal(double range_min, double range_max, double mu, double sigma, std::string outfile);

    double mu; // the mean of the normal distribution
    double sigma; // the standard deviation of the normal distribution

    void printInfo();
    double callFunction(double x);

    private:
    double norm_x(double x);



};

class FiniteCL : public FiniteFunction{

    public:
    FiniteCL();
    FiniteCL(double range_min, double range_max, double Gamma, double X_0, std::string outfile);

    double gamma;
    double x_0;

    void printInfo();
    double callFunction(double x);

    private:
    double cauchyLorentz(double x);



};

class FiniteCB : public FiniteFunction{

    public:
    FiniteCB();
    FiniteCB(double range_min, double range_max, double sigma, double mu, double n, double alpha, std::string outfile);

    double alpha;
    double n;
    double mu; 
    double sigma;


    void printInfo();
    double callFunction(double x);

    private:
    double crystalBall(double x);
    void Calculate_coeffs();
    double erf(double z, double NDiv);

    double A;
    double B;
    double C;
    double D;
    double N;



};