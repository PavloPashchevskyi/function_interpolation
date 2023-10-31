#ifndef NEWTON2_HPP
#define NEWTON2_HPP

#include "IFORMULA.HPP"

class Newton2 : public IFormula {
 private:
  double calcQ(double x, unsigned n) {
   double P = 1;
   for (unsigned j = 0; j < n; j++) {
    P *= ( (q(x) + j)  );
   }
   return P;
  }
  double formula(double x) {
   double S = 0;
   for (unsigned i = 0; i < pointsQuantity; i++) {
    S = S + ( (calcQ(x, i) * Y[i][pointsQuantity-i-1]) / factorial(i) );
   }
   return S;
  }
  public:
   Newton2(unsigned n, double *X, double *Y) : IFormula(n, X, Y) {
   }
   Newton2() : IFormula() {
   }
   double q(double x) {
    return (x - X[pointsQuantity-1]) / step;
   }
   double f(double x) {
    return this->formula(x);
   }
   ~Newton2() {
   }
};

#endif