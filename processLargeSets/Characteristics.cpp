#include "stdafx.h"
#include "Characteristics.h"
#include <math.h>
#include <vector>


using namespace std;
  Characteristics::Characteristics(){
    
    };

  // Intialize sample pathway characteristics.
  Characteristics::Characteristics(int pFireOfInterest, int pPathway, int pAction, int pYear, int pCallFarsite, 
    double pSuppression, double pTimberLoss, double pErc, double pSc, double pArea){

    fireOfInterest = pFireOfInterest;
    pathway = pPathway;
    action = pAction;
    year = pYear;
    callFarsite = pCallFarsite;
    suppression = pSuppression / pow(1.04, year);
    timberLoss = pTimberLoss / pow(1.04, year);
    valueChange = suppression + timberLoss;
    foiErc = pErc;
    foiSc = pSc;
    foiSize = pArea;
    if(year != 0)
      futureSuppression = suppression;
    else
      futureSuppression = 0;
  };

  // Initialize pair characteristics
  Characteristics::Characteristics(int pFoi, int pPathway, double pDifferenceSuppress, double pDifferenceTimberLoss, double pDifferenceTotal){
    fireOfInterest = pFoi;
    pathway = pPathway;
    suppressionCostSavings = pDifferenceSuppress;
    timberLossSavings = pDifferenceTimberLoss;
    totalCostPlusNVC = pDifferenceTotal;
  };

  void Characteristics::updateFoiValues(){
    averageBenefit += suppressionCostSavings;
    standardDeviationBenefit;
    averageLoss += timberLossSavings;
    standardDeviationLoss;

  };

  // Initialize yearly characteristics
  Characteristics::Characteristics(int pYear, int pAction, double pErc, double pSc, double pNumIgnitions,
    double pCrownFire, double pSurfaceFire, double pSuppression, double pTimberLoss){

    year = pYear;
    action = pAction;
    erc = pErc;
    sc = pSc;
    numIgnitions = pNumIgnitions;
    crownFire = pCrownFire;
    surfaceFire = pSurfaceFire;
    area = crownFire + surfaceFire;
    suppression = pSuppression / pow(1.04, year);      
    timberLoss = pTimberLoss / pow(1.04, year);
    valueChange = suppression + timberLoss;
    pathYears = 1;
  };


  /*
  * Totals the suppression costs, timber losses, and value changes
  * for a sample pathway.
  **/
  void Characteristics::updateValue(Characteristics temp){
    suppression += temp.suppression;
    futureSuppression += temp.futureSuppression;
    timberLoss += temp.timberLoss;
    valueChange += temp.valueChange;
    return;
  };

void Characteristics::initializeYearlyTotals(){
  totalErc = erc;
  totalSc = sc;
  totalNumIgnitions = numIgnitions;
  totalCrownFire = crownFire;
  totalSurfaceFire = surfaceFire;
  totalArea = totalCrownFire + totalSurfaceFire;
  totalSuppression = suppression;
  totalTimberLoss = timberLoss;
  pathYears = 1;
  
};

void Characteristics::setYearlyAverageValues(){
  erc = totalErc / pathYears;
  sc = totalSc / pathYears;
  numIgnitions = totalNumIgnitions / pathYears;
  crownFire = totalCrownFire / pathYears;
  surfaceFire = totalSurfaceFire / pathYears;
  area = crownFire + surfaceFire;
  suppression = totalSuppression / pathYears;
  timberLoss = totalTimberLoss / pathYears;
  valueChange = suppression + timberLoss;
};

void Characteristics::totalYearlyValues(Characteristics temp){
  totalErc += temp.erc;
  totalSc += temp.sc;
  totalNumIgnitions += temp.numIgnitions;
  totalCrownFire += temp.crownFire;
  totalSurfaceFire += temp.surfaceFire;
  totalArea += totalCrownFire + temp.totalSurfaceFire;
  totalSuppression += temp.suppression;
  totalTimberLoss += temp.timberLoss;
  pathYears += 1;
};

double calculateSDSuppression(vector<Characteristics> standardDeviationData){

  vector<double> dataset;
  Statistics getStats;
  for(int i = 0; i < (int)standardDeviationData.size(); i ++)
  {
    dataset.push_back(standardDeviationData.at(i).getSuppressionCostSavings());
  }

  double sD = getStats.standardDeviation(dataset);
  return(sD);
  
};

double calculateSDTimberLoss(vector<Characteristics> standardDeviationData){

  vector<double> dataset;
  Statistics getStats;
  for(int i = 0; i < (int)standardDeviationData.size(); i ++)
  {
    dataset.push_back(standardDeviationData.at(i).getTimberLossSavings());
  }

  double sD = getStats.standardDeviation(dataset);
  return(sD);
};

void Characteristics::printAverageValues(FILE * yearOutput){
  setYearlyAverageValues();
  fprintf_s(yearOutput, "%d %d %lf %lf %lf %lf %lf %lf %lf %lf \n", year, action,
    erc, sc, numIgnitions, crownFire, surfaceFire, area, suppression, timberLoss);
};

void Characteristics::printPairValues(FILE * pairOutput){
  fprintf_s(pairOutput, "%d %d %lf %lf %lf\n", fireOfInterest, pathway, suppressionCostSavings, 
    timberLossSavings, totalCostPlusNVC);
};


int Characteristics::getFireOfInterest(){
  return fireOfInterest;
};

int Characteristics::getPathway(){
  return pathway;  
};
  
int Characteristics::getAction(){
  return action;
};
  
int Characteristics::getYear(){
  return year;
};

double Characteristics::getSuppress(){
  return suppression;
};

double Characteristics::getFutureSuppress(){
  return futureSuppression;
};

double Characteristics::getTimberLoss(){
  return timberLoss; 
};

double Characteristics::getValueChange(){
  return valueChange; 
};

double Characteristics::getFOIErc(){
  return foiErc;
};
  
double Characteristics::getFOISc(){
  return foiSc;
};
  
double Characteristics::getFOISize(){
  return foiSize;
};
  
double Characteristics::getSuppressionCostSavings(){
  return suppressionCostSavings;
};

double Characteristics::getTimberLossSavings(){
  return timberLossSavings;
};

double Characteristics::getTotalCostPlusNVC(){
  return totalCostPlusNVC;
};

void Characteristics::setSuppress(double pSupress){
  suppression = pSupress;
};

void Characteristics::setFutureSuppress(double pFutureSuppress){
  futureSuppression = pFutureSuppress;
};

void Characteristics::setTimberLoss(double pTimber){
  timberLoss = pTimber;
};

/**
* @brief Destructor
*/
Characteristics::~Characteristics(){
};

