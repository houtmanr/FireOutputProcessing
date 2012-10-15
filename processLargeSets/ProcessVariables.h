#pragma once
#include "Characteristics.h"

class ProcessVariables{
public:

  ProcessVariables(vector<Characteristics> pVariables);
  void yearlyVariables();
  void pairSamplePathways();
  void differenceSamplePathways();
  void bootstrapFireOfInterest();
  void fireOfInterest();

  ~ProcessVariables();
private:
  vector<Characteristics> variables;
};