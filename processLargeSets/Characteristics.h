#include <vector>
#include "Statistics.h"

using namespace std;

class Characteristics{
  
public:

  /**
  * @brief Default Constructor
  */
  Characteristics::Characteristics();

  /**
  * @brief Constructor
  * Tracks characteristics of a HARVEST sample pathway.
  */
  Characteristics::Characteristics(int pHfireOfInterest, int pHpathway, int pHaction, int pHyear, double pPP1, double pPP2,
    double pPP3, double pPP4, double pPP5, double pLP1, double pLP2, double pLP3, double pMC1, double pMC2, double pMC3, 
    double pMC4, double pMC5, double pHarvestTotal, double pHarvestPP, double pHarvestLP, double pHarvestMC);

  /**
  * @brief Constructor
  * Tracks characteristics of a SUPPRESSION sample pathway.
  */
  Characteristics::Characteristics(int pFireOfInterest, int pPathway, int pAction, int pCallFarsite, int pYear, 
    int startIndex, double pSuppression, double pTimberLoss, double pErc, double pSc, double pPrecip, double pTemperature, 
    double pHumid, int pWdirection, int pWind, double pArea, double pCrown, int pIgnition, int pCover, int pAspect,
    int pSlope, int pFuel);

  /**
  * @brief Constructor
  * Tracks characteristics across years of whole sample set.
  */
  Characteristics::Characteristics(int pYear, int pAction, double pErc, double pSc, double pNumIgnitions,
    double pCrownFire, double pSurfaceFire, double pSuppression, double pTimberLoss);
    
  /**
  * @brief Constructor
  * Tracks characteristics across years of whole sample set.
  */
  Characteristics::Characteristics(int pFoi, int pPathway, double pDifferenceSuppress, double pDifferenceTimberLoss, 
    double pDifferenceTotal);

  /**
  * @brief Destructor
  */
  Characteristics::~Characteristics();

  // Updates the cost variables of a sample pathway.
  void updateValue(Characteristics temp);

  // Updates the values of a given year.
  void totalYearlyValues(Characteristics temp);

  // Updates the average values of a given year.
  void averageYearlyValues();

  // Initializes the total value variables for a year.
  void initializeYearlyTotals();

  // Calculates the average values for a given year across all sample pathways.
  void setYearlyAverageValues();

  // Prints average yearly outputs for all years, across all sample pathways.
  void printAverageValues(FILE * outputs);
  void printPairValues(FILE * pairOutput);
  void printFoiValues(FILE * foiOutput);

  void updateFoiValues();

  double calculateSDSuppression(vector<Characteristics> standardDeviationData);
  double calculateSDTimberLoss(vector<Characteristics> standardDeviationData);

  int getFireOfInterest();
  int getPathway();
  int getAction();
  int getYear();
  int getHFireOfInterest();
  int getHPathway();
  int getHAction();
  int getHYear();
  int getStartIndex();
  double getSuppress();
  double getFutureSuppress();
  double getTimberLoss();
  double getValueChange();
  double getTotalHarvestUndiscounted();
  double getTotalHarvestDiscounted();
  double getPPHarvestVolume();
  double getLPPHarvestVolume();
  double getMCHarvestVolume();
  double getTotalDeviationPP();
  double getFOIErc();
  double getFOISc();
  double getFOISize();
  double getFOICrown();
  double getFOIPrecip();
  double getFOITemperature();
  double getFOIHumid();
  int getFOIWdirection();
  int getFOIWind();
  int getFOIIgnition();
  int getFOICover();
  int getFOIAspect();
  int getFOISlope();
  int getFOIFuel();
  double getFOISuppress();
  double getSuppressionCostSavings();
  double getTimberLossSavings();
  double getTotalCostPlusNVC();
  void setSuppress(double pSupress);
  void setFutureSuppress(double pFutureSuppress);
  void setTimberLoss(double pTimber);

private:

  //Characteristics for HARVEST pathway
  int HfireOfInterest;
  int Hpathway;
  int Haction;
  int Hyear;
  double PP1;
  double PP2;
  double PP3;
  double PP4;
  double PP5;
  double LP1;
  double LP2;
  double LP3;
  double MC1;
  double MC2;
  double MC3;
  double MC4;
  double MC5;
  double harvestVolumePP;
  double harvestVolumeLPP;
  double harvestVolumeMC;
  double totalHarvestValueUndiscounted;
  double harvestPP;
  double harvestLP;
  double harvestMC;
  double totalHarvestValueDiscounted;
  double sclassPP1;
  double sclassPP2;
  double sclassPP3;
  double sclassPP4;
  double sclassPP5;
  double deviationPP;

  // Characteristics for a SUPPRESSION pathway.
  int fireOfInterest;
  int pathway;
  int action;
  int callFarsite;
  int year;
  int startIndex;
  double suppression;
  double futureSuppression;
  double timberLoss;
  double valueChange;
  

  // Characteristics for the first fire.
  double foiErc;
  double foiSc;
  double foiSize;
  double foiCrown;
  int foiStartIndex;
  double foiPrecip;
  double foiTemperature;
  double foiHumid;
  int foiWdirection;
  int foiWind;
  int foiIgnition;
  int foiCover;
  int foiAspect;
  int foiSlope;
  int foiFuel;
  int foiSuppress;

  // Characteristics for the difference calculations.
  double suppressionCostSavings;
  double timberLossSavings;
  double totalCostPlusNVC;

  // Characteristics for the fire of interest averages.
  double averageBenefit;
  double standardDeviationBenefit;
  double averageLoss;
  double standardDeviationLoss;
  vector<double> supressionSD;
  vector<double> timberSD;

  // Characteristics for a year;
  int pathYears;
  double erc;
  double totalErc;
  double sc;
  double totalSc;
  double numIgnitions;
  double totalNumIgnitions;
  double crownFire;
  double totalCrownFire;
  double surfaceFire;
  double totalSurfaceFire;
  double area;
  double totalArea;
  double totalSuppression;
  double totalTimberLoss;
  double totalValueChange;
};