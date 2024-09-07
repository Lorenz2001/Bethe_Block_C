#ifndef BETHE_BLOCK_H
#define BETHE_BLOCK_H

#include <iostream>

#include <Material.h>



enum CORRECTIONS {
    DENSITY_EFFECT = 0,
    SHELL_CORRECTION = 1
};




class Bethe_Block
{
private:
    //Bethe-Block Formula Constants
    double _K;
    //Detector MATERIAL
    int _Z; 
    int _A; 
    double _zeta; // For density effect
    double _I; //Minimum atom exitation energy
    double _thick; //thickness of the detector


    //Corrections enables
    bool _shell_corr;
    bool _density_corr;
    bool _global_enable_correction;


    //Functions
    double _Compute_K();

        //Bethe computations
            //Corrections
    bool _Enable_Correction(CORRECTIONS correction, bool enable); // valid locally (case by case)
    double _Density_Effect(const double& beta, const double& gamma);
    double _Shell_Correction(const double& beta, const double& gamma);
            //Bethe terms
    double _Log(const double& beta, const double& gamma);
    double _Linear_z(const double& dE, const double& beta);
    double _Linear_dE(const double& z, const double& beta);
            //Other Functions

    double _Tmax(const double& M, const double& beta, const double& gamma);


    

public:
    Bethe_Block(bool corrections = true, const Material& material, const double& thickness);
    ~Bethe_Block();

    //Settings
    void Set_Material(int Z, int A, double zeta, double I, double thickness);
    void Set_Material(const Material& material, const double& thickness);

    //GLOBAL CORRECTION ENABLE
    
    bool Enable_Correction(bool enable); //GLOBAL ENABLE or DISABLE, valid always
    


    //FINAL COMPUTATIONS
    double dE(const double& z, const double& tof);
    double z_squared(double dE, double tof);

};

Bethe_Block::Bethe_Block(bool corrections = true, const Material& material, const double& thickness)
{
    _K = _Compute_K();
    Enable_Correction(corrections);
    Set_Material(material,thickness);

    
}

Bethe_Block::~Bethe_Block()
{

}


#endif