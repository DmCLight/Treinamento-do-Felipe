#include <stdio.h>

int main(void){
  double nota_a, nota_b, resultado;

  scanf("%lf %lf", &nota_a, &nota_b);

  resultado =((nota_a * 3.5) + (nota_b * 7.5)) / 11;

  printf("MEDIA = %.5lf\n", resultado);
}
