#ifndef BESSEL_HPP
#define BESSEL_HPP

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include "IFORMULA.HPP"

class Bessel : public IFormula {
 private:

  double calcQ(double x, unsigned n) {
   unsigned r = (n % 2 == 0) ? n / 2. : n / 2. + 1;
   double p = 1;
   for (unsigned j = 1; j <= r; j++) {
    p *= (q(x) - j) * (q(x) + j - 1);
   }

   return p;
  }

  double formula(double x) {
   unsigned m = rangeMiddle, r;
   double Q, D, S = (Y[0][m] + Y[0][m+1]) / 2.;
   for (unsigned j = 0; j <= m; j++) {
    Q = (calcQ(x, j) * ((j % 2 == 0) ? (q(x) - 0.5) : 1) / factorial(j+1));
    r = (j + 1) / 2.;
    D = ((j % 2 == 0) ? Y[j+1][m-r] : ((Y[j+1][m-r]+Y[j+1][m-r+1])/2.));
    S += Q * D;
   }

   return S;
  }
 public:
  Bessel() : IFormula() {
  }
  Bessel(unsigned n, double *X, double *Y) : IFormula(n/*2 * n + 2*/, X, Y) {
  }
  double f(double x) {
   return this->formula(x);
  }
  ~Bessel() {
  }
};

#endif