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
    
  
  
    
    
    
  
  
    cout << "asdf"<<endl;
    
    
    sys.finish();
    sys.printTimeSummary();
      
      
 return 0; 
}
