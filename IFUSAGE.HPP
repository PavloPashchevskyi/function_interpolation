#ifndef IFUSAGE_HPP
#define IFUSAGE_HPP

#include "IFACTORY.HPP"

class IFUsage {
 private:
  static double* transpose(
  unsigned variablesQuantity,
  unsigned valuesQuantity,
  double *Y
  ) {
   double *transposedY =
   new double [(unsigned) pow(valuesQuantity, variablesQuantity)];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    for (unsigned j = 0; j < valuesQuantity; j++) {
     *(transposedY+i*valuesQuantity+j) = *(Y+j*valuesQuantity+i);
    }
   }
   return transposedY;
  }
  static double apply1(
  unsigned valuesQuantity,
  double *X,
  double *Y,
  double x
  ) {
   IFormula *diffTable = IFactory::create(valuesQuantity, X, Y, x);
   double y = diffTable->f(x);
   delete diffTable;
   return y;
  }
  static double apply2(
  unsigned valuesQuantity,
  double *X,
  double *Y,
  double x,
  double y
  ) {
   double *Yt = transpose(2, valuesQuantity, Y);
   double *preY = new double[valuesQuantity];
   for (unsigned j = 0; j < valuesQuantity; j++) {
    preY[j] = apply1(valuesQuantity, (X+0*valuesQuantity), (Yt+j*valuesQuantity), x);
   }
   double f = apply1(valuesQuantity, (X+1*valuesQuantity), preY, y);
   // delete memory
   delete [] preY;
   delete [] Yt;
   // end delete memory
   return f;
  }
 public:
  static double apply(
  unsigned variablesQuantity,
  unsigned valuesQuantity,
  double *X,
  double *Y,
  double *x /* argument of searching value */
  ) {
   if (variablesQuantity == 1) {
    return apply1(valuesQuantity, X, Y, *(x+0));
   }
   if (variablesQuantity == 2) {
    return apply2(valuesQuantity, X, Y, *(x+0), *(x+1));
   }
  }
};

#endif