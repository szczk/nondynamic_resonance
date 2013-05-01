#ifndef _RANDOMS_HH_
#define _RANDOMS_HH_

#include <cmath>
#include <iostream>
#include <limits>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// #include "TH1D.h"


using namespace std;


/**
 * utility random numbers generator
 *
 *
 *
 * **** thread safety: yes, as long as every thread makes his own object 
 *             
 * 
 * IMPORTANT: when using multiple object, it is essential to properly seed every one with
 * different seed - use (void reset(unsigned long seed) )
 * 
 *
 * 
 */

class Randoms {

private:
    //static Randoms* INSTANCE;


    gsl_rng * generator;


    void init();
    void destroy();

    double m_drawSkewLevy(double alpha);

public:
//   static Randoms* getInstance();

    Randoms();
    Randoms(const Randoms &);
    Randoms& operator=(const Randoms&);

    ~Randoms();

    /**
     * Reset (reseed) random number generator
     */
    void reset();
    void reset(long unsigned int seed);

    double getUniform(double a, double b);
    double getGauss(double sigma);
    double getMittagLeffler(double beta); // w publikacji fulgera, par. beta nazywa sie alpha,  par. gamma = 1.0


    double getLevyStable(double alpha,double beta, double sigma, double mu);
    double getSkewLevy(double alpha);
//   double getGslSkewLevy(double alpha, double beta,double sigma);
//
//   double getLevy(double alpha);
    double getLevy2(double mu);
//   double getGslLevy(double alpha);
    double getExponential(double gamma);
    
    // losowanie z rozkladu
    // f(t) = lamba * e^(-lambda t)
    double getSpecialDist1(double lambda);

};

#endif
