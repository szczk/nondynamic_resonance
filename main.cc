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
    rand->reset();
    
    double dt = settings.get("dt");
    double length_power = settings.get("signal_length_power");
    unsigned long size = (unsigned long) pow(2.0,length_power);
    double threshold = settings.get("treshold");
    double omega = settings.get("omega");
    double alpha = settings.get("levy_alpha");
    double skewness = settings.get("levy_beta");
    int repeats = settings.get("ntrajectories");
    
    
    
    
    
    double sigmaStart = settings.get("sigma_start");
    double sigmaEnd = settings.get("sigma_end");
    double sigmaInc = settings.get("sigma_inc");
    

    
    TrajectoryGenerator * generator = new TrajectoryGenerator();
    generator->setRandoms(rand);
    generator->setOmega(omega);
    generator->setDt(dt);
    generator->setSignalLength(size);
    generator->setAlpha(alpha);
    generator->setSkewness(skewness);
    
    
    const char * storagePath = settings.getStoragePath();
    
    char results_filename[200];
    sprintf(results_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_results.txt" , storagePath, alpha, skewness, threshold );
    ofstream results(results_filename, ios_base::out);
    
    for( double sigm = sigmaStart; sigm < sigmaEnd; sigm+=sigmaInc ) 
    {	
	    //if(sigm>2) sigmaInc = 0.4;
      
	    generator->setNoiseIntensity(sigm);
      

	    AveragePowerSpectrum * avps = new AveragePowerSpectrum();
	    
	    int spectrumSize = 0;
	    
	    for(int t = 0; t < repeats ; t++)
	    {
		//cout << "----------------------------------------------------------"<<endl;
		//cout << "iter = " << t << endl;
	      
		double * signal = generator->generateSignal();
		double * time = new double[size];
		
		double * filtered = new double[size];
	      
		for(unsigned int i = 0; i < size; i++)
		{
		  time[i] = i*dt;
		  filtered[i] = filter( threshold, signal[i]);
		}
	    //     cout << "save" <<endl;
	    //     System::saveArrays( "signal.txt", time, signal, size );
// 		System::saveArrays( "filtered.txt", time, filtered, size );
	    // 
	    //     
	    //     cout << "fft" <<endl;
	    //     
		PowerSpectrum2d * pSpec = new PowerSpectrum2d( filtered, size );
		pSpec->setVerbose(false);
		pSpec->setDt(dt);
		pSpec->evaluate();
// 		pSpec->info();
		
	    //     cout << "spec"<<endl;
		double * spectrum = pSpec->getValues();
		
		spectrumSize = pSpec->getK();
		
		avps->setSize(spectrumSize);
		
		avps->addValues(spectrum);
		
	    //     cout << "save" << endl;
	    //     System::saveArray( "pspectrum.txt", spectrum, spectrumSize );
		
	    //     cout << "fq"<<endl;
	    //     double * freqs = PowerSpectrum2d::getFrequencies(size, dt);
	    //     cout << "save" <<endl;
	    //     System::saveArray( "freqs.txt", freqs, spectrumSize );
		
	    //     cout << "snr"<<endl;
		
		
		
	    //     cout << "del signal" <<endl;
		delete[] signal;
	    //     cout << "del time" <<endl;
		delete[] time;

	    //     cout << "del freqs" <<endl;
	    //     delete[] freqs; 
		
	    //     cout << "del spectrum" << endl;
		//delete[] spectrum;
		
	    //     cout << "del pSpec" <<endl;
		delete pSpec;
	    
	    }
	    double * averageSpectrum = avps->getAverage();
	    
// 	    	cout << "fq"<<endl;
// 	        double * freqs = PowerSpectrum2d::getFrequencies(size, dt);
// 	        cout << "save" <<endl;
// 	        System::saveArray( "freqs.txt", freqs, spectrumSize );
	    
// 		System::saveArray( "pspectrum.txt", averageSpectrum, spectrumSize );
	    
	    SNR snr(spectrumSize, averageSpectrum, omega, dt , false);
	    double snrVal = snr.getSNR();
		
		double eta = snr.getSpectralAmplification();
	    
	    results << sigm << "\t" << snrVal << "\t" << eta <<"\n";
	    
	    cout << "****************************************\n";
	    cout << "sigma = " << sigm << "\t spectral ampl=" << eta <<"\t SNR = " << snrVal <<"\n";
	    cout << "****************************************\n";
	    cout << flush;
	    
	    delete averageSpectrum;
            delete avps;
    }
    
    results.close();
    
    cout << "results saved to '" << results_filename <<"'"<<endl;
    
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
