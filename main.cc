#include "main.hh"
#include <map>
#include "TH1D.h"
#include "TCanvas.h"

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
    
	results << "#" << "alpha\tsigma\tSNR\teta\n";
    
	char additional_results_filename[200];
    sprintf(additional_results_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_additional_results.txt" , storagePath, alpha, skewness, threshold );
	ofstream additiona_results(additional_results_filename, ios_base::out);
	
// 	char frequencies_filename[200];
// 	char spectrum_filename[200];
// 	char plot_filename[200];
// 	char psplot_filename[200];
	
	
	TCanvas * canvas = new TCanvas("canvas","canvas",10, 10, 800,600);
	
	map<double,double> * snrValues = new map<double,double>();
	map<double,double> * specAmplValues = new map<double,double>();
	
    for( double sigm = sigmaStart; sigm < sigmaEnd; sigm+=sigmaInc ) 
    {	
	    //if(sigm>2) sigmaInc = 0.4;
      
	    generator->setNoiseIntensity(sigm);
      
		char residence_times_filename[200];
		sprintf(residence_times_filename, "alpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma_%2.2f" , alpha, skewness, threshold, sigm );
		
		TH1D * residenceTimes = new TH1D(residence_times_filename,residence_times_filename,10000,0.0,10.0);
	    AveragePowerSpectrum * avps = new AveragePowerSpectrum();
	    
	    int spectrumSize = 0;
	    
	    for(int t = 0; t < repeats ; t++)
	    {
		//cout << "----------------------------------------------------------"<<endl;
		//cout << "iter = " << t << endl;
	      
		double * signal = generator->generateSignal();
		double * time = new double[size];
		
		double * filtered = new double[size];
	      
		
		bool inUp = false;
		double upStart = 0.0;
		for(unsigned int i = 0; i < size; i++)
		{
		  time[i] = i*dt;
		  filtered[i] = filter( threshold, signal[i]);
		  
		  
		  
		  if(i>0) {
			
			
// 			  cout <<"i = " << i << "\tx(t="<< time[i] <<")="<<signal[i]<<"\ty(t)="<<filtered[i]<<endl;
			
			if( filtered[i] == 0  &&  inUp )
			{
			  upStart = time[i];
			  inUp = false;
			}
			
			if( filtered[i] == 1 &&  !inUp )
			{
			  inUp = true;
			  double duration = time[i] - upStart;
			  residenceTimes->Fill( duration  *omega ); //
			}
			
			
		  }
		}
// 	        cout << "save" <<endl;

// 	  if(t==10) {
// 		char traj_filename[200];
// 		sprintf(traj_filename, "alpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma_%2.2f_t_%i.txt" , alpha, skewness, threshold, sigm , t );  
// 		
//         char filtered_traj_filename[200];
// 		sprintf(filtered_traj_filename, "alpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma_%2.2f_ft_%i.txt" , alpha, skewness, threshold, sigm , t );
// 		
// 	    System::saveArrays( traj_filename, time, signal, size );
// 		System::saveArrays( filtered_traj_filename, time, filtered, size );
// 	  }
	    // 
	    //     
// 	        cout << "fft" <<endl;
	    //     
		PowerSpectrum2d * pSpec = new PowerSpectrum2d( filtered, size );
		pSpec->setVerbose(false);
		pSpec->setDt(dt);
		pSpec->evaluate();
// 		pSpec->info();
		
// 	        cout << "spec"<<endl;
		double * spectrum = pSpec->getValues();
// 		 cout << "spec"<<endl;
		spectrumSize = pSpec->getK();
		
		avps->setSize(spectrumSize);
// 		 cout << "add values"<<endl;
		avps->addValues(spectrum);
		
	    //     cout << "save" << endl;
	    //     System::saveArray( "pspectrum.txt", spectrum, spectrumSize );
		
	    //     cout << "fq"<<endl;
	    //     double * freqs = PowerSpectrum2d::getFrequencies(size, dt);
	    //     cout << "save" <<endl;
	    //     System::saveArray( "freqs.txt", freqs, spectrumSize );
		
	    //     cout << "snr"<<endl;
		
		
		
// 	        cout << "del signal" <<endl;
		delete[] signal;
// 	        cout << "del time" <<endl;
		delete[] time;

	    //     cout << "del freqs" <<endl;
	    //     delete[] freqs; 
		
	    //     cout << "del spectrum" << endl;
		//delete[] spectrum;
		
// 	        cout << "del pSpec" <<endl;
		delete pSpec;
	    
	    }
	    double * averageSpectrum = avps->getAverage();
	    
		SNR snr(spectrumSize, averageSpectrum, omega, dt , true);
		
		
// 	    	cout << "fq"<<endl;
// 	        double * freqs = PowerSpectrum2d::getFrequencies(size, dt);
	    
			
// 			cout << "save" <<endl;
// 			 sprintf(frequencies_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_freq.txt" , storagePath, alpha, skewness, threshold , sigm);	

// 	        System::saveArray( frequencies_filename, freqs, spectrumSize );
// 		delete[] freqs;
			
			

// 	    sprintf(spectrum_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_pspectr.txt" , storagePath, alpha, skewness, threshold , sigm);	
// 		System::saveArray( spectrum_filename, averageSpectrum, spectrumSize );
	    
		
		
// 		sprintf(plot_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_plot.gn" , storagePath, alpha, skewness, threshold , sigm);
// 		GnuplotScriptMaker * scriptMaker = new GnuplotScriptMaker(plot_filename);
		
// 		sprintf(psplot_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma%2.2f_plot.png" , storagePath, alpha, skewness, threshold ,sigm );
// 		scriptMaker->addPowerSpectrumPlot(frequencies_filename, spectrum_filename, psplot_filename, &snr);
		
		double snrVal = snr.getSNR();
		
		double eta = snr.getSpectralAmplification();
		
		
		snrValues->operator[](sigm) = snrVal;
		specAmplValues->operator[](sigm) = eta;
	    
	    results << alpha << "\t" << sigm << "\t" << snrVal << "\t" << eta <<"\n";
	    
	    cout << "****************************************\n";
	    cout << "sigma = " << sigm << "\t spectral ampl=" << eta <<"\t SNR = " << snrVal <<"\n";
	    cout << "****************************************\n";
	    cout << flush;
	    
	    delete averageSpectrum;
        delete avps;
// 		delete scriptMaker;
		
		residenceTimes->Draw();
		residenceTimes->SetXTitle("t/T");
		canvas->Update();
		canvas->Draw();
		
		
// 		char residence_times_filename[200];
		sprintf(residence_times_filename, "%salpha_%2.2f_beta_%2.2f_thr_%2.2f_sigma_%2.2f.png" , storagePath, alpha, skewness, threshold, sigm );
		
// 		
		canvas->Print(residence_times_filename,"png");
		
		delete residenceTimes;
    }
    
    delete canvas;
    
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
	
	additiona_results << "#alpha\t beta \t threshold\t sigma_opt \t eta_max \t SNR_sigma_opt\n";
	additiona_results << alpha << "\t" << skewness << "\t" << threshold << "\t" << setprecision(4) << max_eta_sigma << "\t" << max_eta << "\t" << max_snr_sigma << endl;

	
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
