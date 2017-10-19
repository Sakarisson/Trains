#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <fstream>
#include <vector>

class DataReader
{
public:
    DataReader(std::string);
    ~DataReader();
    std::vector<std::string> getLines() const;
private:
    std::string _filename;
    std::ifstream _infile;
    std::vector<std::string> _lines;
    void openFile();
    void read();
};

#endif // !DATAREADER_H
