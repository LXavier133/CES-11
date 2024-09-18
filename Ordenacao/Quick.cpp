#include <bits/stdc++.h>

int contador=0;

int compara (const char * a, const char * b)
{
contador ++;
return strcmp (a, b);
}

//---------------------------------------------------------------
//CODIGO DO ARMANDO DE QUICKSORT
//---------------------------------------------------------------
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
	QuickSort(V,0,tam-1);
	fim=clock();
	printf("%d\n%.3f",contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);


	return 0;
}
