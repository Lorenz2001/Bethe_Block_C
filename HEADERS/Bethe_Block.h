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

//! SCALED BETHE BLOCK

// SCALED Logarithm
int Log_scaled(int arg, int scale, int version = 1);

double Bethe_Block_scaled(Bethe_Block bb, double dE, double beta,
                          int scale = 4194304);

#endif