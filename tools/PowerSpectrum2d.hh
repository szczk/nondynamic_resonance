#ifndef _POWER_SPECTRUM_2D_
#define _POWER_SPECTRUM_2D_

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <fftw3.h>
// #include "TGraph.h"
// #include "TPaveText.h"
using namespace std;



/**
 *  Calculate power spectrum
 * 
 * whene deleted, everything gets destroyed except 
 * results array (array returned by getValues() )
 * with type *double[npoints/2 +1] 
 * It should be deleted manually when not needed!
 */

// same as PowerSpectrum2d but using doubles (less memory)

class PowerSpectrum2d {
  
private:
    unsigned int nPoints;
    int K; // npoints/2 + 1
    double * fft_input; //y
    fftw_complex * fft_output; // array of type double[2]   => [re][im]
    
    double dt;
    

    double * pSpectrum; // P(freq)
    //double * frequencies; // x
    
//     void prepareComplexData();
//     void prepareGraph();
    
    bool verbose;
    
    void calculateFFT();
    void calculatePowerSpectrum();
    
    double chop(double v);
    
public:
   PowerSpectrum2d(double * input, unsigned int size);
  ~PowerSpectrum2d();
  
  
   void info();
  
  
   void setDt(double dt);
  
   void evaluate();
   void clean();
   
   void printData();
   void printResult();
   void printSpectrum();
   
//    TGraph * getGraph();
   void draw();
   
   static double * getFrequencies(unsigned int nPoints, double dt);
   double * getValues();
   int getK() { return this->K;} // k = npoints/2 + 1   
  
   void setVerbose(bool v) { this->verbose = v; }
  
   static int nearestPowerOf2( int n )
    {
	    return (unsigned) pow( 2, ceil( log( n ) / log( 2 ) ) );
    }
};




#endif