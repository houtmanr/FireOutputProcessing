#include <vector>

using namespace std;

class Statistics{
public:
  Statistics::Statistics();

  double average(vector<double> pData);
  double median(vector<double> pData);
  double standardDeviation(vector<double> pData);
  double standardDeviationTwoMeans(vector<double> pData1, vector<double> pData2);
  double lowerBound(vector<double> pData);
  double upperBound(vector<double> pData);
  double lowerBoundTwoMeans(vector<double> pData);
  double upperBoundTwoMeans(vector<double> pData);
  double lowerBoundBootstrap(vector<double> pData, double populationVariable);
  double upperBoundBootstrap(vector<double> pData, double populationVariable);
  double calculateProbit(vector<double> pData, double populationVariable);
  double calculateA(vector<double> pData, double populationVariable);

  Statistics::~Statistics();


};