#include <bits/stdc++.h>

int contador=0;

int compara (const char * a, const char * b)
{
contador ++;
return strcmp (a, b);
}

//-----------------------------------------------------------
//CODIGO DO ARMANDO PARA MERGESORT
//-----------------------------------------------------------

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



//--------------------------------------------------------------------



int main(){
	FILE 	*entra = fopen("entrada3.txt", "r");
	int tam;
	fscanf(entra,"%d",&tam);
	char 	** V=(char **) malloc(tam*sizeof(char *));
	for(int i=0; i<tam; i++){
		V[i]=(char *) malloc(55*sizeof(char));
		fscanf(entra,"%s",V[i]);
	}
	fclose(entra);
	clock_t inicio,
		fim;
	inicio = clock();
	MergeSort(V,0,tam-1,tam);
	fim=clock();
	printf("%d %.3f",contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);


	return 0;
}
