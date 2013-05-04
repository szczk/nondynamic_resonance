#include "main.hh"


using namespace std;


double filter(double & treshold, double & x) 
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

int main(int argc, char ** argv) {
    cout << endl << endl;

    System& sys = System::getInstance();
    sys.start();
    
    
    Settings& settings = Settings:: getInstance ( "settings.dat" );
    
    settings.readCommandLineParameters ( argc,argv );
    settings.printParameters();
    settings.dumpToFile ( "params.txt" );
    
  
    Randoms * rand = new Randoms();
    
    double dt = 0.01;
    unsigned long size = (unsigned long) pow(2.0,24.0);
    double tresh = 1.0;
    double omega = 2.0;
    double sigma = 2.0;
    
//     cout << "size=" <<size <<endl;
    
    TrajectoryGenerator * generator = new TrajectoryGenerator();
    generator->setRandoms(rand);
    generator->setOmega(omega);
    generator->setDt(dt);
    generator->setSignalLength(size);
    generator->setNoiseIntensity(sigma);
    
    generator->setAlpha(2.0);
    
    
    

    double * signal = generator->generateSignal();
    double * time = new double[size];
    
    double * filtered = new double[size];
   
    for(unsigned int i = 0; i < size; i++)
    {
      time[i] = i*dt;
      filtered[i] = filter( tresh, signal[i]);
    }
//     cout << "save" <<endl;
//     System::saveArrays( "signal.txt", time, signal, size );
//     System::saveArrays( "filtered.txt", time, filtered, size );
// 
//     
//     cout << "fft" <<endl;
//     
    PowerSpectrum2d * pSpec = new PowerSpectrum2d( filtered, size );
    pSpec->setDt(dt);
    pSpec->evaluate();
    pSpec->info();
    
//     cout << "spec"<<endl;
    double * spectrum = pSpec->getValues();
    
    int spectrumSize = pSpec->getK();
//     cout << "save" << endl;
//     System::saveArray( "pspectrum.txt", spectrum, spectrumSize );
    
//     cout << "fq"<<endl;
//     double * freqs = PowerSpectrum2d::getFrequencies(size, dt);
//     cout << "save" <<endl;
//     System::saveArray( "freqs.txt", freqs, spectrumSize );
    
//     cout << "snr"<<endl;
    SNR snr(spectrumSize, spectrum, omega, dt );
    
    snr.getSNR();
    
    
//     cout << "del signal" <<endl;
    delete[] signal;
//     cout << "del time" <<endl;
    delete[] time;

//     cout << "del freqs" <<endl;
//     delete[] freqs; 
    
//     cout << "del spectrum" << endl;
    delete[] spectrum;
    
//     cout << "del pSpec" <<endl;
    delete pSpec;
    
    
     //    cout << "del filtered" <<endl;
    //delete[] filtered;
    
//     cout << "del generator" <<endl;
    delete generator;
    
    
	
	
//     cout << "asdf"<<endl;
    delete rand;
    
    sys.finish();
    sys.printTimeSummary();
      
      
 return 0; 
}
