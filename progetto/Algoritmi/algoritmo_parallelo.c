#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>



int main (int argc, char *argv[]) 
{
	//dichiarazione degli array da sommare
	int * a;
	int * b; 
	
	int nproc;		
	int menum;
	
	int i, n;
	int rest;
	int indice_displs = 0;
		
	//inizializzazione dell'ambiente parallelo
	MPI_Init (&argc, &argv);
	
	//numero di processori inserito nella variabile nproc
	MPI_Comm_size (MPI_COMM_WORLD, &nproc);
	
	//identificativo dei processori inserito nella variabile menum
	MPI_Comm_rank (MPI_COMM_WORLD,&menum);
	
	//array che indica quanti elementi assegnare ad ogni processore
	int * count_send = (int *) malloc(sizeof(int)*nproc);
	
	//array che indica da quale posizione degli array assegnare gli elementi ad ogni processore
	int * displs = (int *) malloc(sizeof(int)*nproc);
	
	//dichiarazione dei sottoarray
    int * ap;
	int * bp;
	int * cp;
	
	/*operazioni effettuate dal processore master:
	  l'utente sceglie le dimensioni e gli elementi dell'array*/
	if (menum == 0)  
	{       	
        	printf("Inserire il size degli array\n");
        	scanf ("%d", &n);
			a = (int *) malloc(sizeof(int)*n);
			b = (int *) malloc(sizeof(int)*n);
			
			printf("Size degli array inserito correttamente\n");
			            
			printf("Ora, inserire i %d elementi di a\n", n);
			for(i = 0; i < n; i++)
				scanf ("%d", &a[i]);
			
			printf("Elementi di a inseriti correttamente\n");
			
			printf("Ora, inserire i %d elementi di b\n", n);
			for(i = 0; i < n; i++)
			       	scanf ("%d", &b[i]);  
				
			printf("Elementi di b inseriti correttamente, adesso verrà visualizzata la somma\n");
				
	} 
			//distribuzione della dimensione degli array agli altri processori
			MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
				
			rest = n%nproc;
			
			//gestione della distribuzione degli elementi e della non perfetta divisibilità
			/*ad ogni processore vengono assegnati n/nproc elementi, ma se questa divisone da resto 
			  maggiore di 0, allora i primi "rest" processori avranno un elemento in più*/
			for (i = 0; i < nproc; i++) 
			{
				count_send[i] = n/nproc;
				if (rest > 0) 
				{
					count_send[i]++;
					rest--;
				}

			displs[i] = indice_displs;
			indice_displs += count_send[i];
			}
				
			/*allocazione dei sottoarray:
			  ognuno è di dimensione pari al numero di elementi che gli verrà assegnato*/
			ap = (int *) malloc(sizeof(int)*count_send[menum]);
			bp = (int *) malloc(sizeof(int)*count_send[menum]);
			cp = (int *) malloc(sizeof(int)*count_send[menum]);
			
			//distribuzione degli array a e b con le routine MPI_Scatterv
			MPI_Scatterv(a, count_send, displs, MPI_INT, ap, count_send[menum], MPI_INT, 0, MPI_COMM_WORLD);
			 
			MPI_Scatterv(b, count_send, displs, MPI_INT, bp, count_send[menum], MPI_INT, 0, MPI_COMM_WORLD);
			
			//somma degli elementi dei sottarray e stampa dei risultati
			for(i = 0; i < count_send[menum]; i++)
			{
				cp[i] = ap[i] + bp[i];
				printf("%d+%d=%d from p%d\t", ap[i], bp[i], cp[i], menum);
				
			}
			
	//fine dell'ambiente parallelo
	MPI_Finalize();
	
	
	return 0;
}
