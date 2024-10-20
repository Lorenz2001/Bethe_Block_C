#include <cmath>
#include <iostream>

#include "../HEADERS/Bethe_Block.h"
#include "../HEADERS/constants.h"

Bethe_Block::Bethe_Block(bool corrections, Material material,
                         double thickness) {
  _K = Compute_K();
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
  _density = material.density;
}

// GLOBAL CORRECTION  ENABLES
bool Bethe_Block::Enable_Correction(bool enable) {
  _global_enable_correction = enable;
  return true;
}

// FINAL COMPUTATIONS
double Bethe_Block::dE(double const &z, double const &beta) {
  double dE;

  if (beta * beta > 1)
    std::cout << "STOP";
  double gamma = 1 / sqrt(1 - beta * beta);
  // double corrections =
  //     ((_shell_corr == true) ? _Shell_Correction(beta, gamma) : 0) +
  //     ((_density_corr == true) ? _Density_Effect(beta, gamma) : 0);
  //
  // dE = _Linear_dE(z, beta) *
  //     (.5 * _Log(beta, gamma) - beta * beta - corrections);

  dE = -_thick * _K * z * z * _density *
       (beta * beta - std::log(2 * m_e * beta * beta * gamma * gamma / _I)) /
       (beta * beta);

  return dE;
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
double Bethe_Block::Compute_K() {
  return 0.307075; // (MeV·cm²/mol) }
}

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
  return std::log(2 * m_e * c * c * gamma * gamma * beta * beta /**
                  _Tmax(10 * m_e, beta, gamma) */
                  / (_I * _I)); // considero approssimazione M>5m_e
}
double Bethe_Block::_Linear_z(const double &dE, const double &beta) {
  double linear;
  linear = dE * beta * beta;    // particle dependence;
  linear /= (_Z / _A) * _thick; // material dependence
  linear /= _K;                 // other constants
  return linear;
}
double Bethe_Block::_Linear_dE(const double &z, const double &beta) {
  double linear;
  linear = z * z / (beta * beta); // particle dependence;
  linear *= _Z / _A;              // material dependence
  linear *= _K;                   // other constants
  return linear;
}

double Bethe_Block::_Tmax(const double &M, const double &beta,
                          const double &gamma) {
  double T;
  if (M > 5 * m_e)
    T = 2 * m_e * pow(c * beta * gamma, 2);
  return T;
}

//! SCALED BETHE_BLOCK

// SCALED Logarithm
int Log_scaled(int arg, int scale, int version) {

  int log;

  switch (version) {
  case 0:
    log = std::log(arg); // * scale;
    break;

  case 1: {
    int n = 0;
    int x = 3;
    while (x < arg) {
      x *= 3;
      n++;
    }
    log = n;
  }; break;
  default:
    break;
  }

  return log * scale;
}

double Bethe_Block_scaled(Bethe_Block bb, double dE, double beta, int scale) {

  //? variables with _s in the name are scaled

  // Beta
  long int beta_s = static_cast<long int>(beta * scale);
  long int beta_squared_s = static_cast<long int>(beta_s * beta_s / scale);

  // Numeratore
  long int dE_s = static_cast<long int>(dE * scale);
  long int num_ss = static_cast<long int>(dE_s * beta_squared_s);

  // Denominatore
  // constants
  long int I_s = static_cast<long int>(bb.Return_I() * scale);
  long int double_me_s = static_cast<long int>(2 * m_e * scale);
  long int Kx_s = static_cast<long int>(bb.Compute_K() * bb.Return_thick() *
                                        bb.Return_density() * scale);
  // Logarithm in denominator

  long int inverse_gamma_squared_s = scale - beta_squared_s; // 1-(beta)^2

  long int arg_1 =
      static_cast<long int>(I_s * inverse_gamma_squared_s); // log denominator
  long int arg_2 =
      static_cast<long int>(beta_squared_s * double_me_s); // log numerator

  if (arg_1 == 0)
    return -2;
  double div = arg_2 / arg_1;
  long int log_div_s = static_cast<long int>(div);

  long int Log_s = Log_scaled(log_div_s, scale);
  long int parentesis_s = Log_s - beta_squared_s;

  long int den_ss = static_cast<long int>(Kx_s * parentesis_s);
  // Result
  if (den_ss == 0) {
    std::cout << beta << " " << parentesis_s << " " << Log_s << " "
              << beta_squared_s << "\n";
    return -1;
  }

  double div_final = num_ss / den_ss;

  long int result_s = static_cast<long int>(div_final);
  return div_final;
}