 
#include "AveragePowerSpectrum.hh"






AveragePowerSpectrum:: AveragePowerSpectrum()
{
  this->inputValues = new vector<resultPrecisionType*>();
  this->size = 0;
  this->averagedValues = NULL;
}

AveragePowerSpectrum:: ~AveragePowerSpectrum()
{
  cout << "delete AVPS"<<endl;
  for(unsigned int i =0; i< this->inputValues->size();i++)
  {
    resultPrecisionType * k  = this->inputValues->at(i);
    delete[] k;
  }
  delete this->inputValues;
  if(this->averagedValues!=NULL) delete[] this->averagedValues;
  
  this->inputValues = NULL;
  this->averagedValues = NULL;
  
}


void AveragePowerSpectrum:: prepare()
{
  if(this->size>0)
  {
    this->averagedValues = new resultPrecisionType[this->size]; 
    for(unsigned int i=0;i<this->size;i++)
    {
      this->averagedValues[i] = 0.0;
    }
  }
}

void AveragePowerSpectrum:: count()
{
  this->nValueSets = this->inputValues->size();
}


void AveragePowerSpectrum:: calculateAverage()
{
  this->count();
  this->prepare();
  if(this->nValueSets>0)
  {
    cout << "-averaging " << this->nValueSets << " datasets. "<<endl;
    vector<resultPrecisionType*>::iterator it ;
    
//     long resultPrecisionType * sums = new long resultPrecisionType[this->size]; 
    
    for(it=this->inputValues->begin(); it != this->inputValues->end(); ++it)
    {
     resultPrecisionType * iv = (*it); 

     for(unsigned int i=0;i<this->size;i++)
     {
      this->averagedValues[i]+= iv[i]; 
     }     

     }    
    for(unsigned int i=0;i<this->size;i++)
     {
      resultPrecisionType s = this->averagedValues[i]; 
      this->averagedValues[i] = (s/((resultPrecisionType) this->nValueSets)); 
     }     
     
//      delete[] sums;
     
//      cout << endl;
  } 
     
//      cout << "averages: ";
//     
//      for(int i=30;i< 42 ;i++)
//      {
//        cout << this->averagedValues[i] << "  " ;      
//      }
//      cout << endl;
   
//      for(int i=0;i< 10 ;i++)
//      {
//        cout << i <<": ";
//        vector<resultPrecisionType*>::iterator it ;
//        for(it=this->inputValues->begin(); it != this->inputValues->end(); ++it)
// 	{
// 	resultPrecisionType * iv = (*it); 
// 	resultPrecisionType s = iv[i]; 
// 	cout << s  << "\t";
// 	}
// 	resultPrecisionType ss = this->averagedValues[i]; 
// 	cout << i<<": \t" << ss << endl;
//      } 

}



  
AveragePowerSpectrum::resultPrecisionType * AveragePowerSpectrum:: getAverage()
{
  this->calculateAverage(); 
  
  
  resultPrecisionType *av = new resultPrecisionType [this->size];
  memcpy(av, this->averagedValues, this->size* sizeof(av[0]) );
  
  return av;  
}


void AveragePowerSpectrum:: addValues(resultPrecisionType * v)
{
  if(this->isValid(v))
  {
   this->inputValues->push_back(v); 
  }
}

void AveragePowerSpectrum:: setSize(unsigned int n)
{
 this->size = n; 
}

bool AveragePowerSpectrum:: isValid(resultPrecisionType *v)
{
  bool ok = false;
  if(v!=0)
  {
    ok = (v[0]==v[0]); // detect NaN
  }
  return ok;
}

