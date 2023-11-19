#ifndef IFACTORY_HPP
#define IFACTORY_HPP

#include "LAGRANGE.HPP"
#include "NEWTON.HPP"
#include "BESSEL.HPP"
#include "NEWTON2.HPP"

class IFactory {
 private:
  static unsigned isSortedAsc(double *X, unsigned n) {
   for (unsigned i = 0; i < n; i++) {
    for (unsigned j = i + 1; j < n; j++) {
     if (*(X+j) < *(X+i)) {
      return 0;
     }
    }
   }
   return 1;
  }
  static double* sort(double *X, unsigned n) {
   double temp;
   for (unsigned i = 0; i < n; i++) {
    for (unsigned j = i + 1; j < n; j++) {
     if (*(X+j) < *(X+i)) {
      temp = *(X+j);
      *(X+j) = *(X+i);
      *(X+i) = temp;
     }
    }
   }
   return X;
  }
  static unsigned calcTheNearestNumberInArray(unsigned n,double *X,double x){
   if (!isSortedAsc(X, n)) {
    X = sort(X, n);
   }
   unsigned low = 0;
   unsigned high = n - 1;
   unsigned mid = (unsigned) (n - 1) / 2.;
   while (low <= high) {
    mid = (unsigned) (low + high) / 2.;
    if (x < X[mid]) {
     high = mid - 1;
    } else {
     low = mid + 1;
    }
   }
   return mid;
  }
  static unsigned isStepConstant(unsigned n, double *X) {
   if (n <= 2) {
    return 1;
   }
   if (!isSortedAsc(X, n)) {
    X = sort(X, n);
   }
   return (X[2] - X[1]) == (X[1] - X[0]);
  }
 public:
  static IFormula* create(
   unsigned valuesQuantity,
   double *X,
   double *Y,
   double x
  ) {
   IFormula *iFormula;
   if (!isStepConstant(valuesQuantity, (X+0*valuesQuantity))) {
    iFormula = new Lagrange(valuesQuantity, X, Y);
   } else {
    unsigned firstThird = (unsigned) valuesQuantity / 3.;
    unsigned theNearestNumber = calcTheNearestNumberInArray(
     valuesQuantity, (X+0*valuesQuantity), x
    );
    if (theNearestNumber <= firstThird) {
     iFormula = new Newton(valuesQuantity, X, Y);
    }
    unsigned secondThird = (unsigned) 2 * valuesQuantity / 3.;
    if (theNearestNumber > firstThird && theNearestNumber <= secondThird) {
     iFormula = new Bessel(valuesQuantity, X, Y);
    }
    if (theNearestNumber > secondThird) {
     iFormula = new Newton2(valuesQuantity, X, Y);
    }
   }
   return iFormula;
  }
};

#endif