#include "stdafx.h"
#include "Characteristics.h"
#include <math.h>
#include <vector>


using namespace std;
  Characteristics::Characteristics(){
    
    };

  //Initialize HARVEST sample pathway characteristics
  Characteristics::Characteristics(int pHfireOfInterest, int pHpathway, int pHaction, int pHyear, double pPP1, double pPP2,
    double pPP3, double pPP4, double pPP5, double pLP1, double pLP2, double pLP3, double pMC1, double pMC2, double pMC3, 
    double pMC4, double pMC5, double pHarvestTotal, double pHarvestPP, double pHarvestLP, double pHarvestMC){

    HfireOfInterest = pHfireOfInterest;
    Hpathway = pHpathway;
    Haction = pHaction;
    Hyear = pHyear;
    PP1 = pPP1;
    PP2 = pPP2;
    PP3 = pPP3;
    PP4 = pPP4;
    PP5 = pPP5;
    LP1 = pLP1;
    LP2 = pLP2;
    LP3 = pLP3;
    MC1 = pMC1;
    MC2 = pMC2;
    MC3 = pMC3;
    MC4 = pMC4;
    MC5 = pMC5;
    harvestTotal = ((pHarvestPP * .165) + (pHarvestLP * .15) + (pHarvestMC * .165));
    harvestPP = (pHarvestPP * .165) / pow(1.04, Hyear);
    harvestLP = (pHarvestLP * .15) / pow(1.04, Hyear);
    harvestMC = (pHarvestMC * .165) / pow(1.04, Hyear);
    totalHarvestValue = harvestPP + harvestLP + harvestMC;
    sclassPP1 = pow(PP1 - 10, 2);
    sclassPP2 = pow(PP2 - 5, 2);
    sclassPP3 = pow(PP3 - 35, 2);
    sclassPP4 = pow(PP4 - 45, 2);
    sclassPP5 = pow(PP5 - 5, 2);
    deviationPP = (sclassPP1 + sclassPP2 + sclassPP3 + sclassPP4 + sclassPP5) / 5;

  };

  
  // Intialize sample pathway characteristics.
  Characteristics::Characteristics(int pFireOfInterest, int pPathway, int pAction, int pYear, int pStartIndex, int pCallFarsite, 
    double pSuppression, double pTimberLoss, double pErc, double pSc, double pPrecip, double pTemperature, double pHumid, 
    int pWdirection, int pWind, double pArea, double pCrown, int pIgnition, int pCover, int pAspect, int pSlope, int pFuel){

    fireOfInterest = pFireOfInterest;
    pathway = pPathway;
    action = pAction;
    year = pYear;
    if(pYear == 0)
      foiSuppress = pSuppression;
    startIndex = pStartIndex;
    callFarsite = pCallFarsite;
    suppression = pSuppression / pow(1.04, year);
    timberLoss = pTimberLoss;                    //pTimberLoss / pow(1.04, year);
    valueChange = suppression + timberLoss;
    foiErc = pErc;
    foiSc = pSc;
    foiSize = pArea;
    foiCrown = pCrown;
    foiPrecip = pPrecip;
    foiTemperature = pTemperature;
    foiHumid = pHumid;
    foiWdirection = pWdirection;
    foiWind = pWind;
    foiIgnition = pIgnition;
    foiCover = pCover;
    foiAspect = pAspect;
    foiSlope = pSlope;
    foiFuel = pFuel;
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

//HARVEST
int Characteristics::getHFireOfInterest(){
  return HfireOfInterest;
};

int Characteristics::getHPathway(){
  return Hpathway;  
};
  
int Characteristics::getHAction(){
  return Haction;
};
  
int Characteristics::getHYear(){
  return Hyear;
};

int Characteristics::getStartIndex(){
  return startIndex;
};

double Characteristics::getTotalHarvestValue(){
  return totalHarvestValue;
}

double Characteristics::getTotalHarvest(){
  return harvestTotal;
}

double Characteristics::getTotalDeviationPP(){
  return deviationPP;
}

//SUPPRESSION
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

double Characteristics::getFOICrown(){
    return foiCrown;
}

double Characteristics::getFOIPrecip(){
  return foiPrecip;
}

double Characteristics::getFOITemperature(){
  return foiTemperature;
}

double Characteristics::getFOIHumid(){
  return foiHumid;
}

int Characteristics::getFOIWdirection(){
  return foiWdirection;
}

int Characteristics::getFOIWind(){
  return foiWind;
}

int Characteristics::getFOIIgnition(){
  return foiIgnition;
}

int Characteristics::getFOICover(){
  return foiCover;
}

int Characteristics::getFOIAspect(){
  return foiAspect;
}

int Characteristics::getFOISlope(){
  return foiSlope;
}

int Characteristics::getFOIFuel(){
  return foiFuel;
}

double Characteristics::getFOISuppress(){
  return foiSuppress;
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

