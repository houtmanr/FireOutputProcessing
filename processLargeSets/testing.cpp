#include "stdafx.h"
#include "ProcessVariables.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    char workingDirectory[100] = "..\\..\\Thesis\\harv38mil_100_199\\";
    char outputDirectory[50] = "\\outputs\\100_199_"; 
    char name[100];
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

    // This vector will be used to evaluate characteristics
    // across the years.
    vector<Characteristics> yearlyCharacters;

    // This vector will be used to evaluate characteristics 
    // for each suppress/let-burn pair.
    vector<Characteristics> pairCharacteristics;

    // This vector will be used to evaluate characteristics
    // for each fire of choice, across random futures.
    vector<Characteristics> foiCharacteristics;
  
    for(int j = 3; j < 4; j++)
    {
      printf("%d\n", j);
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

      }
    }
  return 0;
}