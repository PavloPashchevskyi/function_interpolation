#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "IFUSAGE.HPP"
#include "LAGRANGE.HPP"
#include "NEWTON.HPP"
#include "BESSEL.HPP"
#include "NEWTON2.HPP"

class Strategy {
 private:
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
   X = sort(X, n);
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
  static double getMinStep(unsigned n, double *X) {
   double minDiff = 3.4e+38, diff;
   for (unsigned i = 1; i < n; i++) {
    diff = X[i] - X[i - 1];
    if (diff < minDiff) {
     minDiff = diff;
    }
   }
   return minDiff;
  }
  static unsigned isStepConstant(unsigned n, double *X) {
   if (n <= 2) {
    return 1;
   }
   double max = 3.4e-38, min = 3.4e+38;
   for (unsigned i = 0; i < n; i++) {
    if (X[i] > max) {
     max = X[i];
    }
    if (X[i] < min) {
     min = X[i];
    }
   }
   return ((max - min) / (n - 1)) == getMinStep(n, X);
  }
 public:
  static double apply(
   unsigned variablesQuantity,
   unsigned valuesQuantity,
   double *X,
   double *Y,
   double *x
  ) {
   if (!isStepConstant(valuesQuantity, (X+0*valuesQuantity))) {
    return IFUsage<Lagrange>::apply(
     variablesQuantity,
     valuesQuantity,
     X,
     Y,
     x
    );
   }
   unsigned firstThird = (unsigned) valuesQuantity / 3.;
   unsigned theNearestNumber = calcTheNearestNumberInArray(
    valuesQuantity, (X+0*valuesQuantity), *(x+0)
   );
   if (theNearestNumber <= firstThird) {
    return IFUsage<Newton>::apply(
     variablesQuantity,
     valuesQuantity,
     X,
     Y,
     x
    );
   }
   unsigned secondThird = (unsigned) 2 * valuesQuantity / 3.;
   if (theNearestNumber > firstThird && theNearestNumber <= secondThird) {
    return IFUsage<Bessel>::apply(
     variablesQuantity,
     valuesQuantity,
     X,
     Y,
     x
    );
   }
   if (theNearestNumber > secondThird) {
    return IFUsage<Newton2>::apply(
     variablesQuantity,
     valuesQuantity,
     X,
     Y,
     x
    );
   }
  }
};

#endif