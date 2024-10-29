#include <cmath>
#include <iostream>
#include <vector>

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
unsigned long long int Log_scaled(unsigned long long int arg,
                                  unsigned long long int scale, int version) {

  double xx = static_cast<long double>(arg) / static_cast<long double>(scale);

  unsigned long long int log;
  unsigned long long int ln_two =
      static_cast<unsigned long long int>(0.6931471805599 * scale);

  switch (version) {

  case 0:
    log = static_cast<unsigned long long int>(std::log(arg) * scale);

    break;

  case 1: {
    unsigned long long int n = static_cast<unsigned long long int>(0);
    unsigned long long int x = static_cast<unsigned long long int>(2);
    while (x < xx) {
      x = static_cast<unsigned long long int>(2 * x);
      n = static_cast<unsigned long long int>(n + 1);
    }
    // n *= scale;
    n = static_cast<unsigned long long int>(
        n - 32); // log_2(scale)=# of bits, to have ln(arg)=log_2(arg X
                 // scale)=(log_2(arg x scale)-log_2(scale))x ln(2)

    log = static_cast<unsigned long long int>((n * ln_two));
  }; break;

  case 2: {
    double aa = 6 * (xx - 1) / (xx + 4 * std::sqrt(xx) + 1);
    std::cout << " a " << xx << " " << aa + 22 << " a ";
    log = static_cast<unsigned long long int>((aa + 22) * scale);

  } break;

  case 3: {

    double x = xx;
    int iterations = 15;
    // Fattore di scala K (approssimato)
    double K = 1;
    for (int i = 0; i < iterations; i++)
      K *= 1 /
           std::sqrt(
               1 +
               1 / std::pow(2,
                            2 * i)); // K = prodotto di (1/sqrt(1 + (2^(-i))^2))

    // Inizializzazione
    double z = 0;         // Angolo residuo
    double x_current = x; // Valore di input
    double y_current = 0; // Coordinata y iniziale
    double z_current = 0; // Angolo corrente (inizialmente 0)

    // Tabella degli angoli theta
    std::vector<double> theta(iterations);
    for (int i = 0; i < iterations; i++) {
      theta[i] = std::atan(pow(2, -i));
    }

    // Iterazioni
    for (int i = 0; i < iterations; i++) {
      // Decidi la direzione della rotazione
      int d = (z_current < 0) ? 1 : -1;

      // Aggiorna le coordinate
      double x_next = x_current - d * y_current * std::pow(2, -i);
      double y_next = y_current + d * x_current * std::pow(2, -i);

      // Aggiorna l'angolo residuo
      z_current -= d * theta[i];

      // Aggiorna le coordinate correnti
      x_current = x_next;
      y_current = y_next;
    }

    // Calcola il logaritmo finale
    long double log_value =
        z_current * scale + iterations * ln_two; // Aggiungi ln(2^N)

    return static_cast<unsigned long long int>(
        log_value / K); // Dividi per il fattore di scala K
  } break;
  case 4: {

    xx /= std::pow(2, 4);
    double aa = 6 * (xx - 1) / (xx + 4 * std::sqrt(xx) + 1);
    std::cout << " a " << xx << " " << aa + 22 << " a ";
    log = static_cast<unsigned long long int>((aa + 18) * scale);
  } break;

  case 5: {
    if (arg <= 0)
      throw("ERROR; arg<=0");
    else {
      long double arg_d = static_cast<long double>(arg);
      int a = 0;
      while (arg_d >= 1) {
        arg_d /= 2;
        a++;
      }

      double log_res = 2 * std::atan((arg - 1) / (arg + 1));
      log = static_cast<unsigned long long int>((log_res + (a + 21) * ln_two) *
                                                scale);
    }
  }

  default:
    break;
  }

  return log;
}

long int Bethe_Block_scaled(Bethe_Block bb, double dE, double beta, int scale) {

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

  // Stampa finale
  // std::cout << "Results: "
  //           << "beta_s: " << beta_s << "\n "
  //           << "beta_squared_s: " << beta_squared_s << "\n "
  //           << "dE_s: " << dE_s << "\n "
  //           << "num_ss: " << num_ss << "\n "
  //           << "I_s: " << I_s << "\n "
  //           << "double_me_s: " << double_me_s << "\n "
  //           << "Kx_s: " << Kx_s << "\n "
  //           << "inverse_gamma_squared_s: " << inverse_gamma_squared_s <<
  //           "\n
  //           "
  //           << "arg_1: " << arg_1 << "\n "
  //           << "arg_2: " << arg_2 << "\n "
  //           << "log_div_s: " << log_div_s << "\n "
  //           << "Log_s: " << Log_s << "\n "
  //           << "parentesis_s: " << parentesis_s << "\n "
  //           << "den_ss: " << den_ss << "\n "
  //           << "div_final: " << div_final << "\n "
  //           << "result_s: " << result_s << std::endl
  //           << std::endl;
  //
  return div_final;
}

