#include <iostream>
#include <cmath>

#include <Bethe_Block.h>
#include <constants.h>


//! PUBLIC METHODS

 //Settings
void Bethe_Block::Set_Material(int Z, int A, double zeta, double I, double thickness){

}

//GLOBAL CORRECTION  ENABLES
bool Bethe_Block::Enable_Correction(bool enable){
    _global_enable_correction = enable;
}

//FINAL COMPUTATIONS
double Bethe_Block::dE_dx(double const& z, double const &tof){

}

double Bethe_Block::z_squared(double dE, double beta)
{
    double z_squared;

    //particle parameters
    double gamma = 1/sqrt(1-beta*beta);

    //terms

    double linear;
    double log;
    double corrections;


    linear = _Linear_z(dE, beta);
    corrections = (_shell_corr == true)?_Shell_Correction(beta,gamma):0 + (_density_corr == true)?_Density_Effect(beta,gamma):0;
    log = _Log(beta,gamma);
    
    z_squared = linear/(.5*log-beta*beta-corrections);


    return z_squared;

}



//! PRIVATE METHODS

//Functions
double Bethe_Block::_Compute_K(){

}
    //Bethe computations

bool Bethe_Block::_Enable_Correction(CORRECTIONS correction, bool enable){
    if (_global_enable_correction == true) 
        switch (correction)
        {
        case CORRECTIONS::SHELL_CORRECTION:
            _shell_corr = enable;
            break;
        case CORRECTIONS::DENSITY_EFFECT:
            _density_corr = enable;
        default:
            break;
        }
    else{
        _shell_corr = false;
        _density_corr = false;
    }
}

double Bethe_Block::_Density_Effect(const double& beta, const double& gamma){

    return 1;

}
double Bethe_Block::_Shell_Correction(const double& beta, const double& gamma){
    return 1;
}

double Bethe_Block::_Log(const double& beta, const double& gamma){

}
double Bethe_Block::_Linear_z(const double& dE, const double& beta){

}
double Bethe_Block::_Linear_dE(const double& z, const double& beta){

}

double Bethe_Block::_Tmax(const double& M, const double& beta, const double& gamma){
    double T;
    if(M>5*m_e)
        T = 2*m_e*pow(c*beta*gamma,2);
    return T;
}

