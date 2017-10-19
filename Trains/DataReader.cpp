#include "DataReader.h"

DataReader::DataReader(std::string filename) {
    _filename = filename;
    openFile();
    read();
}


DataReader::~DataReader() {
    _infile.close();
}

std::vector<std::string> DataReader::getLines() const {
    return _lines;
}

void DataReader::openFile() {
    _infile.open(_filename);
    if (!_infile.is_open()) {
        throw std::runtime_error("Could not open " + _filename);
    }
}

void DataReader::read() {
    std::string line;
    while (getline(_infile, line)) {
        _lines.push_back(line);
    }
}