unsigned long long int Bethe_Block_scaled_file(std::string file_name,
                                               Bethe_Block bb, double dE,
                                               double beta,
                                               unsigned long long int scale) {

  //? variables with _s in the name are scaled

  // Beta
  unsigned long long int beta_s =
      static_cast<unsigned long long int>(beta * scale);
  unsigned long long int beta_squared_s =
      static_cast<unsigned long long int>((beta_s * beta_s) / scale);
  // std::cout << " " << beta_squared_s << " ";

  // Numeratore
  unsigned long long int dE_s = static_cast<unsigned long long int>(dE * scale);
  unsigned long long int num_s =
      static_cast<unsigned long long int>(dE * beta_squared_s);

  // Denominatore
  // constants
  unsigned long long int I_s =
      static_cast<unsigned long long int>(bb.Return_I() * scale);
  unsigned long long int double_me_s =
      static_cast<unsigned long long int>(2 * m_e * scale);
  unsigned long long int Kx_s = static_cast<unsigned long long int>(
      bb.Compute_K() * bb.Return_thick() * bb.Return_density() * scale);
  // Logarithm in denominator

  unsigned long long int inverse_gamma_squared_s =
      I_s * scale - I_s * beta_squared_s; // 1-(beta)^2

  unsigned long long int arg_1 = static_cast<unsigned long long int>(
      inverse_gamma_squared_s / scale); // log denominator
  unsigned long long int arg_2 = static_cast<unsigned long long int>(
      beta_squared_s * double_me_s / scale); // log numerator

  if (arg_1 == 0)
    return -2;

  unsigned long long int Log_1_s = Log_scaled(arg_1, scale, 5);
  unsigned long long int Log_2_s = Log_scaled(arg_2, scale, 5);

  unsigned long long int arg_tot =
      static_cast<unsigned long long int>((arg_2 / arg_1) * scale);
  unsigned long long int Log_total = Log_scaled(arg_tot, scale, 5);
  unsigned long long int parentesis_s = Log_2_s - Log_1_s - beta_squared_s;
  std::cout << " int " << arg_tot << " " << Log_1_s << " " << beta_squared_s
            << " "
            << " " << Log_2_s - Log_1_s - beta_squared_s << " ";
  unsigned long long int den_ss =
      static_cast<unsigned long long int>(Kx_s * parentesis_s);
  std::cout << Kx_s * parentesis_s / scale << " " << num_s << " " << std::endl;
  //  Result
  if (den_ss == 0) {
    std::cout << beta << " " << parentesis_s << " " //<< Log_s << " "
              << beta_squared_s << "\n";
    return -1;
  }

  double div_final = (num_s) / (den_ss / scale);

  unsigned long long int result_s =
      static_cast<unsigned long long int>(div_final);

  // Stampa finale
  // std::cout << "Results: "
  //           << "beta_s: " << beta_s << "\n "
  //           << "beta_squared_s: " << beta_squared_s << "\n "
  //           << "dE_s: " << dE_s << "\n "
  //           << "num_ss: " << num_ss << "\n "
  //           << "I_s: " << I_s << "\n "
  //           << "double_me_s: " << double_me_s << "\n "
  //           << "Kx_s: " << Kx_s << "\n "
  //           << "inverse_gamma_squared_s: " << inverse_gamma_squared_s <<
  //           "\n
  //           "
  //           << "arg_1: " << arg_1 << "\n "
  //           << "arg_2: " << arg_2 << "\n "
  //           << "log_div_s: " << log_div_s << "\n "
  //           << "Log_s: " << Log_s << "\n "
  //           << "parentesis_s: " << parentesis_s << "\n "
  //           << "den_ss: " << den_ss << "\n "
  //           << "div_final: " << div_final << "\n "
  //           << "result_s: " << result_s << std::endl
  //           << std::endl;
  //
  std::ofstream out(file_name, std::ios::app);
  // Stampa  su file

  out << beta_s << " " << beta_squared_s << " " << dE_s << " "
      << " " << arg_1 << " " << arg_2 << " " //<< Log_s << " "
      << "parentesis_s: " << parentesis_s << " " << std::endl;

  out.close();
  return div_final;
}