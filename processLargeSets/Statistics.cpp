#include "stdafx.h"
#include "Statistics.h"
#include <algorithm>
#include <boost/math/special_functions/erf.hpp>
#include <boost/math/distributions/normal.hpp>

using namespace std;

/*
* Default constructor
**/
Statistics::Statistics(){

};

double Statistics::average(vector<double> pData){

  double average = 0.0;
  int i;

  for(i = 0; i < (int)pData.size(); i++)
  {
    average += pData.at(i);
  }

  average = average/(i);
  return(average);
} 

double Statistics::median(vector<double> pData){
    
  double median = 0.0;
  int middle = 0;

  sort(pData.begin(),pData.end());

  // Accessor for middle value in the array
  middle = (int)pData.size() / 2;

  // Determines if there are an odd or even number of variables and calcuates median appropriately.
  if((int)pData.size() % 2 > 0)
    median = (pData.at(middle) + pData.at(middle+1)) / 2;
  else
    median = pData.at(middle);
  
  return median;
}

double Statistics::standardDeviation(vector<double> pData){

  double standardDeviation = 0.0;
  int i;
  double mean = average(pData);

  for(i = 0; i < (int)pData.size(); i++)
  {
    standardDeviation += pow(pData.at(i) - mean, 2);
  }

  standardDeviation = sqrt(standardDeviation / ( i - 1));
  
  return(standardDeviation);
}

double Statistics::standardDeviationTwoMeans(vector<double> pData1, vector<double> pData2){

  double variance1 = 0.0;
  double variance2 = 0.0;
  int i;
  double mean1 = average(pData1);
  double mean2 = average(pData2);

  for(i = 0; i < (int)pData1.size(); i++)
  {
    variance1 += pow(pData1.at(i) - mean1, 2);
    variance2 += pow(pData2.at(i) - mean2, 2);
  }

  double standardDeviation = sqrt((variance1 / ( i - 1)) + (variance2 / (i - 1)));
  
  return(standardDeviation);
}


// Returns the lower bound for a 95% confidence interval around the mean.
double Statistics::lowerBound(vector<double> pData){
  
  double stdDev = standardDeviation(pData);
  double mean = average(pData);
  double lowerBound = mean - ( 1.96 * stdDev );

  return lowerBound;
}


// Returns the upper bound for a 95% confidence interval around the mean.
double Statistics::upperBound(vector<double> pData){
  
  double stdDev = standardDeviation(pData);
  double mean = average(pData);
  double upperBound = mean + ( 1.96 * stdDev );

  return upperBound;
}

double Statistics::lowerBoundBootstrap(vector<double> pData, double populationVariable){
  double z = calculateProbit(pData, populationVariable);
  double a = calculateA(pData, populationVariable);
  double lower = z + ((z - 1.64)/(1 - a * (z - 1.64)));
  boost::math::normal norm;
  double a1 = boost::math::cdf(norm, lower);
  a1 *= 999.0;
  return pData[a1];
};

double Statistics::upperBoundBootstrap(vector<double> pData, double populationVariable){
  double z = calculateProbit(pData, populationVariable);
  double a = calculateA(pData, populationVariable);
  double upper = z + ((z + 1.64)/(1 - a * (z + 1.64)));
  boost::math::normal norm;
  double a2 = boost::math::cdf(norm, upper);
  a2 *= 999;
  return pData[a2];
};

double Statistics::calculateProbit(vector<double> pData, double populationVariable){
  // Loop through the vector to determine how T*
  double i = 0.0;  
  while(pData.at(i) < populationVariable)
    i++;

  double p = i/1000.0;
  double probit = pow(2, .5) * (boost::math::erf_inv(2 * p - 1));
  return probit;
};

double Statistics::calculateA(vector<double> pData, double populationVariable){
  
  double topSum = 0;
  double bottomSum = 0;
  double mean = average(pData);

  for(int i = 0; i < (int)pData.size(); i++){
    vector<double> pData_i = pData;
    double i_thPoint = pData_i.at(i);
    pData_i.erase(pData_i.begin() + i);
    double mean_i = average(pData_i);
    topSum += i_thPoint - mean_i;
    bottomSum += i_thPoint - (mean_i * mean_i);
  }

  double top = pow(topSum, 3);
  double bottom = 6 * pow(bottomSum, 3/2);

  double a = top/bottom;
  return a;
};

/*
* Default destructor
**/
Statistics::~Statistics(){
};