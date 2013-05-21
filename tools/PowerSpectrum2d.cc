#include "PowerSpectrum2d.hh"







PowerSpectrum2d:: PowerSpectrum2d(double * input, unsigned int n)
{
//  this->data = new double[n];
//  this->frequencies = new double[n];
//  this->pSpectrum = new double[n];
 
 this->fft_input = input;
 this->nPoints =n;
//  this->prepareComplexData();
 this->verbose = true;
 
 
//  for(int i=0;i<10;i++)
//  {
//   cout << "fftinput["<<i<<"] ="<<fft_input[i]<<endl; 
//  }
 
}


PowerSpectrum2d:: ~PowerSpectrum2d()
{
//   cout << "delete PS"<<endl;

//     delete this->fftRealResult; //0 - N/2
//     delete this->freq; // x
// //     delete this->pSpectrum; // P(freq)
//     delete this->fftdata;
//     
//     this->freq = NULL;
//     this->fftdata = NULL;
  this->clean();
}


void PowerSpectrum2d:: setDt(double dt)
{
  this->dt = dt;
}


void PowerSpectrum2d:: info()
{
  if(this->fft_input!=NULL)
  {
    cout << endl;
    cout << "N = " << this->nPoints << " nearest power of 2 = "<< nearestPowerOf2(this->nPoints)<< endl;
    cout << "DT = "<< this->dt << endl;
    cout << "N/2 + 1 = " << (this->nPoints/2) + 1 << endl;
    cout << "nyquist frequency: " << 1.0/(2.0*this->dt) << endl;
    cout << endl;
  }  
}


void PowerSpectrum2d:: clean()
{
//     delete[] this->frequencies;
//   this->frequencies =  NULL;
//    cout << "-PS clean(): delete input..."<<endl;
  delete[] this->fft_input;
  this->fft_input = NULL;
  
  delete[] this->pSpectrum;
  this->pSpectrum = NULL;
//    cout << "-PS clean():  fftw_clean..."<<endl;
  fftw_free(this->fft_output);
}

void PowerSpectrum2d:: printResult()
{
  cout << "-------------------"<<endl;
  cout << "fft result: " <<endl;
  
  for(int i =0; i < this->K; i++)
  {
   cout << "complex["<<i<<"]  =  ";
   cout << this->fft_output[i][0];
   cout << " + i " << this->fft_output[i][1] ;
   cout << endl; 
  }
  
}

void PowerSpectrum2d:: printSpectrum()
{
  cout << "-------------------"<<endl;
  cout << "calculated periodogram: " <<endl;
  
  for(int i =0; i < this->K; i++)
  {
   cout << "P["<<i<<"]  =  ";
   cout << this->pSpectrum[i];
   cout << endl; 
  }
  
}

void PowerSpectrum2d:: calculateFFT()
{
  this->K = (int)((this->nPoints/2.0)+1);
   // do actual fft  
   // input is already allocated
   
  int numThreads = 4;
  
  int init = fftw_init_threads();
  if(verbose) cout << "fftw_init_threads() = " << init <<endl;
  
  
   // allocate output
   this->fft_output = (fftw_complex*) fftw_malloc( sizeof(fftw_complex) * this->nPoints );
   
   
   
   fftw_plan_with_nthreads(numThreads);
   
//    cout << "-prepare fftw plan..."<<endl;
   fftw_plan plan = fftw_plan_dft_r2c_1d(nPoints, this->fft_input, this->fft_output, FFTW_ESTIMATE );

//    cout << "-execute fftw plan..."<<endl;
   fftw_execute(plan); 
   
   // cleanup
   fftw_destroy_plan(plan);
   
   fftw_cleanup_threads();
}


void PowerSpectrum2d:: calculatePowerSpectrum()
{
  int array_size = this->K;
 
//   double h = ((double) nPoints* ( double) nPoints);
//   cout << "nPoints="<< nPoints << "\tnPoints*nPoints = " << nPoints*nPoints << "\th = " <<h << endl;
  double norm = 1.0; // /(((double) nPoints* ( double) nPoints)); //  1.0/sqrt(this->nPoints);    
  
//   cout <<  "norm = " << norm << endl;
  
  this->pSpectrum = new double[array_size];
  
  this->pSpectrum[0] = norm * chop(this->fft_output[0][0])*chop(this->fft_output[0][0]);
  for(int j = 1; j< (array_size-1); j++)
    {
      this->pSpectrum[j] = norm *  (  chop(this->fft_output[j][0])* chop(this->fft_output[j][0]) + chop(this->fft_output[j][1]) * chop(this->fft_output[j][1])   );
      
      this->pSpectrum[j] = chop( this->pSpectrum[j] );
      
//       if(j > (array_size - 11)) cout << "pspectr ["<<j<<"]="<<pSpectrum[j]<<endl;
    }  
  this->pSpectrum[array_size-1] = norm * chop( this->fft_output[array_size-1][0])*chop(this->fft_output[array_size-1][0]);
  
}

void PowerSpectrum2d:: evaluate()
{
  if(verbose) cout << "- calculating FFT... "<<endl;
  this->calculateFFT();
  
  if(verbose) cout << "- calculating PS..." << endl;
  this->calculatePowerSpectrum();
}



/**
 *  Generate array of frequencies for given npoints and dt
 *  so it can be used as x-axis for plotting power spectrum
 *  from data made with the same parameters 
 * 
 * 
 *  note: returned array size will be the same as size of power spectrum array
 *  also, remember to delete result array when not needed anymore
 * 
 */
double * PowerSpectrum2d:: getFrequencies(unsigned int nPoints, double dt) 
{ 
  unsigned int array_size = (unsigned int)((nPoints/2.0)+1);
  double * frequencies = new double[array_size];

  double m = (((double)nPoints)*dt);
  for(unsigned int k =0 ; k < array_size; k++)
  {
    frequencies[k] = ((double) k)/(m);
  }
  
  return frequencies;  
}

/**
 * make a copy of  result and returns it
 */
double* PowerSpectrum2d:: getValues()
{
   double *fq = new double[this->K];
   memcpy(fq, this->pSpectrum, this->K* sizeof(fq[0]) );
   return fq;
}


/**
 *  fix numerical zeros ( change values like 1.0e-300 into 0.0)
 */
double PowerSpectrum2d:: chop(double k)
{
  double t = k;
  
  if( abs (t) < 1.0e-30) 
  {
//     cout << t << " => 0.0 "<<endl;
    t = 0.0;
  }
  return t;
}