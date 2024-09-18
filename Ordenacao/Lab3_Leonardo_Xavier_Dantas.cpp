/* Leonardo Xavier Dantas		*/
/* Turma 28.4				*/
/* Exercício 3 : Ordenação		*/
/*					*/
/* Programa Compilado com G++ 9.4.0	*/
// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritimos e Estruturas de Dados
// Prof. Armando
// setembro de 2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>

int contador=0;

int compara (const char * a, const char * b)
{
contador ++;
return strcmp (a, b);
}

void BubbleSort(char **V, int n){
	for(int p=0; p<n-1; p++)
		for(int i=0; i<n-1; i++)
			if(compara(V[i],V[i+1])>0){
				char aux[55];
				strcpy(aux,V[i+1]);
				strcpy(V[i+1],V[i]);
				strcpy(V[i],aux);
			}
}


//CODIGO DO ARMANDO DE QUICKSORT

int Partition (char **V, int ini, int fim)
{
   char pivo[55], aux[55];
   int esq, dir;

   strcpy(pivo,V[ini]);    // neste exemplo, o pivo é o primeiro da esquerda
   esq  = ini + 1;
   dir  = fim;
   do
   {
      // percorrer da esquerda para a direita. encontrar alguem >= pivo
      while (esq < fim && compara(V[esq],pivo) < 0)
         esq++;
      // percorrer da direita para a esquerda. encontrar alguem < pivo
      while (ini < dir && compara(pivo,V[dir]) <= 0)
         dir--;
      // se achou um `a esquerda e outro `a direita
      if(esq < dir)
      {
         // permutar
         strcpy(aux,V[esq]);
         strcpy(V[esq],V[dir]);
         strcpy(V[dir],aux);
      }
      // caso contrario, terminaraŽ a repeticao
   }while (esq < dir);

   // trocar o pivo com o elemento que "divide" os subvetores
   strcpy(V[ini],V[dir]);
   strcpy(V[dir],pivo);
   // retornar a posição da "divisa"
   return dir;
}


void QuickSort (char **V, int ini, int fim)
{
   int p; //posição do pivo
   if (ini < fim)
   {
      p = Partition (V, ini, fim);
      QuickSort     (V, ini, p-1);
      QuickSort     (V, p+1, fim);
   }
}

//CODIGO DO ARMANDO PARA MERGESORT


void Merge (char **V, int ini, int fim, int n)
{
   char T[n][55];   // temporario
   int med,
       i,     // percorre T
       j,     // percorre lado esquerdo de V
       k;     // percorre lado direito  de V

   med = (ini+fim)/2; //mesmo arredondamento feito ao chamar MergeSort
   j = ini;
   k = med+1;
   i = ini;
   //percorrer selecionando os menores
   while (j <= med && k <= fim)
   {
      if (compara(V[j],V[k]) <= 0)
      {
         strcpy(T[i],V[j]);
         j++;
      }
      else
      {
         strcpy(T[i],V[k]);
         k++;
      }
      i++;
   }
   //se sobrou algo `a esquerda, copiar para T
   while(j <= med)
   {
      strcpy(T[i],V[j]);
      i++;
      j++;
   }
   //se sobrou algo `a direita, copiar para T
   while(k<=fim)
   {
      strcpy(T[i],V[k]);
      i++;
      k++;
   }
   // V recebe T
   for(i=ini; i<=fim; i++)
      strcpy(V[i],T[i]);
}


void MergeSort (char **V, int ini, int fim, int n)
{
   int med;
   if (ini < fim)
   {
      med = (ini+fim)/2;          // dividir ao meio
      MergeSort (V, ini,   med,n);  // ordenar lado esquerdo
      MergeSort (V, med+1, fim,n);  // ordenar lado direito
      Merge     (V, ini,   fim,n);  // mesclar as duas metades
   }
}

int main(){
	FILE *entra = fopen("entrada3.txt", "r");
	FILE *saidaB = fopen("Lab3_Leonardo_Xavier_Dantas_bubble.txt", "w");
	FILE *saidaM = fopen("Lab3_Leonardo_Xavier_Dantas_merge.txt", "w");
	FILE *saidaQ = fopen("Lab3_Leonardo_Xavier_Dantas_quick.txt", "w");
	int tam;
	fscanf(entra,"%d",&tam);
	char ** VB=(char **) malloc(tam*sizeof(char *));
	char ** VM=(char **) malloc(tam*sizeof(char *));
	char ** VQ=(char **) malloc(tam*sizeof(char *));
	for(int i=0; i<tam; i++){
		VB[i]=(char *) malloc(55*sizeof(char));
		VM[i]=(char *) malloc(55*sizeof(char));
		VQ[i]=(char *) malloc(55*sizeof(char));
		fscanf(entra,"%s",VB[i]);
		strcpy(VM[i],VB[i]);
		strcpy(VQ[i],VB[i]);
	}
	
	fclose(entra);	
		
	clock_t inicio,fim;
	
	
	inicio = clock();
	MergeSort(VM,0,tam-1,tam);
	fim=clock();
	fprintf(saidaM,"Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução : %.3f segundos\n\n--------------------------------------------------\n",tam,contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);
	for(int i=0; i<tam; i++)
		fprintf(saidaM,"%s\n",VM[i]);
	fclose(saidaM);
	
	
	contador=0;
	inicio = clock();
	QuickSort(VQ,0,tam-1);
	fim=clock();
	fprintf(saidaQ,"Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução : %.3f segundos\n\n--------------------------------------------------\n",tam,contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);
	for(int i=0; i<tam; i++)
		fprintf(saidaQ,"%s\n",VQ[i]);
	fclose(saidaQ);
	
	
	contador=0;
	inicio = clock();
	BubbleSort(VB,tam);
	fim=clock();
	fprintf(saidaB,"Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução : %.3f segundos\n\n--------------------------------------------------\n",tam,contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);
	for(int i=0; i<tam; i++)
		fprintf(saidaB,"%s\n",VB[i]);
	fclose(saidaB);

	return 0;
}


