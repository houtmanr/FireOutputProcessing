// processLargeSets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProcessVariables.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
  // Variables to be read in from file
  int fireOfInterest;
  int pathway;
  int action;
  int attemptSuppression;
  int callFarsite;
  int year;
  int startIndex;
  int endIndex;
  double erc;
  double sc;
  double numIgnitions;
  int crownFirePixels;
  int surfaceFirePixels;
  double suppressionCost;
  double timberLoss;
  
  // tracks when a new file has been opened.
  bool newFile = 0;

      
  // This vector will be used to evaluate characteristics
  // across the years.
  vector<Characteristics> yearlyCharacters;

  // This vector will be used to evaluate characteristics 
  // for each suppress/let-burn pair.
  vector<Characteristics> pairCharacteristics;

  // This vector will be used to evaluate characteristics
  // for each fire of choice, across random futures.
  vector<Characteristics> foiCharacteristics;
  
  for(int j = 0; j < 21; j++)
  {

    // This vector will be used to evaluate characteristics
    // of the pathways. Declared here in order to empty
    // after each 50 pathway set.
    vector<Characteristics> pathwayCharacters;
    
    FILE *inputs;
    char name[100];
    sprintf_s(name, "..\\..\\..\\..\\estimates\\August19\\estimatedoutput%d.csv", j);
    fopen_s(&inputs, name, "r");

    while(!feof(inputs))
    {
      // Read in the input variables. 
      fscanf_s(inputs, "%d, %d, %d, %d, %d, %d, %d, %d, %lf, %lf, %lf, %d, %d, %lf, %lf \n", 
        &fireOfInterest, &pathway, &action, &attemptSuppression, &callFarsite,
        &year, &startIndex, &endIndex, &erc, &sc, &numIgnitions, &crownFirePixels,
         &surfaceFirePixels, &suppressionCost, &timberLoss);

      Characteristics temp = Characteristics(fireOfInterest, pathway, action, year,
        callFarsite, suppressionCost, timberLoss, erc, sc, crownFirePixels + surfaceFirePixels);


      if(pathwayCharacters.empty())
        pathwayCharacters.push_back(temp);
      else
      {
        for(int k = 0; k < (int)pathwayCharacters.size(); k++){
          int foi = pathwayCharacters.at(k).getFireOfInterest();
          int path = pathwayCharacters.at(k).getPathway();
          int act = pathwayCharacters.at(k).getAction();
          int yr = pathwayCharacters.at(k).getYear();

          if(foi == fireOfInterest && path == pathway && act == action){
            pathwayCharacters.at(k).updateValue(temp);
            break;
          } else if(foi > fireOfInterest){
              vector<Characteristics>::iterator it;
              it = pathwayCharacters.begin();
              pathwayCharacters.insert(it + k, temp);
              break;
          } else if(foi == fireOfInterest && path > pathway){
              vector<Characteristics>::iterator it;
              it = pathwayCharacters.begin();
              pathwayCharacters.insert(it + k, temp);
              break;
          } else if(foi == fireOfInterest && path == pathway && act > action){
              vector<Characteristics>::iterator it;
              it = pathwayCharacters.begin();
              pathwayCharacters.insert(it + k, temp);
              break;
          } else if(k + 1  == (int)pathwayCharacters.size()){
            pathwayCharacters.push_back(temp);
            break;
          }
        }
      }

      // Yearly characteristics.
      Characteristics temp2 = Characteristics(year, action, erc, sc, numIgnitions,
        crownFirePixels, surfaceFirePixels, suppressionCost, timberLoss);

      if(yearlyCharacters.empty())
      { 
        temp2.initializeYearlyTotals();
        yearlyCharacters.push_back(temp2);
      }
      else 
      {
        for(int x = 0; x < (int)yearlyCharacters.size(); x++)
        {
          int yr = yearlyCharacters.at(x).getYear();
          int act = yearlyCharacters.at(x).getAction();
          if(yr == year && act == action)
          {
            yearlyCharacters.at(x).totalYearlyValues(temp2);
            break;
          }
          else if(yr > year)
          {
            temp2.initializeYearlyTotals();
            vector<Characteristics>::iterator it;
            it = yearlyCharacters.begin();
            yearlyCharacters.insert(it + x, temp2);
            break;
          }
          else if(x + 1 == (int)yearlyCharacters.size())
          {
            temp2.initializeYearlyTotals();
            yearlyCharacters.push_back(temp2);
            break;
          }
        }
      }
    }  

    // Create pair characteristic vector.
    int i = 0;
    while((int)pathwayCharacters.size() > i)
    {
        Characteristics letBurn = pathwayCharacters.at(i);
        Characteristics suppress = pathwayCharacters.at(i + 1);
        if(letBurn.getFireOfInterest() == suppress.getFireOfInterest()
          && letBurn.getPathway() == suppress.getPathway() 
          && letBurn.getAction() + 1 == suppress.getAction()){
            letBurn.setSuppress(letBurn.getSuppress());
            letBurn.setFutureSuppress(letBurn.getFutureSuppress());
            letBurn.setTimberLoss(letBurn.getTimberLoss());
            suppress.setSuppress(suppress.getFutureSuppress());
            suppress.setFutureSuppress(suppress.getFutureSuppress());
            suppress.setTimberLoss(suppress.getTimberLoss());      

          double differenceSuppress = letBurn.getSuppress() - suppress.getSuppress();
          double differenceFutureSuppress = letBurn.getFutureSuppress() - suppress.getFutureSuppress();
          double differenceTimber = letBurn.getTimberLoss() - suppress.getTimberLoss();
          double differenceTotal = differenceSuppress + differenceTimber;
          int foiID = letBurn.getFireOfInterest();
          int pathwayID = letBurn.getPathway();
          Characteristics difference = Characteristics(foiID, pathwayID, differenceSuppress, differenceTimber, differenceTotal);
          pairCharacteristics.push_back(difference);
          i += 2;
        }
        else
          i++;
    }
    
    FILE * pathOutput;
    if(newFile == 0){
      fopen_s(&pathOutput, "..\\pathOutputs_500.txt", "a");
      //fprintf_s(pathOutput, "FireOfInterest Future Action SuppressCost TimberLoss "
        //"ValueChange ERC_FF SC_FF FireSize_FF\n");
    }
    else
      fopen_s(&pathOutput, "..\\pathOutputs_500.txt", "a");
    newFile = 1;
    

    for(int m = 0; m < (int)pathwayCharacters.size(); m ++)
    {
      
      pathwayCharacters.at(m).setFutureSuppress(pathwayCharacters.at(m).getFutureSuppress());
      pathwayCharacters.at(m).setTimberLoss(pathwayCharacters.at(m).getTimberLoss());

      fprintf_s(pathOutput, "%d %d %d %lf %lf %lf %lf %lf %lf\n", pathwayCharacters.at(m).getFireOfInterest(), 
        pathwayCharacters.at(m).getPathway(), pathwayCharacters.at(m).getAction(),
        pathwayCharacters.at(m).getFutureSuppress(), pathwayCharacters.at(m).getTimberLoss(),
        pathwayCharacters.at(m).getValueChange(), pathwayCharacters.at(m).getFOIErc(),
        pathwayCharacters.at(m).getFOISc(), pathwayCharacters.at(m).getFOISize());
    }

    fclose(pathOutput);
    fclose(inputs);
  }    

  // File for yearly averages.
  FILE * yearOutput;
  fopen_s(&yearOutput, "..\\yearOutputs_500.txt", "w");
  fprintf_s(yearOutput, "Year Action ERC SC #Ignitions CrownFire SurfaceFire TotalBurned SuppressionCosts TimberLosses\n");

  for(int m = 0; m < (int)yearlyCharacters.size(); m++)
    yearlyCharacters.at(m).printAverageValues(yearOutput);

  fclose(yearOutput);

  // File for change in suppression costs and timber loss over each sample pathway.
  FILE * pairOutput;
  fopen_s(&pairOutput, "..\\pairOutputs_500.txt", "w");
  fprintf_s(pairOutput, "FireOfInterest Pathway SuppressionSavings TimberLoss ValueChange\n");

  for(int m = 0; m < (int)pairCharacteristics.size(); m++)
    pairCharacteristics.at(m).printPairValues(pairOutput);

  fclose(pairOutput);

  // Bootstrapping proceedure.
  ProcessVariables meanBootstrap = ProcessVariables(pairCharacteristics);
  meanBootstrap.bootstrapFireOfInterest();

  // Fire of Interest outputs.
  vector<double> suppressionCosts;
  vector<double> timberLosses;

  Statistics runStats;
  int i = pairCharacteristics.at(0).getFireOfInterest();
  int k = 0;
  FILE * foiOutput;
  fopen_s(&foiOutput, "..\\foiOutput_500.txt", "w");
  fprintf(foiOutput, "FireOfInterest NumPaths AverageSuppressionSavings SDSuppressionSavings "
    "LowerSC UpperSC AverageTimberLoss SDTimberLoss LowerTL UpperTL\n");
    
  for(int m = 0; m < (int)pairCharacteristics.size() - 1; m)
  {
    int count = 0;
    bool check = 0;
    while(m < (int)pairCharacteristics.size() && i == pairCharacteristics.at(k).getFireOfInterest() ){
      suppressionCosts.push_back((double)pairCharacteristics.at(m).getSuppressionCostSavings());
      timberLosses.push_back((double)pairCharacteristics.at(m).getTimberLossSavings());
      k++;
      m++;
      check = 1;
      count++;
    }

    if(check == 1)
    {
      double aveSC = runStats.average(suppressionCosts);
      double medianSC = runStats.median(suppressionCosts);
      double sDSC = runStats.standardDeviation(suppressionCosts);
      double lowerSC = runStats.lowerBound(suppressionCosts);
      double upperSC = runStats.upperBound(suppressionCosts);
      double aveTL = runStats.average(timberLosses);
      double sDTL = runStats.standardDeviation(timberLosses);
      double lowerTL = runStats.lowerBound(timberLosses);
      double upperTL = runStats.upperBound(timberLosses);

    
      fprintf_s(foiOutput, "%d %d %lf %lf %lf %lf %lf %lf %lf %lf\n", pairCharacteristics.at(k - 1).getFireOfInterest(), 
        count, aveSC, sDSC, lowerSC, upperSC, aveTL, sDTL, lowerTL, upperTL);
    }
    suppressionCosts.clear();
    timberLosses.clear();
    i++;
  }
  fclose(foiOutput);


	return 0;
}


