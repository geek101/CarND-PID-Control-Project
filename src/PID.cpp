#include <cmath>
#include <numeric>
#include <limits>
#include <iostream>

#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

double PID::tol = 0.1;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  p = vector<double>({ Kp, Kd, Ki });
  dp = vector<double>({1, 1, 1});
  next_k = 0;
  doubled_pred = vector<bool>({ false, false, false });

  first_time = false;
  p_error = i_error = d_error = 0.0;
  n_steps = 100;
  steps = 0;
  best_err = numeric_limits<double>::max();
}

void PID::UpdateError(double cte) {
  if (!first_time) {
    p_error = cte;
    first_time = true;
  }

  d_error = cte - p_error;
  p_error = cte;
  if ((int)q.size() < n_steps) {
    i_error += cte;
    q.emplace_back(cte);
  } else {
    i_error -= q.front();
    q.pop_front();
    i_error += cte;
    q.emplace_back(cte);
  }

  if (steps++ >= n_steps) {
    err += pow(cte, 2);
    //twiddle();
  }
}

double PID::TotalError() {
  return -(p_error*p[0] + d_error*p[1] + i_error*p[2]);
}

void
PID::twiddle() {
  if (accumulate(dp.begin(), dp.end(), 0.0) > tol) {
    if (err < best_err) {
      best_err = err;
      dp[next_k] *= 1.1;
      p[next_k] += dp[next_k];
      doubled_pred[next_k] = false;
    } else if (!doubled_pred[next_k]) {
      p[next_k] -= 2 * dp[next_k];
      doubled_pred[next_k] = true;
    } else if (doubled_pred[next_k]) {
      p[next_k] += dp[next_k];
      dp[next_k] *= 0.9;
      doubled_pred[next_k] = false;
    }
    next_k++;
    next_k %= p.size();
    cout << "Kp: " << p[0] << " Kd: " << p[1] << " Ki: " << p[2] << endl;
  }  // if()
  return;
}
