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
  * Tracks characteristics of a sample pathway.
  */
  Characteristics::Characteristics(int pFireOfInterest, int pPathway, int pAction, int pCallFarsite, int pYear, 
    double pSuppression, double pTimberLoss, double pErc, double pSc, double pArea);

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
  double getSuppress();
  double getFutureSuppress();
  double getTimberLoss();
  double getValueChange();
  double getFOIErc();
  double getFOISc();
  double getFOISize();
  double getSuppressionCostSavings();
  double getTimberLossSavings();
  double getTotalCostPlusNVC();
  void setSuppress(double pSupress);
  void setFutureSuppress(double pFutureSuppress);
  void setTimberLoss(double pTimber);

private:

  // Characteristics for a pathway.
  int fireOfInterest;
  int pathway;
  int action;
  int callFarsite;
  int year;
  double suppression;
  double futureSuppression;
  double timberLoss;
  double valueChange;

  // Characteristics for the first fire.
  double foiErc;
  double foiSc;
  double foiSize;

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