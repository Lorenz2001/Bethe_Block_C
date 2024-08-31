#ifndef BETHE_BLOCK_H
#define BETHE_BLOCK_H

#include <iostream>

enum CORRECTIONS {
    DENSITY_EFFECT = 0,
    SHELL_CORRECTION = 1
};


struct Material {
    double density;
    int Z;
    int A;
    double zeta;
    double I;
}



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
    double _Linear_dE(const int& z, const double& beta);
            //Other Functions

    double _Tmax(const double& M, const double& beta, const double& gamma);


    

public:
    Bethe_Block(const Material& material, double thickness, bool corrections = true);
    ~Bethe_Block();

    //Settings
    void Set_Material(int Z, int A, double zeta, double I, double thickness);

    //GLOBAL CORRECTION ENABLE
    
    bool Enable_Correction(bool enable); //GLOBAL ENABLE or DISABLE, valid always
    


    //FINAL COMPUTATIONS
    double dE_dx(const int& z, const double& beta, bool enable_dx = false);
    double z_squared(const double& dE, const double& beta);

};

Bethe_Block::Bethe_Block(const Material& material, double thickness, bool corrections = true)
{
    _Compute_K();
    Set_Material(material.Z, material.A, material.zeta,material.I,thickness)


}

Bethe_Block::~Bethe_Block()
{

}


#endif