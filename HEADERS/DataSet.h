#ifndef DATSET_H
#define DATSET_H

#include <vector>
#include <map>
#include <algorithm>

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
    bool empty = false;
    T min;
    T max;
};
class DataSet
{
    RooDataSet* generated;
private:
    RooRealVar _dE;
    RooRealVar _tof;
    Bethe_Block _BB;
    std::map<int,Range<double>> _map_charge_tof; //int = carica disponibile, Range = range del tof relativo a quella carica


    bool Generator();
    
public:
    DataSet(Range<int> range,const Bethe_Block BB, std::vector<int> N_particles, std::vector<Range<double>> tof_range);
    ~DataSet();
};

DataSet::DataSet(Range<int> range,const Bethe_Block BB, std::vector<int> N_particles, std::vector<Range<double>> tof_range) : _BB{BB}
{
    for(auto i = range.min; i < range.max;i++)
        if(tof_range.at(i).empty != true)
            _map_charge_tof[i] = tof_range.at(i);

    Generate();

    
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
    

    bool _ToF_Generator(const int N = 1E3/*Numbers of particles generated*/);
    bool _dE_Generator(const RooDataSet* ToF_Data, const double& L);


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
