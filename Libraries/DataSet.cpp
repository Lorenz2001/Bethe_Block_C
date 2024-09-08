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











inline double DataSet::_ToF_Generator(){


    RooRealVar tof("t","t",_range.min,_range.max,_unit);
    RooRealVar mean("mean","mean",_mean,_unit);
    RooRealVar sigma("sigma","sigma",_sigma,_unit);

    RooGaussian gauss("gauss","gaussian distribution ToF",tof,mean,sigma);

    RooDataSet* data = gauss.generate(tof,N);

     if(/*control condition*/1)
        
        return true;
    else 
        throw std::runtime_error("\033[1;31m ERROR: Error in dE generation");
}

inline bool DataSet::_dE_Generator(const RooDataSet* ToF_Data, const double& L){
    
    
    
    
    RooDataSet* dE_Data;
    RooRealVar dE;
    
    for(int i = 0; i < ToF_Data->numEntries(); i++){
        TRandom3* rand;
        const RooArgSet* row = ToF_Data->get(i);
        double tof = ((RooRealVar*)row->find("t"))->getVal();
        dE.setVal(rand->Gaus(_BB->dE(_z, tof/(L*c)),_resolution));
        dE_Data->add(RooArgSet(dE));
    }

    if(/*control condition*/1)

        return true;
    else 
        throw std::runtime_error("\033[1;31m ERROR: in dE generation");

}



