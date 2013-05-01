#ifndef __TRAJECTORY_GENERATOR_HH__
#define __TRAJECTORY_GENERATOR_HH__

#include <cmath>
#include "core/Randoms.hh"

using namespace std;






class TrajectoryGenerator {

private:

  double dt;
  double max_t;
  double treshold;
  double omega;
  
  
  double getX(double &t);
  double filter( double & );
  
public:
  
  TrajectoryGenerator();
  ~TrajectoryGenerator();


  
  double * generateSignal();
  
  
  
  void setTreshold(double t) { treshold = t; }
  double getTreshold() { return treshold; }

  
  void setOmega(double o) { omega = o; }
  double getOmega() { return omega; }
};


#endif

