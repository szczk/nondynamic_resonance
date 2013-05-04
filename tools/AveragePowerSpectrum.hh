#ifndef AVERAGE_POWER_SPECTRUM
#define AVERAGE_POWER_SPECTRUM

#include <vector>
#include <iostream>
#include <string.h>
#include "Settings.hh"

using namespace std;

/**
 * 
 * 
 * just a very simple tool
 * 
 * 
 * 
 * usage: 
 * 
 * create new object
 * setSize()
 * 
 * -> addValues(*)
 * 
 * <- getAverage()
 * 
 * delete
 * 
 * 
 * when deleted, everything gets deleted (including input arrays)
 * except array returned by getAverage() (which is a copy, so must be deleted manually when not needed)
 * 
 * 
 * 
 * 
 * warning: it should not be used for large number of trajectories 
 * (no overflow protection)
 */





class AveragePowerSpectrum {
  
private:
  
  typedef Settings::paramsType paramsPrecisionType;
  typedef Settings::resultType resultPrecisionType; //using floats = 1/2 less memory needed 
  
  unsigned int size; //size of value array
  unsigned int nValueSets; // how many arrays to average
  vector<resultPrecisionType*> *inputValues ; // vector of arrays, all have to have same size!

  resultPrecisionType * averagedValues;
  
  void count();
  void prepare();
  void calculateAverage();
  
  
  
public:
  AveragePowerSpectrum();
  ~AveragePowerSpectrum();
  void addValues(resultPrecisionType *);
  
  void setSize(unsigned int n);
  resultPrecisionType * getAverage();
  int getSize() { return this->size;} 
  
  bool isValid(resultPrecisionType *v);
  
  
};








#endif