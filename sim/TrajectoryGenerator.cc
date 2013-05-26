#include "TrajectoryGenerator.hh"



TrajectoryGenerator:: TrajectoryGenerator() : rand(NULL), treshold(0.0), omega(2.0), noiseIntensity(1.0),alpha(2.0)
{
  
  
}

TrajectoryGenerator:: ~TrajectoryGenerator()
{
  
}




double TrajectoryGenerator:: getX(double &t)
{
  double signal = sin( 2 * M_PI * omega * t);
  //M_SQRT1_2
  double noise = noiseIntensity *  rand->getLevyStable( alpha, skewness_beta, 1.0 , 0.0);
  
  
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
  double maxT = (signalLength-1)*dt;
  
//    cout << "maxT = " <<maxT<< " \t " << signalLength-1 << "\talpha=" << alpha << "\tnoise=" << noiseIntensity << endl;
  
  
  double * traj = new double[signalLength];
  int index = 1;
  
  traj[0] = 0.0;
  
  while(t < maxT)
  {
    
   double x = getX(t);
   
   //double y = filter(x);
   
//    cout << "t = " << t << "\tx(t)= " << x <<"\ty(x) = "<<y<<endl; 
   traj[index++] = x; 
   
   t+= dt;
  } 
  
  
  
  return traj;
}
