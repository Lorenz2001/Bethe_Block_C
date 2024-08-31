#ifndef DATSET_H
#define DATSET_H

#include <vector>
#include <map>

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"


#include <Bethe_Block.h>

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



//? Generator of ToF and dE data for the input particle with charge z
class DataGenerator
{
private:

    //particle
    int _z;



    //ToF parameters
    Range<double> _range;
    double _mean;
    double _sigma;
    const char* _unit;

    //dE parameters
    double _resolution;

    //BetheBlock
    Bethe_Block* _BB;
    

    bool _ToF_Generator(const int N = 1E3/*Numbers of data generated*/);
    bool _dE_Generator(const int N = 1E3/*Numbers of data generated*/);


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
