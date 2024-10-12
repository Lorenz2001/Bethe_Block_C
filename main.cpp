#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "HEADERS/Bethe_Block.h"
#include "HEADERS/DataSet.h"
#include "HEADERS/material.h"

#include "TCanvas.h"
#include "TH1D.h"
#include "TRandom.h"

// TODO: considerare la teoria di LANDAU e quindi la modifica col T_cut

double Bethe(Bethe_Block bb, double dE, double beta) {
  return dE * beta * beta /
         (bb.Return_thick() * bb.Compute_K() * bb.Return_density() *
          (-beta * beta + std::log(2 * m_e * beta * beta /
                                   (bb.Return_I() * (1 - beta * beta)))));
}

int main() {

  auto start = std::chrono::high_resolution_clock::now();
  Material material; // silicon
  material.A = 28.09;
  material.I = 16.0e-6; // Energia media di ionizzazione (in MeV)
  material.Z = 14;
  material._Zeta = 31;     // Not real
  material.density = 2.32; // g/cm^3

  Bethe_Block BB(false, material, 0.1); // 0.1 = thickness in cm

  // Generation data
  Range<int> charge;
  charge.min = 1;
  charge.max = 10; // ARRIVA FINO ALLA CARICA 9

  std::vector<int> N_particles;
  // to remove the charges < charge.min
  for (int i = 0; i < charge.max; i++) {
    N_particles.push_back((i >= charge.min) ? 1E4 : 0);
  }

  std::vector<Range<double>> tof_range(charge.max, {20, 30});
  DataSet data(charge, BB, N_particles, tof_range);

  // data.Print_Data(100, 200);
  int N_errors = 0;
  for (int i = 0; i < data.Return_N(); i++) {

    if (Bethe(BB, data.Return_dE(i), data.Return_beta(i)) -
            Bethe_Block_scaled(BB, data.Return_dE(i), data.Return_beta(i)) >
        0.5) {
      N_errors++;

      // if (Bethe_Block_scaled(BB, data.Return_dE(i), data.Return_beta(i)) ==
      // -2)
      std::cout << "\n " << i << ") "
                << "real: " << data.Return_charge(i) << " z double: "
                << Bethe(BB, data.Return_dE(i), data.Return_beta(i)) << " "
                << " z int : "
                << Bethe_Block_scaled(BB, data.Return_dE(i),
                                      data.Return_beta(i));
    }
  }
  std::cout << "\n ERRORI:" << N_errors;

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end_time - start;
  std::cout << "\nExecution time total: " << duration.count() << " seconds"
            << std::endl;

  return 0;
}
