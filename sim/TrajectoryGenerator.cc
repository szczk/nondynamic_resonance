#include "TrajectoryGenerator.hh"



TrajectoryGenerator:: TrajectoryGenerator() : omega(1.0)
{
  
  
}

TrajectoryGenerator:: ~TrajectoryGenerator()
{
  
}




double TrajectoryGenerator:: getX(double &t)
{
  double signal = sin( 2 * M_PI * omega * t);
  double noise = 0.0;
  
  
  return signal + noise;
}


double TrajectoryGenerator:: filter( double & x) 
{
  if(x > treshold) 
  {
    return 1.0;
  }
  else
  {
    return 0.0;
  }  
}




double * TrajectoryGenerator:: generateSignal() {
  
  double t = 0.0;
  double maxT = max_t;
  
  while(t < maxT)
  {
    
    
    
    
    
    t+= dt;
  } 
  
  
  
  
}
