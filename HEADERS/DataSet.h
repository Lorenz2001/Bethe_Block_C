#ifndef DATSET_H
#define DATSET_H

#include <algorithm>
#include <map>
#include <vector>

#include "TRandom3.h"

#include "../HEADERS/Bethe_Block.h"

// Idea: Genero valori di ToF, Calcolo dE e la convulizzo con una gaussianaa
//
//
//
//

template <typename T> struct Range {
  T min;
  T max;
  std::vector<int> neglet = {}; // contains the values that not are considered
};

class DataSet {

private:
  // SET-UP
  Bethe_Block _BB;
  double _t_resolution;
  double _dE_resolution;

  std::vector<int> _charges;
  std::vector<Range<double>>
      _tof_range; // int = carica disponibile, Range = range del tof relativo a
                  // quella carica
  std::vector<int> _n_events;

  int N_tot;

  // Events generated
  bool generated; // true if the generation has been performed
  std::vector<double> _beta;
  std::vector<double> _dE;
  std::vector<int> _charge;

  bool Generate();
  void SetResolutions(double t_res, double dE_res);

  double _ToF_Generator(Range<double> tof, double sigma, TRandom3 &rand);
  double _dE_Generator(double tof, int charge, double sigma, TRandom3 &rand);

public:
  DataSet(Range<int> range, const Bethe_Block BB, std::vector<int> N_particles,
          std::vector<Range<double>> tof_range);
  ~DataSet();

  const void Print_Data(int x_bin, int y_bin);
  const void Print_dE() { throw std::logic_error("Metodo non implementato!"); };
  const void Print_tof() {
    throw std::logic_error("Metodo non implementato!");
  };

  const double Return_dE(int i) { return _dE.at(i); };
  // const double Return_tof(int i) { return _beta.at(i); };
  const double Return_beta(int i) { return _beta.at(i); };
  const int Return_charge(int i) { return _charge.at(i); };
  const int Return_N() { return N_tot; }
};

#endif
