#include <stdio.h>

int main(void){
  double nota_a, nota_b, nota_c, resultado;

  scanf("%lf %lf %lf", &nota_a, &nota_b, &nota_c);

  resultado = ((nota_a * 2) + (nota_b * 3) + (nota_c * 5)) / 10;

  printf("MEDIA = %.1lf\n", resultado);
}
