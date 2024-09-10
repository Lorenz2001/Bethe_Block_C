#ifndef DATSET_H
#define DATSET_H

#include <vector>
#include <map>
#include <algorithm>

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"


#include "../HEADERS/Bethe_Block.h"

//Idea: Genero valori di ToF, Calcolo dE e la convulizzo con una gaussianaa
//
//
//
//

template <typename T>
struct Range{
    T min;
    T max;
    std::vector<int> neglet = {}; //contains the values that not are considered
};


class DataSet
{
    
private:
    
    //SET-UP
    Bethe_Block _BB;
    double _t_resolution;
    double _dE_resolution;

    std::vector<int> _charges;
    std::vector<Range<double>> _tof_range; //int = carica disponibile, Range = range del tof relativo a quella carica
    std::vector<int> _m_events;



    //Events generated
    bool generated; //true if the generation has been performed
    std::vector<double> _tof;
    std::vector<double> _dE;
    std::vector<int> _charge;

    bool Generator();

    
    bool _ToF_Generator(Range<double> tof, double sigma = 1);
    bool _dE_Generator(double tof, int charge, double sigma = 1);

    
public:
    DataSet(Range<int> range,const Bethe_Block BB, std::vector<int> N_particles, std::vector<Range<double>> tof_range);
    ~DataSet();
};

//charge = charge to consider
//N_particle = how many particles must be generate for i-th charge. If N_particle.size()==1 then the same amount for everyone. If the i-th element is 0, the charge is not considered
//tof_range = sets the range of the tof for each charge. If size()==1 than the same range is considered for every charge
DataSet::DataSet(Range<int> charge,const Bethe_Block BB, std::vector<int> N_particles, std::vector<Range<double>> tof_range) : _BB{BB}
{

    for(auto i = range.min; i < range.max;i++)
        if(charges.neglet.size()!=0){
            _charges.push_back(i);
            _tof_range.push_back(tof_range[i]);
            _n_events.push_back(N_particles(i));
        }
        else
          if(std::find(charge.neglet.begin(), charge.neglet.end(), i) == charge.neglet.end()){
                _charges.push_back(i);
                _tof_range.push_back(tof_range[i]);
                _n_events.push_back(N_particles(i));
          }
    Generate();

    
}

DataSet::~DataSet()
{
}




#endif
