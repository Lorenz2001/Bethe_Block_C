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
double Bethe_Block::dE_dx(const int& z, const double& beta, bool enable_dx = false){


    double dE_dx;

    //particle parameters
    double gamma = 1/sqrt(1-beta*beta);

    //terms

    double linear;
    double log;
    double corrections;


    linear = _Linear_dE(z, beta);
    corrections = (_shell_corr == true)?_Shell_Correction(beta,gamma):0 + (_density_corr == true)?_Density_Effect(beta,gamma):0;
    log = _Log(beta,gamma);
    
    dE_dx = linear*(.5*log-beta*beta-corrections);

    if(enable_dx == true ) dE_dx = dE_dx/_thick;


    return dE_dx;
    



}

double Bethe_Block::z_squared(const double& dE, const double& beta)
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

    return 0;

}
double Bethe_Block::_Shell_Correction(const double& beta, const double& gamma){
    return 0;
}

double Bethe_Block::_Log(const double& beta, const double& gamma){

    double log;

    log = 2*m_e*c*c*gamma*gamma*beta*beta/(_I*_I);
    log = log*_Tmax(double(),beta,gamma);
    
    if(log <= 0){
        throw std::invalid_argument("\033[1;31mERROR: Invalid logarithm argument: "+std::to_string(log)+" !!");
    }
    else{

        log = 0.5*log;
        return log;
    }

}
double Bethe_Block::_Linear_z(const double& dE, const double& beta){
    return -(dE*_A*beta*beta/(_thick*_Z*_K));
}
double Bethe_Block::_Linear_dE(const int& z, const double& beta){
    return _K*_Z*z*z/(_A*beta*beta);
}

double Bethe_Block::_Tmax(const double& M = 10*m_e, const double& beta, const double& gamma){
    double T;
    if(M>5*m_e)
        T = 2*m_e*pow(c*beta*gamma,2);
    return T;
}

