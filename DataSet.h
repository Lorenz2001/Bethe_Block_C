#ifndef DATSET_H
#define DATSET_H

#include <vector>
#include <map>

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"

//Idea: Genero valori di ToF, Calcolo dE e la convulizzo con una gaussianaa
//
//
//
//

template <typename T>
struct Range{
    T min;
    T max;
};
class DataSet
{
private:
    
    std::map<int,Range> _map_charge_tof; //int = carica disponibile, Range = range del tof relativo a quella carica

    
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


class DataGenerator
{
private:

    int _ID;

    //ToF parameters
    Range<double> _range;
    double _mean;
    double _sigma;
    const char* _unit;
    

    RooDataSet _ToFGenerator();


public:
    DataGenerator(/* args */);
    ~DataGenerator();
};




DataGenerator::DataGenerator(/* args */)
{
}

DataGenerator::~DataGenerator()
{
}


#endif
