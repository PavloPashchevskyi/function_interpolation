#ifndef NEWTON_HPP
#define NEWTON_HPP

#include "IFORMULA.HPP"

class Newton : public IFormula {
 private:
  double calcQ(double x, unsigned n) {
   double P = 1;
   for (unsigned j = 0; j < n; j++) {
    P *= ( (q(x) - j)  );
   }
   return P;
  }
  double formula(double x) {
   double S = 0;
   for (unsigned i = 0; i < pointsQuantity; i++) {
    S = S + ( (calcQ(x, i) * Y[i][0]) / factorial(i) );
   }
   return S;
  }
  public:
   Newton(unsigned n, double *X, double *Y) : IFormula(n, X, Y) {
   }
   Newton() : IFormula() {
   }
   double q(double x) {
    return (x - X[0]) / step;
   }
   double f(double x) {
    return this->formula(x);
   }
   ~Newton() {
   }
};

#endif