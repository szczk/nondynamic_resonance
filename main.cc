#include "main.hh"


using namespace std;




int main(int argc, char ** argv) {
    cout << endl << endl;

    System& sys = System::getInstance();
    sys.start();
    
    
    Settings& settings = Settings:: getInstance ( "settings.dat" );
    
    settings.readCommandLineParameters ( argc,argv );
    settings.printParameters();
    settings.dumpToFile ( "params.txt" );
    
  
  
    
    
    
	TrajectoryGenerator * generator = new TrajectoryGenerator();
  
	generator->setDt(0.01);
	generator->setSignalLength(100);
	
	generator->generateSignal();
	
  
	
	delete generator;
    cout << "asdf"<<endl;
    
    
    sys.finish();
    sys.printTimeSummary();
      
      
 return 0; 
}
