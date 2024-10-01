#include <cmath>
#include <iostream>

#include "../HEADERS/Bethe_Block.h"
#include "../HEADERS/constants.h"

Bethe_Block::Bethe_Block(bool corrections, Material material,
                         double thickness) {
  _K = _Compute_K();
  Enable_Correction(corrections);
  Set_Material(material, thickness);
}

Bethe_Block::~Bethe_Block() {}

//! PUBLIC METHODS

// Settings
void Bethe_Block::Set_Material(int Z, int A, double zeta, double I,
                               double thickness) {}
void Bethe_Block::Set_Material(Material material, double thickness) {
  _Z = material.Z;
  _A = material.A;
  _zeta = material._Zeta;
  _I = material.I;
  _thick = thickness;
}

// GLOBAL CORRECTION  ENABLES
bool Bethe_Block::Enable_Correction(bool enable) {
  _global_enable_correction = enable;
  return true;
}

// FINAL COMPUTATIONS
double Bethe_Block::dE(double const &z, double const &beta) { 
  double dE;
  
  double gamma = 1 / sqrt(1 - beta * beta);
  double corrections =  ((_shell_corr == true) ? _Shell_Correction(beta, gamma) : 0) +
                        ((_density_corr == true) ? _Density_Effect(beta, gamma) : 0);
  
  dE = _Linear_dE(z,beta)*(.5*_Log(beta,gamma)-beta*beta -corrections);
  
  return 0; 
}

double Bethe_Block::z_squared(double dE, double beta) {
  double z_squared;

  // particle parameters
  double gamma = 1 / sqrt(1 - beta * beta);

  // terms

  double linear;
  double log;
  double corrections;

  linear = _Linear_z(dE, beta);
  corrections = ((_shell_corr == true) ? _Shell_Correction(beta, gamma) : 0) +
                ((_density_corr == true) ? _Density_Effect(beta, gamma) : 0);
  log = _Log(beta, gamma);

  z_squared = linear / (.5 * log - beta * beta - corrections);

  return z_squared;
}

//! PRIVATE METHODS

// Functions
double Bethe_Block::_Compute_K() { return 1; }
// Bethe computations

bool Bethe_Block::_Enable_Correction(CORRECTIONS correction, bool enable) {
  if (_global_enable_correction == true)
    switch (correction) {
    case CORRECTIONS::SHELL_CORRECTION:
      _shell_corr = enable;
      break;
    case CORRECTIONS::DENSITY_EFFECT:
      _density_corr = enable;
    default:
      break;
    }
  else {
    _shell_corr = false;
    _density_corr = false;
  }
  return true;
}

double Bethe_Block::_Density_Effect(const double &beta, const double &gamma) {

  return 1;
}
double Bethe_Block::_Shell_Correction(const double &beta, const double &gamma) {
  return 1;
}

double Bethe_Block::_Log(const double &beta, const double &gamma) { 
  return 2*m_e*c*c*gamma*gamma*beta*beta*_Tmax(10*m_e,beta,gamma)/(_I*_I); //considero approssimazione M>5m_e 
}
double Bethe_Block::_Linear_z(const double &dE, const double &beta) {
  double linear;
  linear = dE*beta*beta; //particle dependence;
  linear /= (_Z/_A)*_thick; //material dependence
  linear /= _K; //other constants
  return linear;
}
double Bethe_Block::_Linear_dE(const double &z, const double &beta) {
  double linear;
  linear = z*z/(beta*beta); //particle dependence;
  linear *= _Z/_A; //material dependence
  linear *= _K; //other constants
  return linear;
}

double Bethe_Block::_Tmax(const double &M, const double &beta,
                          const double &gamma) {
  double T;
  if (M > 5 * m_e)
    T = 2 * m_e * pow(c * beta * gamma, 2);
  return T;
}
