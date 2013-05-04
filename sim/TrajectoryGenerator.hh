#ifndef __TRAJECTORY_GENERATOR_HH__
#define __TRAJECTORY_GENERATOR_HH__

#include <cmath>
#include "Randoms.hh"
#include <iostream>

using namespace std;






class TrajectoryGenerator {

private:
  Randoms * rand;

  double dt;
  double max_t;
  double treshold;
  double omega;
  double noiseIntensity;
  double alpha;
  
  unsigned long signalLength;
  
  double getX(double &t);
  double filter( double & );
  
public:
  
  TrajectoryGenerator();
  ~TrajectoryGenerator();


  
  double * generateSignal();
  
  
  void setRandoms(Randoms * r) { this->rand = r; }
  
  void setDt(double dt) { this->dt = dt; }
  
  void setTreshold(double t) { treshold = t; }
  double getTreshold() { return treshold; }

  
  void setOmega(double o) { omega = o; }
  double getOmega() { return omega; }
  
  void setAlpha(double a) { this->alpha = a; }
  
  
  void setSignalLength(unsigned long n) { signalLength = n;}
  unsigned long getSignalLength() { return signalLength; }
  
  void setNoiseIntensity(double s) { noiseIntensity = s; }
};


#endif

