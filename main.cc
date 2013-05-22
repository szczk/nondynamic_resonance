#include "main.hh"
#include <map>

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
    
	
	char additional_results_filename[200];
    sprintf(additional_results_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_additional_results.txt" , storagePath, alpha, skewness, threshold );
	ofstream additiona_results(additional_results_filename, ios_base::out);
	
	char frequencies_filename[200];
	char spectrum_filename[200];
	char plot_filename[200];
	char psplot_filename[200];
	
	
	map<double,double> * snrValues = new map<double,double>();
	map<double,double> * specAmplValues = new map<double,double>();
	
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
	    
		SNR snr(spectrumSize, averageSpectrum, omega, dt , true);
		
		
// 	    	cout << "fq"<<endl;
	        double * freqs = PowerSpectrum2d::getFrequencies(size, dt);
	    
			
// 			cout << "save" <<endl;
			 sprintf(frequencies_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_freq.txt" , storagePath, alpha, skewness, threshold , sigm);	

	        System::saveArray( frequencies_filename, freqs, spectrumSize );
	    
			
			

	    sprintf(spectrum_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_pspectr.txt" , storagePath, alpha, skewness, threshold , sigm);	
		System::saveArray( spectrum_filename, averageSpectrum, spectrumSize );
	    
		
		
		sprintf(plot_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_plot.gn" , storagePath, alpha, skewness, threshold , sigm);
		GnuplotScriptMaker * scriptMaker = new GnuplotScriptMaker(plot_filename);
		
		
	    
		
		sprintf(psplot_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_plot.png" , storagePath, alpha, skewness, threshold ,sigm );
		scriptMaker->addPowerSpectrumPlot(frequencies_filename, spectrum_filename, psplot_filename, &snr);
		
	    double snrVal = snr.getSNR();
		
		double eta = snr.getSpectralAmplification();
		
		
		snrValues->operator[](sigm) = snrVal;
		specAmplValues->operator[](sigm) = eta;
	    
	    results << sigm << "\t" << snrVal << "\t" << eta <<"\n";
	    
	    cout << "****************************************\n";
	    cout << "sigma = " << sigm << "\t spectral ampl=" << eta <<"\t SNR = " << snrVal <<"\n";
	    cout << "****************************************\n";
	    cout << flush;
	    
	    delete averageSpectrum;
        delete avps;
		delete scriptMaker;
    }
    
    results.close();
	
	
	//find maximums
	map<double,double>::iterator it;
	
	double max_snr = 0.0;
	double max_snr_sigma = 0.0;
	for (it=snrValues->begin(); it!=snrValues->end(); ++it)
	{
	  if(max_snr < it->second) {
		max_snr = it->second;
		max_snr_sigma = it->first;
	  }
	}
	double max_eta = 0.0;
	double max_eta_sigma = 0.0;
	for (it=specAmplValues->begin(); it!=specAmplValues->end(); ++it)
	{
	  if(max_eta < it->second) {
		max_eta = it->second;
		max_eta_sigma = it->first;
	  }
	}
	
	additiona_results << "#threshold\tsigma for max SNR \t  sigma for max eta\t maxSNR/maxETA\t maxETA/maxSNR\n";
	additiona_results <<threshold << setprecision(8) <<"\t"<< max_snr_sigma << "\t" << max_eta_sigma << "\t"<<(max_snr_sigma/max_eta_sigma) << "\t" <<(max_eta_sigma/max_snr_sigma) << endl;
	
    additiona_results.close();
    cout << "results saved to '" << results_filename <<"'"<<endl;
    
     //    cout << "del filtered" <<endl;
    //delete[] filtered;
    
//     cout << "del generator" <<endl;
    delete generator;
    
    
	delete snrValues;
	delete specAmplValues;
	
//     cout << "asdf"<<endl;
    delete rand;
    
    sys.finish();
    sys.printTimeSummary();
      
      
 return 0; 
}
