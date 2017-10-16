#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <fstream>
#include <vector>

class DataReader
{
private:
    std::string _filename;
    std::ifstream _infile;
    std::vector<std::string> _lines;
    void openFile();
    void read();
public:
    DataReader(std::string);
    ~DataReader();
    std::vector<std::string> getLines() const;
};

#endif // !DATAREADER_H
