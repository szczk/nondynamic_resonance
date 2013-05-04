#ifndef SNR_HH_
#define SNR_HH_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "Settings.hh"

using namespace std;




class SNR {
  
private:
  
  typedef Settings::paramsType paramsPrecisionType;
  typedef Settings::resultType resultPrecisionType; //using floats = 1/2 less memory needed 
  
  double maxValue;
  double signalStrength;
  double noiseMean;
  int maxValueIndex;
  
  // border values for calculating noise mean
  double noiseMean_minVal;
  double noiseMean_maxVal;
  
  //paramsPrecisionType * frequencies; // frequencies array
  resultPrecisionType * values;	// values array , sizes should match
  
  unsigned int nPoints;
  
  paramsPrecisionType inputSignalFrequency;
  paramsPrecisionType dt;
  double snrValue;
  
  void findMaxValue();
  
  bool verbose;
  
public:
  SNR(unsigned int npoints, resultPrecisionType * values, paramsPrecisionType inputSignalFrequency, paramsPrecisionType dt , bool verbose );
  ~SNR();
  
  
  //void setFrequencies(paramsPrecisionType * f) { this->frequencies = f; }
  void setDt(paramsPrecisionType d) { this->dt = d;}
  
  double getSignalStrength() { return this->signalStrength; }
  double getNoiseMean() { return this->noiseMean; }
  double getMaxValue() { return this->maxValue; }
  int getMaxValueIndex() { return this->maxValueIndex; }
  double getSNR() { return this->snrValue; }
  
  double getNoiseMeanMinVal(){return this->noiseMean_minVal;}
  double getNoiseMeanMaxVal(){return this->noiseMean_maxVal;}
  
  void setVerbose(bool v) { this->verbose = v; }
};

#endif









