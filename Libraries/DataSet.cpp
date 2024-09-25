#include "../HEADERS/DataSet.h"
#include "../HEADERS/Bethe_Block.h"
#include "../HEADERS/constants.h"  

#include <vector>
#include <map>
#include <algorithm>

#include "TH2D.h"
#include "TRandom3.h"
#include "TCanvas.h"





//charge = charge to consider
//N_particle = how many particles must be generate for i-th charge. If N_particle.size()==1 then the same amount for everyone. If the i-th element is 0, the charge is not considered
//tof_range = sets the range of the tof for each charge. If size()==1 than the same range is considered for every charge
DataSet::DataSet(Range<int> charge,const Bethe_Block BB, std::vector<int> N_particles, std::vector<Range<double>> tof_range) : _BB{BB}
{

    for(auto i = charge.min; i < charge.max;i++)
        if(N_particles[i] != 0){
            _charges.push_back(i);
            _tof_range.push_back(tof_range[i]);
            _n_events.push_back(N_particles[i]);
        }
    Generate();

    
}

DataSet::~DataSet()
{
}





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

    return true;
}


inline double DataSet::_ToF_Generator(Range<double> tof, double sigma){


   double average = (tof.min+tof.max)/2;

   TRandom3 rand;
   TRandom3 rand2;

     if(/*control condition*/1)
        
        return rand.Gaus(rand2.Gaus(average, sigma),_t_resolution);
    else 
        throw std::runtime_error("\033[1;31m ERROR: Error in dE generation");
}

 double DataSet::_dE_Generator(double tof, int charge, double sigma){
    
    
    
    
   double average =_BB.dE(charge,tof);

   TRandom3 rand;
   TRandom3 rand2;

     if(/*control condition*/1)
        
        return rand.Gaus(rand2.Gaus(average, sigma),_dE_resolution);
    else 
        throw std::runtime_error("\033[1;31m ERROR: Error in dE generation");

}



const void DataSet::Print_Data(int x_bin, int y_bin){

    TH2D* Data = new TH2D("Data","Data",x_bin,*std::min_element(_tof.begin(),_tof.end()),*std ::max_element(_tof.begin(),_tof.end()),y_bin,*std::min_element(_dE.begin(),_dE.end()),*std::max_element(_dE.begin(),_dE.end()));

    for(int i = 0; i < _tof.size(); i++){
        Data -> Fill(_tof[i],_dE[i]);
    }

    TCanvas* data_plot = new TCanvas();
    data_plot -> cd();
    Data -> Draw("colz");




}


