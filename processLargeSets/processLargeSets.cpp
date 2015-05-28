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
  // Set pathway variables here for a specific dataset. Directories MUST EXIST to work.
  char workingDirectory[100] = "..\\..\\Thesis\\harv9mil_100_199\\";
  char outputDirectory[50] = "\\outputs\\9mil_100_199_";
  
  // Variables to be read in from SUPPRESSION file
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
  double precip;
  double temperature;
  double humid;
  int wind;
  int wDirection;
  int ignition;
  int cover;
  int aspect;
  int slope;
  int fuel;
  int numIgnitions;
  int crownFirePixels;
  int surfaceFirePixels;
  double suppressionCost;
  double timberLoss;
  vector<double> initialSuppressionCost;
  vector<double> sclassPP0;
  vector<double> harvestPP0;
  vector<double> sclassPP9;
  vector<double> harvestPP9;
  vector<double> harvestPP9T;
  vector<double> sclassPP19;
  vector<double> harvestPP19;
  vector<double> harvestPP19T;
  vector<double> sclassPP29;
  vector<double> harvestPP29;
  vector<double> harvestPP29T;
  vector<double> sclassPP39;
  vector<double> harvestPP39;
  vector<double> harvestPP39T;
  vector<double> sclassPP49;
  vector<double> harvestPP49;
  vector<double> harvestPP49T;
  vector<double> sclassPP59;
  vector<double> harvestPP59;
  vector<double> harvestPP59T;
  vector<double> sclassPP69;
  vector<double> harvestPP69;
  vector<double> harvestPP69T;
  vector<double> sclassPP79;
  vector<double> harvestPP79;
  vector<double> harvestPP79T;
  vector<double> sclassPP89;
  vector<double> harvestPP89;
  vector<double> harvestPP89T;
  vector<double> sclassPP99;
  vector<double> harvestPP99;
  vector<double> harvestPP99T;
  vector<double> harvestPPtotal;
  vector<double> harvestPPAvg;
  vector<double> sclassPPtotal;
  vector<double> sclassPP50;
  vector<double> sclassPP20;

  // Variables to be read in from HARVEST file
  double averageHarvestVolume;
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
  double harvestTotal = 0;
  double harvestPP = 0;
  double harvestLP = 0;
  double harvestMC = 0;
  double finalHarvest[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Characteristics temp0;

  // tracks when a new file has been opened.
  bool newFile = 0;

  vector<Characteristics> HpathwayCharacters;
  vector<double> finalLTV;
  vector<Characteristics> pathwayCharacters;
  
  
  FILE *inputs;
  char name[100];
  sprintf_s(name, "%sharvestoutput_sorted.csv", workingDirectory);
  fopen_s(&inputs, name, "r");
  int harvest = 0;
  while(!feof(inputs))
  {
    if(harvest < 11)
    {
      // Read in the HARVEST input variables. 
      fscanf_s(inputs, "%d, %d, %d, %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", 
        &HfireOfInterest, &Hpathway, &Haction, &Hyear, &averageHarvestVolume, &PP1, &PP2, &PP3, &PP4, &PP5, &LP1, &LP2, &LP3, &MC1, &MC2, &MC3, &MC4, &MC5,
        &harvestTotal, &harvestPP, &harvestLP, &harvestMC);
      harvest++;

      temp0 = Characteristics(HfireOfInterest, Hpathway, Haction, Hyear, PP1, PP2, PP3, PP4, PP5, LP1, LP2, LP3, MC1, MC2, MC3, MC4, MC5,
        harvestTotal, harvestPP, harvestLP, harvestMC);

      // This loop sorts the harvest variables by fire of interest, pathway, action, and year. There must
      // be a faster way to do this. Vector sort function?
      if(HpathwayCharacters.empty())
        HpathwayCharacters.push_back(temp0);
      else
      {
        for(int k = 0; k < (int)HpathwayCharacters.size(); k++){
          int Hfoi = HpathwayCharacters.at(k).getHFireOfInterest();
          int Hpath = HpathwayCharacters.at(k).getHPathway();
          int Hact = HpathwayCharacters.at(k).getHAction();
          int Hyr = HpathwayCharacters.at(k).getHYear();

          if(Hfoi == HfireOfInterest && Hpath == Hpathway && Hact == Haction && Hyr == Hyear){
            HpathwayCharacters.at(k).updateValue(temp0);
            break;
          } else if(Hfoi > HfireOfInterest){
              vector<Characteristics>::iterator it;
              it = HpathwayCharacters.begin();
              HpathwayCharacters.insert(it + k, temp0);
              break;
          } else if(Hfoi == HfireOfInterest && Hpath > Hpathway){
              vector<Characteristics>::iterator it;
              it = HpathwayCharacters.begin();
              HpathwayCharacters.insert(it + k, temp0);
              break;
          } else if(Hfoi == HfireOfInterest && Hpath == Hpathway && Hact > Haction){
              vector<Characteristics>::iterator it;
              it = HpathwayCharacters.begin();
              HpathwayCharacters.insert(it + k, temp0);
              break;
          } else if(k + 1  == (int)HpathwayCharacters.size()){
            HpathwayCharacters.push_back(temp0);
            break;
          } else if(k + 2  == (int)HpathwayCharacters.size()){      //NEW
            HpathwayCharacters.push_back(temp0);
            break;
          }

        }
      }
    }
    else if(harvest == 11)
    {
      fscanf_s(inputs, ", %d, %d, %d, %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", &HfireOfInterest, &Hpathway, &Haction, &Hyear, 
                        &finalHarvest[0], &finalHarvest[1], &finalHarvest[2], &finalHarvest[3], &finalHarvest[4], &finalHarvest[5], &finalHarvest[6], 
                        &finalHarvest[7], &finalHarvest[8], &finalHarvest[9],  &finalHarvest[10]);
      harvest = 0;
      finalLTV.push_back(finalHarvest[10]);
    }
  }


  // Variable notes: totalHarvestUndiscounted == the total value of the harvest for a given year
  //                 totalHarvestDiscounted == the total value of the harvest discounted to t = 0

  //Returns the harvest and sclass deviation for all year 0's and places them in a vector
  for(int b = 0; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest0 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP0.push_back(harvest0);
      double deviationPP0 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP0.push_back(deviationPP0);
  }
  //Returns the harvest and sclass deviation for all year 9's and places them in a vector
  for(int b = 1; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest9 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP9.push_back(harvest9);
      double harvest9T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP9T.push_back(harvest9T);
      double deviationPP9 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP9.push_back(deviationPP9);
  }
  //Returns the harvest and sclass deviation for all year 19's and places them in a vector
  for(int b = 2; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest19 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP19.push_back(harvest19);
      double harvest19T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP19T.push_back(harvest19T);
      double deviationPP19 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP19.push_back(deviationPP19);
  }
  //Returns the harvest and sclass deviation for all year 29's and places them in a vector
  for(int b = 3; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest29 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP29.push_back(harvest29);
      double harvest29T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP29T.push_back(harvest29T);
      double deviationPP29 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP29.push_back(deviationPP29);
  }
  //Returns the harvest and sclass deviation for all year 39's and places them in a vector
  for(int b = 4; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest39 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP39.push_back(harvest39);
      double harvest39T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP39T.push_back(harvest39T);
      double deviationPP39 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP39.push_back(deviationPP39);
  }
  //Returns the harvest and sclass deviation for all year 49's and places them in a vector
  for(int b = 5; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest49 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP49.push_back(harvest49);
      double harvest49T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP49T.push_back(harvest49T);
      double deviationPP49 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP49.push_back(deviationPP49);
  }
  //Returns the harvest and sclass deviation for all year 59's and places them in a vector
  for(int b = 6; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest59 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP59.push_back(harvest59);
      double harvest59T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP59T.push_back(harvest59T);
      double deviationPP59 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP59.push_back(deviationPP59);
  }
  //Returns the harvest and sclass deviation for all year 69's and places them in a vector
  for(int b = 7; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest69 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP69.push_back(harvest69);
      double harvest69T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP69T.push_back(harvest69T);
      double deviationPP69 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP69.push_back(deviationPP69);
  }
  //Returns the harvest and sclass deviation for all year 79's and places them in a vector
  for(int b = 8; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest79 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP79.push_back(harvest79);
      double harvest79T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP79T.push_back(harvest79T);
      double deviationPP79 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP79.push_back(deviationPP79);
  }
  //Returns the harvest and sclass deviation for all year 89's and places them in a vector
  for(int b = 9; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest89 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP89.push_back(harvest89);
      double harvest89T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP89T.push_back(harvest89T);
      double deviationPP89 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP89.push_back(deviationPP89);
  }
  //Returns the harvest and sclass deviation for all year 99's and places them in a vector
  for(int b = 10; b < (int)HpathwayCharacters.size(); b += 11){
      double harvest99 = HpathwayCharacters.at(b).getTotalHarvestDiscounted();
      harvestPP99.push_back(harvest99);
      double harvest99T = HpathwayCharacters.at(b).getTotalHarvestUndiscounted();
      harvestPP99T.push_back(harvest99T);
      double deviationPP99 = HpathwayCharacters.at(b).getTotalDeviationPP();
      sclassPP99.push_back(deviationPP99);
  }

  for(int b = 0; b < int(harvestPP29.size()); b ++){

      double harvestTotal = harvestPP9.at(b) + harvestPP19.at(b) + harvestPP29.at(b) + harvestPP39.at(b) + harvestPP49.at(b) +
          harvestPP59.at(b) + harvestPP69.at(b) + harvestPP79.at(b) + harvestPP89.at(b) + harvestPP99.at(b);
      harvestPPtotal.push_back(harvestTotal);

      double sclassTotal20 = sclassPP19.at(b);
      sclassPP20.push_back(sclassTotal20);      

      double sclassTotal50 = sclassPP49.at(b);
      sclassPP50.push_back(sclassTotal50);

      double sclassTotal = sclassPP99.at(b);
      sclassPPtotal.push_back(sclassTotal);
      
      double harvestTotalAvg = (harvestPP9T.at(b) + harvestPP19T.at(b) + harvestPP29T.at(b) + harvestPP39T.at(b) + harvestPP49T.at(b) +
          harvestPP59T.at(b) + harvestPP69T.at(b) + harvestPP79T.at(b) + harvestPP89T.at(b) + harvestPP99T.at(b)) / 100;
      harvestPPAvg.push_back(harvestTotalAvg);

  }
    
  // This vector will be used to evaluate characteristics
  // across the years.
  vector<Characteristics> yearlyCharacters;

  // This vector will be used to evaluate characteristics 
  // for each suppress/let-burn pair.
  vector<Characteristics> pairCharacteristics;

  // This vector will be used to evaluate characteristics
  // for each fire of choice, across random futures.
  vector<Characteristics> foiCharacteristics;
  
  for(int j = 0; j < 11; j++)
  {

    // This vector will be used to evaluate characteristics
    // of the pathways. Declared here in order to empty
    // after each 50 pathway set.
    //vector<Characteristics> pathwayCharacters;
    
    FILE *inputs2;
    sprintf_s(name, "%sestimatedoutput%d.csv", workingDirectory, j);
    fopen_s(&inputs2, name, "r");

    while(!feof(inputs2))
    {
      // Read in the input variables. 
      fscanf_s(inputs2, "%d, %d, %d, %d, %d, %d, %d, %d, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d, %d, %lf, %lf, ", 
        &fireOfInterest, &pathway, &action, &attemptSuppression, &callFarsite,
        &year, &startIndex, &endIndex, &erc, &sc, &precip, &temperature, &humid, &wDirection, &wind, 
        &numIgnitions, &crownFirePixels, &surfaceFirePixels, &suppressionCost, &timberLoss);

      for(int i = 0; i < numIgnitions; i++){
        fscanf_s(inputs2, "%d, %d, %d, %d, %d, ", &ignition, &cover, &aspect, &slope, &fuel);
      }

      fscanf_s(inputs2, "\n");

      Characteristics temp = Characteristics(fireOfInterest, pathway, action, year,
        startIndex, callFarsite, suppressionCost, timberLoss, erc, sc, precip, 
        temperature, humid, wDirection, wind, crownFirePixels + surfaceFirePixels, 
        crownFirePixels, ignition, cover, aspect, slope, fuel);

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
    

      //Yearly characteristics.
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
    }

    // Create pair characteristic vector.
    int i = 0;
    int check = (int)pathwayCharacters.size();
    while((int)pathwayCharacters.size() - 1 > i)
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
    sprintf_s(name, "%sPathOutputs.txt", workingDirectory);
    if(newFile == 0){
      ofstream pathOutput(name, ios::trunc);
      pathOutput << "FireOfInterest Pathway Action FutureSuppressCost InitialSuppressionCost "
        "TimberLoss ValueChange ERC_FirstFire SC_FirstFire StartIndex Precipitation Temperature Humidity "
        "WindDirection WindSpeed Size_FirstFire CrownFire IgnitionLocation CoverType Aspect Slope "
        "FuelModel Harvest$Year0 Harvest$Total HarvestValueAvePerPeriod "
        //"Harvest$PP Harvest$LPP Harvest$MC "
        "SClass_0 SClass_20 SClass_50 SClass_Total FinalLTV\n";
      pathOutput.close();
    }
    ofstream pathOutput(name, ios::app);
    newFile = 1;
    
    int o = 0;
    for(int m = 0; m < (int)pathwayCharacters.size(); m ++)
    {
      
      pathwayCharacters.at(m).setFutureSuppress(pathwayCharacters.at(m).getFutureSuppress());
      pathwayCharacters.at(m).setTimberLoss(pathwayCharacters.at(m).getTimberLoss());

      pathOutput << pathwayCharacters.at(m).getFireOfInterest() << " " << pathwayCharacters.at(m).getPathway() << " " << 
        pathwayCharacters.at(m).getAction() <<  " " << pathwayCharacters.at(m).getFutureSuppress() <<  " " << 
        pathwayCharacters.at(m).getFOISuppress() <<  " " << pathwayCharacters.at(m).getTimberLoss() <<  " " << 
        pathwayCharacters.at(m).getValueChange() <<  " " << pathwayCharacters.at(m).getFOIErc() <<  " " << 
        pathwayCharacters.at(m).getFOISc() <<  " " << pathwayCharacters.at(m).getStartIndex() <<  " " << 
        pathwayCharacters.at(m).getFOIPrecip() <<  " " << pathwayCharacters.at(m).getFOITemperature() <<  " " << 
        pathwayCharacters.at(m).getFOIHumid() <<  " " << pathwayCharacters.at(m).getFOIWdirection() <<  " " << 
        pathwayCharacters.at(m).getFOIWind() <<  " " << pathwayCharacters.at(m).getFOISize() <<  " " << 
        pathwayCharacters.at(m).getFOICrown() <<  " " << pathwayCharacters.at(m).getFOIIgnition() <<  " " << 
        pathwayCharacters.at(m).getFOICover() <<  " " << pathwayCharacters.at(m).getFOIAspect() <<  " " << 
        pathwayCharacters.at(m).getFOISlope() <<  " " << pathwayCharacters.at(m).getFOIFuel() <<
        harvestPP0.at(o) <<  " " << harvestPPtotal.at(o) <<  " " << harvestPPAvg.at(o) <<  " " << 
        sclassPP0.at(o) <<  " " << sclassPP20.at(o) <<  " " << sclassPP50.at(o) <<  " " << sclassPPtotal.at(o) << " " << 
        finalLTV.at(o) << "\n";
        if(m % 10 == 0)
          o++;
    }

    pathOutput.close();
    fclose(inputs);
      
    
    //File for yearly averages.
    sprintf_s(name, "%sYearOutputs.txt", workingDirectory);
    FILE * yearOutput;
    fopen_s(&yearOutput, name, "w");
    fprintf_s(yearOutput, "Year Action ERC SC #Ignitions CrownFire SurfaceFire TotalBurned SuppressionCosts TimberLosses\n");

    for(int m = 0; m < (int)yearlyCharacters.size(); m++)
      yearlyCharacters.at(m).printAverageValues(yearOutput);

    fclose(yearOutput);

    // File for change in suppression costs and timber loss over each sample pathway.
    sprintf_s(name, "%sPairOutputs.txt", workingDirectory);
    FILE * pairOutput;
    fopen_s(&pairOutput, name, "w");
    fprintf_s(pairOutput, "FireOfInterest Pathway SuppressionSavings TimberLoss ValueChange\n");

    for(int m = 0; m < (int)pairCharacteristics.size(); m++)
      pairCharacteristics.at(m).printPairValues(pairOutput);

    fclose(pairOutput);

    // Bootstrapping proceedure.
    /*ProcessVariables meanBootstrap = ProcessVariables(pairCharacteristics);
    meanBootstrap.bootstrapFireOfInterest();

    // Fire of Interest outputs.
    vector<double> suppressionCosts;
    vector<double> timberLosses;

    Statistics runStats;
    int z = pairCharacteristics.at(0).getFireOfInterest();
    int k = 0;
    FILE * foiOutput;
    fopen_s(&foiOutput, "..\\foiOutput_37mil.txt", "w");
    fprintf(foiOutput, "FireOfInterest NumPaths AverageSuppressionSavings SDSuppressionSavings "
      "LowerSC UpperSC AverageTimberLoss SDTimberLoss LowerTL UpperTL\n");
    
    for(int m = 0; m < (int)pairCharacteristics.size() - 1; m)
    {
      int count = 0;
      bool check = 0;
      while(m < (int)pairCharacteristics.size() && z == pairCharacteristics.at(k).getFireOfInterest() ){
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
      z++;
    }
    fclose(foiOutput);*/

	return 0;
}


