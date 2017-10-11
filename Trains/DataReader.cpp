#include "DataReader.h"

#include <iostream>

DataReader::DataReader(string filename) {
    _filename = filename;
    try {
        openFile();
        read();
    }
    catch (exception e) {
        cout <<
            "An error occurred while attempting to open datafile:" << endl <<
            e.what() << endl;
    }
}


DataReader::~DataReader() {
    _infile.close();
}

vector<string> DataReader::getLines() const {
    return _lines;
}

void DataReader::openFile() {
    _infile.open(_filename);
    if (!_infile.is_open()) {
        throw runtime_error("Could not open " + _filename);
    }
}

void DataReader::read() {
    string line;
    while (getline(_infile, line)) {
        _lines.push_back(line);
    }
}
