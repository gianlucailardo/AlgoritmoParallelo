#include <stdio.h>
#include <stdlib.h>
int main () 
{
	//dichiarazione degli array
	int * a;
	int * b; 
	int * c;
	int i, n;
	
	//all'utente viene fatto scegliere il size e gli elementi degli array
	printf("inserire il size degli array\n");
    scanf ("%d", &n);
	a = (int *) malloc(sizeof(int)*n);
	b = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);
			            
	printf("inserire i %d elementi di a\n", n);
	for(i=0; i<n; i++)
		scanf ("%d", &a[i]);
			
	printf("inserire i %d elementi di b\n", n);
	for(i=0; i<n; i++)
		scanf ("%d", &b[i]);  

	/*ciclo for che scorre tutti gli elementi dei due array 
	e li somma nell'array c, poi stampa gli elementi di c*/
	for(i = 0; i < n; i++)
	{
		c[i] = a[i] + b[i];
		printf("%d\t", c[i]);
	}
	
	return 0;
	
}
			
	