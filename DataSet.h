#ifndef DATSET_H
#define DATSET_H

#include <vector>

class DataSet
{
private:
    std::vector<bool> _charges; //1 if the charge is aviable, 0 otherwise
public:
    DataSet(/* args */);
    ~DataSet();
};

DataSet::DataSet(/* args */)
{
}

DataSet::~DataSet()
{
}

#endif
