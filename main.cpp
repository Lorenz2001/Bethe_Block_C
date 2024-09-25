#include <iostream>
#include <vector>
#include <algorithm>

#include "HEADERS/Bethe_Block.h"
#include "HEADERS/DataSet.h"
#include "HEADERS/material.h"

int main(){

    Material material;
    material.A = 100;
    material.I = 23;
    material.Z = 50;
    material._Zeta = 32;

    Bethe_Block BB(false, material, 0.1);
    
    //Generation data
    Range<int> charge;
    charge.min = 1;
    charge.max = 10;
    
    std::vector<int> N_particles(charge.max,10);
    for(auto it = N_particles.begin(); it != N_particles.begin()+charge.min; it++)
        *it = 0;

    std::vector<Range<double>> tof_range(charge.max,{10,30});
    DataSet data(charge, BB, N_particles, tof_range);

    data.Print_Data(100,200);
    


}

