
#include "stdafx.h"
#include "ProcessVariables.h"
#include <ctime>
#include <algorithm>


ProcessVariables::ProcessVariables(vector<Characteristics> pVariables){
  variables = pVariables;
  srand(static_cast<unsigned int> (time(0)));
};

void ProcessVariables::yearlyVariables(){

};

void ProcessVariables::pairSamplePathways(){

};

void ProcessVariables::differenceSamplePathways(){

};

void ProcessVariables::bootstrapFireOfInterest(){
  

  FILE * bootstrapFile;
  fopen_s(&bootstrapFile, "..\\bootstrap_500.txt", "w");

  FILE * samplesFile;
  fopen_s(&samplesFile, "..\\bootstrapSamples_500.txt", "w");
  // Create instance of statistics to run on bootstrap samples.
  Statistics bootstrap;

  // Holds the actual values from the data set.
  vector<double> values;
  // Holds the specific values from a random sampling of data with replacement.
  vector<double> sample;
  // Holds the set of mean values based on random sampling of data with replacement.
  vector<double> means;
  // Holds the set of median values based on random sampling of data with replacement.
  vector<double> medians;

  // Total number of pathways in the vector.
  int maxPath = variables.at(variables.size()-1).getFireOfInterest();
  // Interator through the variable vector.
  int b = 0;
  // For each fire of interest:
  for(int a = variables.at(0).getFireOfInterest(); a <= maxPath; a = variables.at(b).getFireOfInterest())
  {
    // For each fire of interest:
    int foi = variables.at(b).getFireOfInterest();
    while(variables.at(b).getFireOfInterest() == foi && b < (int)variables.size() - 1 ){
      values.push_back(variables.at(b).getSuppressionCostSavings());
      b++;
    }
    values.push_back(variables.at(b).getSuppressionCostSavings());

    double foiAverage = bootstrap.average(values);
    double foiMedian = bootstrap.median(values);

    // Choose random values with replacement.
    for(int d = 0; d < 999; d++)
    {
      for(int c = 0; c < (int)values.size(); c++)
      {
        int select = rand() % values.size();
        sample.push_back(values.at(select));
      }
      
      means.push_back(bootstrap.average(sample));
      medians.push_back(bootstrap.median(sample));
      fprintf(samplesFile, "%d %lf %lf\n", foi, means.at(d), medians.at(d));
      sample.clear();
    }
    sort(means.begin(), means.end());
    sort(medians.begin(), medians.end());

    double lower95 = bootstrap.lowerBoundBootstrap(means, foiAverage);
    double upper95 = bootstrap.upperBoundBootstrap(means,foiAverage);

    fprintf(bootstrapFile, "%d %lf %lf %lf %lf\n", 
      foi, foiAverage, lower95, upper95, foiMedian);
    means.clear();
    medians.clear();
    values.clear();
    if(a == maxPath)
      break;
  }
  fclose(bootstrapFile);
  fclose(samplesFile);
};

void ProcessVariables::fireOfInterest(){

};


ProcessVariables::~ProcessVariables(){
};