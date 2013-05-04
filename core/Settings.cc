#include "Settings.hh"




Settings& Settings::getInstance(const char * sFile)
{

    static Settings instance(sFile);

    return instance;
}



void Settings::readCommandLineParameters(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if ( strcmp ("--alpha",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new alpha: " << atof(argv[i+1]) <<endl;
            this->set("levy_alpha", atof(argv[i+1])) ;
        }
        if ( strcmp ("--beta",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new beta: " << atof(argv[i+1]) <<endl;
            this->set("levy_beta", atof(argv[i+1])) ;
        }
        if ( strcmp ("--omega",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new omega: " << atof(argv[i+1]) <<endl;
            this->set("omega", atof(argv[i+1])) ;
        }

        if ( strcmp ("--tmp",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new temp path:: '" << argv[i+1] << "'" << endl;
            this->setTmpPath(argv[i+1]) ;
        }

        if ( strcmp ("--storage",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new storage path: '" << argv[i+1] << "'" << endl;
            this->setStoragePath(argv[i+1]) ;
        }
        
        if ( strcmp ("--n",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new n: '" << argv[i+1] << "'" << endl;
            this->setNtrajectories(atoi(argv[i+1]));
        }
        
        if ( strcmp ("--threads",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " number of threads: '" << argv[i+1] << "'" << endl;
            this->setNumThreads(atoi(argv[i+1]));
        }

        if ( strcmp ("--threshold",argv[i]) == 0  && (i+1) < argc )
        {
            cout << " new threshold: '" << argv[i+1] << "'" << endl;
            this->set("treshold",atof(argv[i+1]));
        }
        
    }
}


Settings:: Settings(const char * sFile)
{
    this->settingsFile = sFile;
    this->init();
}

Settings:: ~Settings()
{
    this->close();
}


void Settings:: init()
{
    this->setStoragePath("./");
    this->setTmpPath("/tmp/");

    this->loadFromFile();
}

void Settings:: close()
{
    cout << "removing Settings..."<<flush;

    // nothing here...

    cout << "ok." <<endl;
}

void Settings:: loadFromFile()
{
    cout << " Reading file:" << this->settingsFile << ""<<endl;
    ifstream settings(this->settingsFile,ios_base::in);

    //read file
    string line;

    string paramName;
    paramsType paramValue;

    if (settings.is_open())
    {
        while ( settings.good() )
        {
            getline (settings,line);
            if (line[0] =='#' || line.size()<1) continue;

            stringstream sline(line);

            string a;
            if ( getline(sline,a,'=') )
            {
                paramName = a;
                paramName.erase(0, paramName.find_first_not_of(' '));       //trim prefixing spaces
                paramName.erase(paramName.find_last_not_of(' ')+1);         //trim surfixing spaces

// 	cout <<"'" << paramName << "'"<<endl;
                if (paramName.size()==0)
                {
                    //string trimmed to 0
                    continue;
                }
                sline >> paramValue;

                this->parameters.insert( pair<string,paramsType>(paramName,paramValue) );
            }

        }
        settings.close();
    }

//   settings.close();
}


void Settings:: printParameters()
{
    map<string,paramsType>::iterator it;
    for ( it=this->parameters.begin() ; it != this->parameters.end(); it++ )
    {
        cout << (*it).first << " = " << (*it).second << endl;
    }

    cout << "\n\n" << flush ;
}


// dump parameters to file
void Settings:: dumpToFile(const char * sFile)
{
    ofstream fout(sFile,ios_base::trunc);

/*
    fout << "trajectory length: " << this->parameters["num_of_periods"] << " * 2^(" << this->parameters["length_power"] << ")";
    fout << setprecision(30) << " = " << this->calculateNpoints() << setprecision(3)<< endl;

    fout << "jumps parameter: \n alpha = " << this->parameters["alpha"] <<endl << endl;
    fout << "waiting time parameter:\n beta = " << this->parameters["beta"] <<endl << endl;


    fout << "time step: \n dt = " << this->parameters["dt"] <<endl << endl;
    fout << "start time: \n t0 = " << this->parameters["starttime"] <<endl << endl;

    fout << "------------------------------------------" << endl;*/

    map<string,paramsType>::iterator it;
    for ( it=this->parameters.begin() ; it != this->parameters.end(); it++ )
    {
        fout << (*it).first << " = " << (*it).second << endl;
    }
    fout << endl;

    fout.close();
}

unsigned long int Settings:: calculateNpoints()
{
    return ((unsigned long int) (this->parameters["num_of_periods"] * pow(2.0, this->parameters["length_power"] )));
}

unsigned long int Settings:: calculatePeriodNpoints()
{
    return ((unsigned long int) (pow(2.0, this->parameters["length_power"] )));
}

string  Settings::normalizePath(const char* str)
{
    string cc(str);
//     if ( cc.at( cc.length() -1 ) != '/' )
//     {
//         cc.append("/");
//         cerr << "Settings:: fixing path '" << str << "' to '" << cc <<"'" << endl;
//     }
    return cc;
}

