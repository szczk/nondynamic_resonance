#ifndef _SETTINGS_HH_
#define _SETTINGS_HH_


#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;


// global settings class (singleton)

// reads settings file
// and provides access to parameters



class Settings {

public:
    /// GLOBAL PRECISION SETTINGS
    typedef double paramsType; /// these types are used in entire program
    typedef double resultType; /// using floats = 1/2 less memory needed
    ///*************************************************************************************

private:
    const char * settingsFile;

    map<string,paramsType> parameters;

    Settings(const char * sFile);
    ~Settings();

    void loadFromFile();

    void init();
    void close();

    unsigned long int calculateNpoints();
    unsigned long int calculatePeriodNpoints();

    // path for temporary files
    string tmpPath;

    // path for result files
    string storagePath;

    string normalizePath(const char *);

public:

    void setFile(const char * sFile= "settings.dat");
//     static Settings& getInstance();
    static Settings& getInstance(const char * sFile= "settings.dat");
    void printParameters();

    void dumpToFile(const char * sFile = "params.txt");

    paramsType get(const char * key) {
        return this->parameters[key];
    }

    void set(const char * key, paramsType value)
    {
        this->parameters[key] = value;
    }
    
    unsigned int getNtrajectories() {
        return ((unsigned int) this->get("ntrajectories"));
    }

    void setNtrajectories( unsigned int nt )
    {
        this->parameters["ntrajectories"] = nt;
    }

    paramsType getStartTime() {
        return this->parameters["starttime"];
    }

    unsigned long int getNpoints() {
        return this->calculateNpoints();
    }
    unsigned long int getPeriodNpoints() {
        return this->calculatePeriodNpoints();
    }

    paramsType getDt() {
        return this->parameters["dt"];
    }
    paramsType getJumpsParameter() {
        return this->parameters["alpha"];
    }
    paramsType getWaitingTimesParameter() {
        return this->parameters["beta"];
    }

    void setJumpsParameter( paramsType alpha) {
        this->parameters["alpha"] = alpha;
    }
    void setWaitingTimesParameter(paramsType beta ) {
        this->parameters["beta"] = beta;
    }

    
    /**
     * Read command line parameters, can be used to overwrite loaded params
     */
    void readCommandLineParameters( int argc, char **argv);


    void setTmpPath(const char * temp) {
        this->tmpPath = normalizePath(temp);
    }
    const char* getTmpPath() {
        return this->tmpPath.c_str();
    }

    void setStoragePath(const char * st) {
        this->storagePath = normalizePath(st);

    }
    const char* getStoragePath() {
        return this->storagePath.c_str();
    }
    
    void setNumThreads(unsigned int threads) { 
      this->parameters["NUM_THREADS"] = threads;
    }
    
    unsigned int getNumThreads() { 
      return this->parameters["NUM_THREADS"];
    }
};



#endif
