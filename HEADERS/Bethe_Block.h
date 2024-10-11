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
  double _zeta;  // For density effect
  double _I;     // Minimum atom exitation energy
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
              double thickness = 0);
  ~Bethe_Block();

  // Settings
  void Set_Material(int Z, int A, double zeta, double I, double thickness);
  void Set_Material(Material material, double thickness);

  double Compute_K();
  double Return_thick() { return _thick; };
  double Return_I() { return _I; };

  // GLOBAL CORRECTION ENABLE

  bool Enable_Correction(bool enable); // GLOBAL ENABLE or DISABLE, valid always

  // FINAL COMPUTATIONS
  double dE(const double &z, const double &beta);
  double z_squared(double dE, double beta);

  friend double Bethe_Block_scaled(Bethe_Block bb, double dE, double beta);
};

// namespace scaled {
//? Funzioni riscalate

int scale = 1E6;

// Prodotto tra N interi contenuti nell'array factors
inline int Product_int(int factors[]) {
  int prod = 1;

  int *ptr = factors;
  while (ptr != factors + sizeof(factors) / sizeof(factors[0])) {
    prod *= static_cast<int>((*ptr) * scale);
  }
  return prod;
}

// inverso riscalato
inline int Inverse_int(int arg) { return static_cast<int>((1 / arg) * scale); }

// logaritmo riscalato
inline int Log_int(int arg) {

  int log = std::log(arg) * scale;

  return log;
}

inline double Bethe_Block_scaled(Bethe_Block bb, double dE, double beta) {

  // PARAMETRI SCALATI DA USARE NEI CALCOLI
  int dE_int = static_cast<int>(dE * scale);
  int beta_int = static_cast<int>(dE * scale);

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

  return Product_int(final_product) / scale; // z_squared
}

//} // namespace scaled

#endif