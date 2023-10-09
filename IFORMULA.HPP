#ifndef IFORMULA_HPP
#define IFORMULA_HPP

#include <math.h>
#include <string.h>
#include <stdio.h>

void sortAsc(unsigned n, double **x, double **y) {
 double temp;
 for (unsigned i = 0; i < n; i++) {
  for (unsigned j = i + 1; j < n; j++) {
   if (*(*x+j) < *(*x+i)) {
    temp = *(*x+j);
    *(*x+j) = *(*x+i);
    *(*x+i) = temp;
    temp = *(*y+j);
    *(*y+j) = *(*y+i);
    *(*y+i) = temp;
   }
  }
 }
}

class IFormula {
 private:
  static const double accuracy;

  double getMinStep() {
   double minDiff = 3.4e+38, diff;
   for (unsigned i = 1; i < pointsQuantity; i++) {
    diff = X[i] - X[i - 1];
    if (diff < minDiff) {
     minDiff = diff;
    }
   }
   return minDiff;
  }

 protected:
  double *X, **Y, step;
  unsigned pointsQuantity, rangeMiddle;

  long factorial(unsigned n) {
   long p = 1;
   while (n > 1) {
    p *= n;
    n--;
   }
   return p;
  }
 public:
  IFormula() {
   pointsQuantity = 3;
   rangeMiddle = 1;
   X = new double [pointsQuantity];
   Y = new double* [pointsQuantity];
   for (unsigned j = 0; j < pointsQuantity; j++) {
    X[j] = j;
    Y[j] = new double [pointsQuantity - j];
    for (unsigned k = 0; k < pointsQuantity - j; k++) {
     Y[j][k] = (j == 0) ? k : (Y[j-1][k+1]-Y[j-1][k]);
    }
   }
   step = 1;
  }
  IFormula(unsigned n, double *dblX, double *dblY) {
   pointsQuantity = n;
   rangeMiddle = (pointsQuantity - 2) / 2.;
   if ((pointsQuantity - 2) % 2 != 0) {
    rangeMiddle += 1;
   }
   sortAsc(n, &dblX, &dblY);
   this->X = new double [pointsQuantity];
   this->Y = new double* [pointsQuantity];
   for (unsigned j = 0; j < pointsQuantity; j++) {
    this->X[j] = dblX[j];
    this->Y[j] = new double[pointsQuantity - j];
    for (unsigned k = 0; k < pointsQuantity - j; k++) {
     this->Y[j][k] = (j == 0) ? dblY[k] : (this->Y[j-1][k+1]-this->Y[j-1][k]);
    }
   }
   step = this->getMinStep();
  }
  virtual double q(double x) = 0;
  unsigned isStepConstant() {
   double max = 3.4e-38, min = 3.4e+38;
   for (unsigned i = 0; i < pointsQuantity; i++) {
    if (X[i] > max) {
     max = X[i];
    }
    if (X[i] < min) {
     min = X[i];
    }
   }
   return ((max - min) / (pointsQuantity - 1)) == step;
  }
  char* outputDiffsTable() {
   char strTemp[20];
   char *result = new char[pointsQuantity * 19 + 1];
   strcpy(result, "");
   for (unsigned j = 0; j < pointsQuantity; j++) {
    for (unsigned k = 0; k < pointsQuantity - j; k++) {
     sprintf(strTemp, "%f ", Y[j][k]);
     strcat(result, strTemp);
    }
    strcat(result, "\n");
   }
   return result;
  }
  virtual double f(double x) = 0;
  virtual ~IFormula() {
   delete [] X;
   for (unsigned j = 0; j < pointsQuantity; j++) {
    delete Y[j];
   }
   delete [] Y;
  }
};

const double IFormula::accuracy = 0.000001;

#endif