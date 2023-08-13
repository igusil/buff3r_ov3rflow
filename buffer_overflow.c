#include <stdio.h>
#include <stdlib.h>

int main (void) {
  char var1[50];
  gets(var1);
  printf("Valor digitado: %s\n",var1);

  return(0);
}
