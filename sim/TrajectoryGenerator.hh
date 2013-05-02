#ifndef __TRAJECTORY_GENERATOR_HH__
#define __TRAJECTORY_GENERATOR_HH__

#include <cmath>
#include "Randoms.hh"
#include <iostream>

using namespace std;






class TrajectoryGenerator {

private:

  double dt;
  double max_t;
  double treshold;
  double omega;
  
  unsigned long signalLength;
  
  double getX(double &t);
  double filter( double & );
  
public:
  
  TrajectoryGenerator();
  ~TrajectoryGenerator();


  
  double * generateSignal();
  
  
  void setDt(double dt) { this->dt = dt; }
  
  void setTreshold(double t) { treshold = t; }
  double getTreshold() { return treshold; }

  
  void setOmega(double o) { omega = o; }
  double getOmega() { return omega; }
  
  
  void setSignalLength(unsigned long n) { signalLength = n;}
  unsigned long getSignalLength() { return signalLength; }
};


#endif

