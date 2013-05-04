#include "SNR.hh" 




  

SNR:: SNR(unsigned int n, resultPrecisionType * val, paramsPrecisionType inputFQ, paramsPrecisionType DT )
{
  this->nPoints = n;
  this->values = val;
  this->inputSignalFrequency = inputFQ;
  this->setDt(DT);
  this->findMaxValue();
}

SNR:: ~SNR()
{
  
}
  
  
  
void SNR::findMaxValue()
{
  this->signalStrength = 0.0;
  this->noiseMean = 0.0;
  this->maxValue = 0.0;
  this->maxValueIndex = 0;
  
   // npoints to lizczba punktow w tablicy z power spectrum
  
   // ale czestotliwosci sa co k/N*dt  gdzie N to liczba punktów z input!!
    // dlatego tu powinno by 2.0 *   bo N = 2* npoints
  
  /// update: nie zupelnie N = 2*points
  /// raczej jest  npoints = (N/2 + 1)
  
  /// wiec   N  = 2 * (npoints - 1)

    unsigned int index = (unsigned int) (inputSignalFrequency*((double)( (2.0*((double) (this->nPoints-1))) *this->dt)));
    
    // dont use this
    this->maxValueIndex = index;
    this->maxValue = this->values[index];
    //====================
    
    
    this->signalStrength = (double) this->values[index];
    
    cout << "SNR: input signal frequency: " << this->inputSignalFrequency << endl;
    cout << "match index:"<<index<< " ( index/(N*dt) = " << index/(2.0* ((double) nPoints)*dt)  << ")"<< endl;
    
    for(unsigned int j =  index - 4; j < index + 5 ;j++)
    {
     cout << "snr[" << j << " => f=" << setprecision(8) << j/(2.0* ((double) nPoints)*dt) <<"] = " << setprecision(5) <<values[j]<< endl;
    }
    
//     cout << "SNR: closest match ("<< indexes->size() <<"): f["<<this->maxValueIndex<<"] = " << this->frequencies[this->maxValueIndex] << endl;
   
    unsigned int oldIndex = index;
   /// manually search near index to find better (bigger) values
    
    for(unsigned int j =  oldIndex - 6; j < oldIndex + 6 ;j++)
    {
      double nw = (double) values[j];
      
      if(nw > signalStrength)
      {
	cerr << "nw= "<< nw << ", signalStrength="<<signalStrength;
	cerr <<", index = " << index << ", j = "<< j << endl;
	
	index = j;
	this->signalStrength = nw;
	
	cout << " better max value found : ";
	cout << "snr[" << j << " => f=" << setprecision(8) << j/(2.0* ((double) nPoints)*dt) <<"] = " << setprecision(5) <<values[j]<< endl;
      }
    }
    
    
    
//     delete indexes;
    
    // find noise level
    int nVal = 0;
    unsigned int M = 14;
    long double mean_val = 0.0;
    
//     long double check = 0.0;
    
    for(unsigned int j = 3; j < M ; j++)
    {
//       cout << "this->values[maxValueIndex - j]="<<this->values[maxValueIndex - j] <<"\t this->values[maxValueIndex + j]="<<this->values[maxValueIndex + j]<< endl;
//       noiseMean+= (this->values[maxValueIndex - j]  + this->values[maxValueIndex + j]);
//       nVal+=2;

	long double m2 = 0.0;
	
	if(index - j >= 0)
	{
	   m2 += this->values[index - j];
	   nVal++;
	   
	}
	
	if(index + j < this->nPoints)
	{
	   m2+=this->values[index + j];
	   nVal++;
	}
// 	cout << "m2 = " << m2 <<endl;
	mean_val = ((mean_val*(nVal-2)) + m2)/nVal;
// 	cout << "mean_val = " << mean_val << endl;
    }
    this->noiseMean_minVal =  ((double) (maxValueIndex - (M-1) ) )/( (((double)(2.0*this->nPoints*this->dt))));
    this->noiseMean_maxVal = ((double) (maxValueIndex + (M-1) ) )/( (((double)(2.0*this->nPoints*this->dt))));
    cout << "noiseMean_minVal = " <<  this->noiseMean_minVal << endl;
    cout << "noiseMean_maxVal = " <<  this->noiseMean_maxVal << endl;
    
//     noiseMean = (noiseMean)/((double)nVal);
    noiseMean = mean_val;
    
    cout <<" signal strength: " << this->signalStrength <<  "\t\tnoise mean="<< this->noiseMean <<endl;

    if( this->noiseMean != 0.0 )
    {
    snrValue = this->signalStrength/(this->noiseMean);
    }
    else
    {
     snrValue = 0.0;
     cerr<< " SNR:: noiseMean = 0! " <<endl;
    }
    
//     cout << "noise mean: " << noiseMean << endl;
     cout << "SNR value =  " << snrValue <<endl;
}
