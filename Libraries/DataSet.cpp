#include <DataSet.h>
#include <Bethe_Block.h>
#include <constants.h>

#include <vector>
#include <map>



#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"

#include "TRandom3.h"














//---------------------------------------

inline bool DataGenerator::_ToF_Generator(const int N = 1E3/*Numbers of data generated*/){


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

inline bool DataGenerator::_dE_Generator(const RooDataSet* ToF_Data, const double& L){
    
    
    
    
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



