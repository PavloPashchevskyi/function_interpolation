#include "BESSEL.HPP"
#include "LAGRANGE.HPP"

double* getArrayOffset(double *y, unsigned dim, unsigned valsPerDimension) {
 if (dim < 1) {
  printf(
   "Incorrect array dimention. Array beginning address will be returned.\n"
  );
  return y;
 }
 unsigned offset = 0;
 for (unsigned i = 0; i < dim; i++) {
  offset += (i * valsPerDimension);
 }
 return (y + offset);
}

int main() {
 //double X[] = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5};
 //double Y[] = {0.25, 0.2125, 0.2, 0.2125, 0.25, 0.3125};
 //double X[] = {1.00, 1.05, 1.10, 1.15, 1.20, 1.25, 1.30};
 //double Y[] = {2.7183, 2.8577, 3.0042, 3.1582, 3.3201, 3.4903, 3.6693};
 unsigned variablesQuantity, valuesQuantity;
 double *X, *Y, *x, *f, y, varBegin, varEnd, varStep;
 char c;
 clrscr();
 do {
  printf("Input variables quantity: ");
  scanf("%d", &variablesQuantity);
  printf("You have input variables quantity %d: ", variablesQuantity);
 } while (variablesQuantity > 6);
 X = new double [variablesQuantity * valuesQuantity];
 printf("Will step of argument(s) be constant (y/n)?");
 c = getch();
 if (c == 'n' || c == 'N' || c == '≠' || c == 'ç') {
  printf("\nInput values quantity: ");
  scanf("%d", &valuesQuantity);
  for (unsigned i = 0; i < variablesQuantity; i++) {
   printf("Input the values of argument#%d:\n", i+1);
   for (unsigned j = 0; j < valuesQuantity; j++) {
    scanf("%lf", (X+i*valuesQuantity+j));
   }
  }
 } else {
  for (unsigned i = 0; i < variablesQuantity; i++) {
   printf("\nInput min max and step of variable %d (delimiter - space): ", i+1);
   scanf("%lf %lf %lf", &varBegin, &varEnd, &varStep);
   valuesQuantity = ((varEnd - varBegin) / varStep) + 1;
   for (unsigned j = 0; j < valuesQuantity; j++) {
    *(X+i*valuesQuantity+j) = varBegin + j * varStep;
   }
  }
 }
 Y = new double [variablesQuantity * valuesQuantity];
 double *yOffset = getArrayOffset(Y, variablesQuantity, valuesQuantity);

 char strTemp[19];
 for (unsigned j = 0; j < valuesQuantity; j++) {
  char *strFx = new char[18*variablesQuantity+2*(variablesQuantity-1)+7];
  strcpy(strFx, "f(");
  for (unsigned i = 0; i < variablesQuantity; i++) {
   sprintf(strTemp, "%f", *(X+i*valuesQuantity+j));
   strcat(strFx, strTemp);
   strcat(strFx, (i < variablesQuantity - 1) ? ", " : ") = ");
  }
  printf("%s", strFx);
  delete [] strFx;
  scanf("%lf", (yOffset + j));
 }
 x = new double [variablesQuantity];
 printf("Input argument(s) you want to calculate function value (delimiter - space):\n");
 for (unsigned i = 0; i < variablesQuantity; i++) {
  scanf("%lf", (x + i));
 }
 f = new double [valuesQuantity];
 IFormula *diffTables = new Bessel[valuesQuantity + 1];
 for (j = 0; j < valuesQuantity; j++) {
  for (unsigned i = 0; i < variablesQuantity; i++) {
   diffTables[j] = Bessel(valuesQuantity, (X+i*valuesQuantity), (Y+i*valuesQuantity));
   f[j] = diffTables[j].f(x[i]);
  }
 }
 unsigned m = variablesQuantity - 1;
 diffTables[valuesQuantity] = Bessel(
  valuesQuantity,
  (X+m*valuesQuantity),
  f
 );
 y = diffTables[valuesQuantity].f(x[m]);
 delete f;

 printf("f(%3.5f)=%3.5f", *(x+m), y);
 delete x;
 delete [] diffTables;
 delete [] Y;
 delete [] X;
 getch();
 return 0;
}