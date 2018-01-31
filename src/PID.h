#ifndef PID_H
#define PID_H

#include <utility>
#include <vector>
#include <queue>

class PID {
public:
  /*
  * Errors
  */
  static double tol;
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */

  bool first_time;
  double err;
  int n_steps;
  int steps;
  bool best_err;

  std::vector<double> p;
  std::vector<double> dp;
  int next_k;
  std::vector<bool> doubled_pred;
  std::deque<double> q;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void twiddle();
};

#endif /* PID_H */
