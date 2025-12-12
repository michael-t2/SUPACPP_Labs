#include "CustomFunctions.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "TestFiniteFunctions.h"




int main(){
    std::vector<double> mysData = readInData("./Outputs/data/MysteryData11045.txt");
    FiniteNormal norm = FiniteNormal();
    FiniteCL cauch = FiniteCL();
    FiniteCB crystal = FiniteCB();

    FiniteCL fitFunc = FiniteCL(-10,10,0.5,-2,"CLFitFunction");

    norm.plotFunction();
    norm.plotData(mysData, 1000);
    cauch.plotFunction();
    cauch.plotData(mysData, 1000);
    crystal.plotFunction();
    crystal.plotData(mysData, 1000);
    fitFunc.plotFunction();
    fitFunc.plotData(mysData,1000);

    std::vector<double> samples = fitFunc.metroSample(0.5,20);
    printDataVals(samples);
    return 0;
}



FiniteNormal::FiniteNormal():FiniteFunction(){
    mu = 0;
    sigma = 0.5;
    this->checkPath("NormalFunction");
}

FiniteNormal::FiniteNormal(double range_min, double range_max, double Mu, double Sigma, std::string outfile) :FiniteFunction(range_min, range_max, outfile){
    mu = Mu;
    sigma = Sigma;
    this->checkPath(outfile);
};

 void FiniteNormal::printInfo(){std::cout << "Normal (Gaussian) distribution with mean: " << mu << " and std: " << sigma << std::endl; };
 double FiniteNormal::callFunction(double x){ return norm_x(x);}; 


double FiniteNormal::norm_x(double x){
    double norm_const = 1/(sigma*pow(2*pi,0.5));

    double exponent = -0.5*pow((x - mu)/(sigma), 2);

    return norm_const*pow(e,exponent);
};

FiniteCL::FiniteCL() :FiniteFunction(){
    gamma = 0.5;
    x_0 = 0;
    this->checkPath("CauchyLorentzFunction");
}

FiniteCL::FiniteCL(double range_min, double range_max, double Gamma, double X_0, std::string outfile) :FiniteFunction(range_min, range_max, outfile) {
    FiniteFunction(range_min, range_max, outfile);
    gamma = Gamma;
    x_0 = X_0;
    this->checkPath(outfile);
    std::cout << m_RMax << std::endl;
};

 void FiniteCL::printInfo(){std::cout << "Cauchy-Lorentz distribution with gamma: " << gamma << std::endl; };
 double FiniteCL::callFunction(double x){ return cauchyLorentz(x);}; 


double FiniteCL::cauchyLorentz(double x){
    double denom = gamma*pi*(1 + pow((x-x_0)/gamma,2));
    return 1/denom;
};

FiniteCB::FiniteCB():FiniteFunction(){
    n = 1.5;
    alpha = 0.5;
    sigma = 0.5;
    mu = 0;
    Calculate_coeffs();
    this->checkPath("CrystalBallFunction");
}

FiniteCB::FiniteCB(double range_min, double range_max,double Sigma, double Mu,  double N, double Alpha, std::string outfile):FiniteFunction(range_min, range_max, outfile){
    FiniteFunction(range_min, range_max, outfile);
    n = N;
    alpha = Alpha;
    sigma = Sigma;
    mu = Mu;
    Calculate_coeffs();
    this->checkPath(outfile);

};

 void FiniteCB::printInfo(){std::cout << "Crystal Ball distribution with:" << std::endl
    <<  "n: " << n << std::endl
    << "alpha: " << alpha << std::endl
   << " Gaussian mean: " << mu << std::endl 
    << "Gaussian std: " << sigma << std::endl;  };
 double FiniteCB::callFunction(double x){ return crystalBall(x);}; 


void FiniteCB::Calculate_coeffs(){
    double e_to_al_2 = pow(e,-1*alpha*alpha/2);
    A = pow(n/alpha,n)*e_to_al_2;
    B = n/alpha - alpha;
    C =(n/alpha)*(1/(n-1))*e_to_al_2;
    D = pow(pi/2,0.5)*erf(alpha/pow(2,0.5), 1000);
    N = 1/(sigma*(C+D));
}



double FiniteCB::erf(double z, double Ndiv=1000){
  double output = 0;
  double step = (z)/Ndiv;
  for( double i = 0; i < z; i+= step){
    output += pow(e,-1*i*i)*step;
  }
  return output;  
}

double FiniteCB::crystalBall(double x){
    if(-1*(x-mu)/sigma < alpha){
        double exponent = -1*pow(x-mu,2)/(2*sigma*sigma);
        return N*(pow(e,exponent));
    }
    else{
        return N*A*(pow(B-((x-mu)/sigma),-n));
    }
};
