#ifndef __GNUPLOT_SCRIPT_MAKER__
#define __GNUPLOT_SCRIPT_MAKER__


#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

#include "SNR.hh"
/**
 * 
 *  Simple tool that creates gnuplot script for drawing plots
 * 
 * 
 */



class GnuplotScriptMaker {
  
  
private:
  ofstream fout;
  int precision;
  const char * fileName;
  void init();
  void close();
  
  
  
public:
  GnuplotScriptMaker(const char * file);
  ~GnuplotScriptMaker();
  
  void addPowerSpectrumPlot(const char * freqsFile, const char * powerSpectrumFile, const char * plotFileName, SNR* snrObj, const char * plotTitle = 0);
  
  void addTrajectoryPlot(const char *timeFile, const char * trajectoryFile, const char * plotFileName, const char * plotTitle);
//   void addTrajectoryPlot( string trajectoryFile, string plotFileName);
  void setPrecision(int p);
};


#endif

