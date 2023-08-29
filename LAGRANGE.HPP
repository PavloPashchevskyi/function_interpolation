#ifndef LAGRANGE_HPP
#define LAGRANGE_HPP

#include "IFORMULA.HPP"

class Lagrange : public IFormula {
 private:
  double* calcLMatrix(double x) {
   double *L = new double [pointsQuantity * pointsQuantity];
   for (unsigned i = 0; i < pointsQuantity; i++) {
    for (unsigned j = 0; j < pointsQuantity; j++) {
     *(L+i*pointsQuantity+j) = (i == j) ? x - X[j] : X[i] - X[j];
    }
   }
   return L;
  }

  double formula(double x) {
   double *lMatrix = calcLMatrix(x);
   double *D, P = 1, S;
   D = new double [pointsQuantity];
   for (unsigned i = 0; i < pointsQuantity; i++) {
    D[i] = 1;
    for (unsigned j = 0; j < pointsQuantity; j++) {
     D[i] *= *(lMatrix+i*pointsQuantity+j);
    }
    P *= *(lMatrix+i*pointsQuantity+i);
   }
   S = 0;
   for(i = 0; i < pointsQuantity; i++) {
    S = S + (Y[0][i] / D[i]);
   }
   delete [] D;
   delete [] lMatrix;
   return P * S;
  }
 public:
  Lagrange(unsigned n, double *X, double *Y) : IFormula(n, X, Y) {
  }
  double f(double x) {
   return this->formula(x);
  }
  ~Lagrange() {
  }
};

#endif