#include "DataReader.h"

DataReader::DataReader() {
    try {
        openFiles();
    }
    catch (exception e) {
        cout <<
            "An error occurred while attempting to open datafiles:" << endl <<
            e.what() << endl;
    }
}


DataReader::~DataReader() {
    
}

void DataReader::openFiles() {
    _trainsFile.open(_trainsFileName);
    _trainStationsFile.open(_trainStationsFileName);
    if (!_trainsFile.is_open()) {
        throw runtime_error("Could not open " + _trainsFileName);
    }
    if (!_trainStationsFile.is_open()) {
        throw runtime_error("Could not open " + _trainStationsFileName);
    }
}
