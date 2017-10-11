#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class DataReader
{
private:
    string _filename;
    ifstream _infile;
    vector<string> _lines;
    void openFile();
    void read();
public:
    DataReader(string);
    ~DataReader();
    vector<string> getLines() const;
};

#endif // !DATAREADER_H
