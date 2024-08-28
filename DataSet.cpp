#include <DataSet.h>

#include <vector>
#include <map>



#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"


inline RooDataSet DataGenerator::_ToFGenerator(){


    RooRealVar tof("t","t",_range.min,_range.max,_unit);
    RooRealVar mean("mean","mean",_mean,_unit);
    RooRealVar sigma("sigma","sigma",_sigma,_unit);

    

}



