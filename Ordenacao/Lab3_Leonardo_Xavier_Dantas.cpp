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

int contador=0; //contador global para poder ser alterado em todas as funcoes

int compara (const char * a, const char * b) //funcao compara como especificado
{
contador ++;
return strcmp (a, b);
}

void BubbleSort(char **V, int n){ 
	for(int p=0; p<n-1; p++) //etapa atual, para garantir a ordem, n-1 vezes
		for(int i=0; i<n-1; i++) //compara todos os pares e troca caso estejam em ordem errada
			if(compara(V[i],V[i+1])>0){
				char aux[55];
				strcpy(aux,V[i+1]);
				strcpy(V[i+1],V[i]);
				strcpy(V[i],aux);
			}
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




//-----------------------------------------------------------
//CODIGO DO ARMANDO PARA MERGESORT
//-----------------------------------------------------------

void Merge (char **V, int ini, int fim, int n)
{
   static char T[10000000][55];   // temporario
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
	
	//abertura dos arquivos de entrada e saida
	FILE 	*entra = fopen("entrada3.txt", "r"),
		*saidaB = fopen("Lab3_Leonardo_Xavier_Dantas_bubble.txt", "w"),
		*saidaM = fopen("Lab3_Leonardo_Xavier_Dantas_merge.txt", "w"),
		*saidaQ = fopen("Lab3_Leonardo_Xavier_Dantas_quick.txt", "w");
	
	//leitura do tamanho do array de strings
	int tam;
	fscanf(entra,"%d",&tam);
	

	//dois vetores, um que vai manter a ordem original e um que vai mudar por ordenacao
	char 	** Vfixo=(char **) malloc(tam*sizeof(char *)),
		** Vmuda=(char **) malloc(tam*sizeof(char *));
	
	//leitura dos valores, tamanho das strings
	for(int i=0; i<tam; i++){
		Vfixo[i]=(char *) malloc(55*sizeof(char));
		Vmuda[i]=(char *) malloc(55*sizeof(char));
		fscanf(entra,"%s",Vfixo[i]);
	}
	
	fclose(entra);	//fecha a entrada que nao sera mais usada
		

	//inicia os medidores de tempo
	clock_t inicio,
		fim;
	

	//o restante do codigo eh bem igual, zera o contador, transfere de vfixo pra vmuda, inicia tempo, ordena, finaliza tempo, escreve arquivo, fecha
	
	for(int i=0; i<tam; i++)
		strcpy(Vmuda[i],Vfixo[i]);
	inicio = clock();
	MergeSort(Vmuda,0,tam-1,tam);
	fim=clock();
	fprintf(saidaM,"Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução : %.3f segundos\n\n--------------------------------------------------\n",tam,contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);
	for(int i=0; i<tam; i++)
		fprintf(saidaM,"%s\n",Vmuda[i]);
	fclose(saidaM);
	
	
	
	for(int i=0; i<tam; i++)
		strcpy(Vmuda[i],Vfixo[i]);
	contador=0;
	inicio = clock();
	QuickSort(Vmuda,0,tam-1);
	fim=clock();
	fprintf(saidaQ,"Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução : %.3f segundos\n\n--------------------------------------------------\n",tam,contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);
	for(int i=0; i<tam; i++)
		fprintf(saidaQ,"%s\n",Vmuda[i]);
	fclose(saidaQ);
	
	
	
	for(int i=0; i<tam; i++)
		strcpy(Vmuda[i],Vfixo[i]);
	contador=0;
	inicio = clock();
	BubbleSort(Vmuda,tam);
	fim=clock();
	fprintf(saidaB,"Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução : %.3f segundos\n\n--------------------------------------------------\n",tam,contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);
	for(int i=0; i<tam; i++)
		fprintf(saidaB,"%s\n",Vmuda[i]);
	fclose(saidaB);


	return 0;
}


