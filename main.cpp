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

int main() {

  auto start = std::chrono::high_resolution_clock::now();
  Material material; // silicon
  material.A = 28.09;
  material.I = 0.000173; // MeV
  material.Z = 14;
  material._Zeta = 31;

  Bethe_Block BB(false, material, 0.1);

  // Generation data
  Range<int> charge;
  charge.min = 1;
  charge.max = 10; // ARRIVA FINO ALLA CARICA 9

  std::vector<int> N_particles;
  // to remove the charges < charge.min
  for (int i = 0; i < charge.max; i++) {
    N_particles.push_back((i >= charge.min) ? 1E4 : 0);
  }

  std::vector<Range<double>> tof_range(charge.max, {10, 30});
  DataSet data(charge, BB, N_particles, tof_range);

  // data.Print_Data(100, 200);

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end_time - start;
  std::cout << "\nExecution time total: " << duration.count() << " seconds"
            << std::endl;
}
