#include "GnuplotScriptMaker.hh" 




  

GnuplotScriptMaker:: GnuplotScriptMaker(const char * file)
{
  this->precision = 8;
  this->fileName = file;
  
  
  this->init();
}


GnuplotScriptMaker:: ~GnuplotScriptMaker()
{
  
 this->close(); 
}
  


void GnuplotScriptMaker:: init()
{
  cout << endl;
  cout << "GnuplotScriptMaker:: creating gnuplot script '" << this->fileName << "' ..."<<flush;
  
  
  this->fout.open(this->fileName,ios_base::trunc);
  if(this->fout.good())
  {
    cout << "ok.\n"<<flush;    
  }
  else
  {
    cout << "failed!\n"<<flush;    
  }
  
  this->fout << setprecision(this->precision);
}

void GnuplotScriptMaker:: close()
{
  cout << "GnuplotScriptMaker:: closing script '" << this->fileName << "' ..."<<flush;
  this->fout.close();
  if(!this->fout.is_open())
  {
    cout << "ok.\n"<<flush;    
  }
  else
  {
    cout << "failed!\n"<<flush;    
  }
}
  
void GnuplotScriptMaker:: setPrecision(int p)
{
  this->precision = p;
  this->fout << setprecision(this->precision);
}
  
void GnuplotScriptMaker:: addPowerSpectrumPlot(const char * freqsFile, const char * powerSpectrumFile, const char * plotFileName, SNR* snrObj, const char * plotTitle)
{
    fout << "\n";
    fout << "reset\n";
    fout << "set terminal png size 6000,700; \n";
    fout << "set out \""<< plotFileName <<"\"\n";
    fout << "set logscale;\n";
    if(plotTitle!=0) { fout << "set title \"" << plotTitle <<"\";\n"; }
    fout << "set label \"S = " << snrObj->getSignalStrength() << ", N = " << snrObj->getNoiseMean() <<" \\n SNR = " << snrObj->getSNR() << "\" at graph 0.5,0.95;\n";
    fout << "set arrow from " << snrObj->getNoiseMeanMinVal()<< "," << snrObj->getNoiseMean() 
	 << " to "<<  snrObj->getNoiseMeanMaxVal() << "," << snrObj->getNoiseMean() 
	 << " nohead lt 4 lw 3.2 lc rgbcolor '#FF0000'; \n";
//     fout << "plot '"<< powerSpectrumFile <<"' using 1:2 with linespoints notitle lc rgbcolor '#000000'; \n";
    fout << "plot \"<paste "<<freqsFile<<" "<< powerSpectrumFile <<"\" using 1:2 with linespoints notitle lc rgbcolor '#000000'; \n";
    fout << "\n";
    fout <<"unset logscale;\n";
    fout <<"unset label;\n";
    fout <<"unset arrow;\n";
}


void GnuplotScriptMaker:: addTrajectoryPlot(const char *timeFile, const char * trajectoryFile, const char * plotFileName, const char * plotTitle = 0)
{
    fout << "\n";
    fout << "reset\n";
    fout << "set terminal pngcairo enhanced size 6000,700;\n"; 
	fout << "set yrange [-1.5:1.5];\n";
    fout << "set out \""<<plotFileName<<"\";\n";
	fout << "set xlabel \"t\"\n";
	fout << "set ylabel \"<x>(t)\"\n";
	fout <<" set style line 1 lt 1 lc rgb \"gray\" lw 1\n";
	if(plotTitle!=0) { fout << "set title \"" << plotTitle <<"\";\n"; }
	 
// 	fout << "set title <x>(t)\n";
//     fout << "set yrange [-2:2];\n";
    fout << "plot 0.0 ls 1,'< paste "<<timeFile <<" "<<trajectoryFile<<"' using 1:2 with lines notitle lc rgbcolor '#000000';\n";
}
