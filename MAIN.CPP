#include "BESSEL.HPP"
#include "IFUSAGE.HPP"

int main() {
 unsigned variablesQuantity, valuesQuantity;
 double *X, *Y, *x, *f, y, varBegin, varEnd, varStep;
 char c;
 clrscr();
 printf("Would you like to input 2 variables function (y/n)?\n");
 c = getch();
 variablesQuantity = (c == 'y' || c == 'Y' || c == '§' || c == 'Ñ') ? 2 : 1;
 printf("You have input variables quantity %d: ", variablesQuantity);
 X = new double [variablesQuantity * valuesQuantity];
 printf("\nWill step of argument(s) be constant (y/n)?");
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
 Y = new double [(unsigned) pow(valuesQuantity, variablesQuantity)];
 for (unsigned i = 0; i < valuesQuantity; i++) {
  if (variablesQuantity > 1) {
   for (unsigned j = 0; j < valuesQuantity; j++) {
    printf("f(%f, %f) = ", *(X+0*valuesQuantity+i), *(X+1*valuesQuantity+j));
    scanf("%lf", (Y+i*valuesQuantity+j));
   }
  } else {
   printf("f(%f) = ", *(X+i));
   scanf("%lf", (Y+i));
  }
 }
 do {
  x = new double [variablesQuantity];
  printf("Input argument(s) you want to calculate function value (delimiter - space):\n");
  for (unsigned i = 0; i < variablesQuantity; i++) {
   scanf("%lf", (x + i));
  }
  double z = IFUsage<Bessel>::apply(variablesQuantity, valuesQuantity, X, Y, x);
  char strRes[45], strTemp[19];
  strcpy(strRes, "f(");
  for (i = 0; i < variablesQuantity; i++) {
   sprintf(strTemp, "%f", *(x+i));
   strcat(strRes, strTemp);
   strcat(strRes, (i < variablesQuantity - 1) ? ", " : ") = ");
  }
  sprintf(strTemp, "%f", z);
  strcat(strRes, strTemp);
  printf("%s\n", strRes);
  delete [] x;
  printf(
  "Would you like to calculate this function for another argument(y/n)?\n"
  );
  c = getch();
 } while (!(c == 'n' || c == 'N' || c == '≠' || c == 'ç'));
 delete [] Y;
 delete [] X;
 printf("Press any key to halt.\n");
 getch();
 return 0;
}