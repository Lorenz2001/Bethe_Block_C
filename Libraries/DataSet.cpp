#include "../HEADERS/DataSet.h"
#include "../HEADERS/Bethe_Block.h"
#include <constants.h>

#include <vector>
#include <map>

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"

#include "TRandom3.h"



inline bool DataSet::Generate(){

    for(int i = 0 ; i < _charges.size(); i++)
    {
        for(int j = 0; j < _n_events.size() ; j++ ){ 
            _charge.push_back(_charges[i]);
            auto tof = _ToF_Generator(_tof_range[i]);
            _tof.push_back(tof);
            _dE.push_back(_dE_Generator(tof,_charges[i]));
        }
    }

    retrun true;
}


inline double DataSet::_ToF_Generator(Range<double> tof, double sigma = 1){


   double average = (tof.min+tof.max)/2;

   TRandom3 rand;
   TRandom3 rand2;

     if(/*control condition*/1)
        
        return rand.Gaus(rand2.Gaus(average, sigma),_t_resolution);
    else 
        throw std::runtime_error("\033[1;31m ERROR: Error in dE generation");
}

inline bool DataSet::_dE_Generator(double tof, int charge, double sigma = 1){
    
    
    
    
   double average =_BB.dE(charge,tof);

   TRandom3 rand;
   TRandom3 rand2;

     if(/*control condition*/1)
        
        return rand.Gaus(rand2.Gaus(average, sigma),_dE_resolution);
    else 
        throw std::runtime_error("\033[1;31m ERROR: Error in dE generation");

}



