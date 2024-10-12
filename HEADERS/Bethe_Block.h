#ifndef BETHE_BLOCK_H
#define BETHE_BLOCK_H

#include <cmath>
#include <iostream>

#include "../HEADERS/constants.h"
#include "../HEADERS/material.h"

enum CORRECTIONS { DENSITY_EFFECT = 0, SHELL_CORRECTION = 1 };

class Bethe_Block {
private:
  // Bethe-Block Formula Constants
  double _K;
  // Detector MATERIAL
  int _Z;
  double _A;
  double _zeta; // For density effect
  double _I;    // Minimum atom exitation energy
  double _density;
  double _thick; // thickness of the detector

  // Corrections enables
  bool _shell_corr;
  bool _density_corr;
  bool _global_enable_correction;

  // Functions

  // Bethe computations
  // Corrections
  bool _Enable_Correction(CORRECTIONS correction,
                          bool enable); // valid locally (case by case)
  double _Density_Effect(const double &beta, const double &gamma);
  double _Shell_Correction(const double &beta, const double &gamma);

  // Bethe terms
  double _Log(const double &beta, const double &gamma);
  double _Linear_z(const double &dE, const double &beta);
  double _Linear_dE(const double &z, const double &beta);

  // Other Functions

  double _Tmax(const double &M, const double &beta,
               const double &gamma); //! TO MAKE BETTER

public:
  Bethe_Block(bool corrections = true, Material material = Material(),
              double thickness = 0.5);
  ~Bethe_Block();

  // Settings
  void Set_Material(int Z, int A, double zeta, double I, double thickness);
  void Set_Material(Material material, double thickness);

  double Compute_K();
  double Return_thick() { return _thick; };
  double Return_I() { return _I; };
  double Return_density() { return _density; };

  // GLOBAL CORRECTION ENABLE

  bool Enable_Correction(bool enable); // GLOBAL ENABLE or DISABLE, valid always

  // FINAL COMPUTATIONS
  double dE(const double &z, const double &beta);
  double z_squared(double dE, double beta);

  // friend double Bethe_Block_scaled(Bethe_Block bb, double dE, double beta,
  //                               int scale);
};

// namespace scaled {
//? Funzioni riscalate
/*
// Prodotto tra N interi contenuti nell'array factors
inline int Product_int(int factors[], int scale = 1E6) {
  int prod = 1;

  int *ptr = factors;
  while (ptr != factors + sizeof(factors) / sizeof(factors[0])) {
    prod *= static_cast<int>((*ptr) * scale);
  }
  return prod;
}

// inverso riscalato
inline int Inverse_int(int arg, int scale = 1E6) {
  return static_cast<int>((1 / arg) * scale);
}*/

// logaritmo riscalato
inline int Log_scaled(int arg, int scale, int version = 1) {

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

  // std ::cout << log << "\n";

  return log * scale;
}

inline double Bethe_Block_scaled(Bethe_Block bb, double dE, double beta,
                                 int scale = 4194304) {

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
  // std::cout << num_s << " " << den_s << "\n";

  long int result_s = static_cast<long int>(div_final);
  return div_final;
  /*

  int supp_arr_0[2] = {beta_int, beta_int};
  int beta_squared = Product_int(supp_arr_0);
  int support_gamma = static_cast<int>(scale * scale - beta_squared);
  int gamma_squared_int = static_cast<int>(Inverse_int(support_gamma));

  int K = static_cast<int>(bb.Compute_K() * scale);
  int thick = static_cast<int>(bb.Return_thick() * scale);
  int m_e_int = static_cast<int>(m_e * scale);
  int I_int = static_cast<int>(bb.Return_I() * scale);

  // -----  CALCOLI FINALI PER LA BETHE BLOCK
  int energy_loss = static_cast<int>(dE_int * Inverse_int(thick));

  int supp_arr_1[2] = {I_int, I_int};
  int inverse_ion = static_cast<int>(Inverse_int(Product_int(supp_arr_1)));

  int supp_arr_2[6] = {2 * scale, m_e_int,           beta_int,
                       beta_int,  gamma_squared_int, inverse_ion};
  int support_log_arg = static_cast<int>(Product_int(supp_arr_2));

  int log_arg = static_cast<int>(Log_int(support_gamma));

  int final_product[5] = {energy_loss, Inverse_int(K), beta_squared,
                          Inverse_int(beta_squared - Log_int(log_arg))};

  return Product_int(final_product) / scale; // z_squared */
}

//} // namespace scaled

#endif