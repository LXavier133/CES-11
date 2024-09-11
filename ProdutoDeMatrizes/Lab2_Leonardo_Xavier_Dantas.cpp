/* Leonardo Xavier Dantas		*/
/* Turma 28.4				*/
/* Exercício 2 : Produto de Matrizes	*/
/*					*/
/* Programa Compilado com G++ 9.4.0	*/
// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritimos e Estruturas de Dados
// Prof. Armando
// setembro de 2024


#include <stdio.h>
#include <climits>


int chama=0; //variavel que guarda o numero de chamadas da funcao
int bestK[25][25]; //guarda o melhor corte entre as matrizes


// OBS!!!!! No meu lab, a matriz A_n comeca em m[n-1] e termina em m[n]


// determina o resultado do item a
int melhor(int i, int j, int m[]){
        chama++; // aumenta o numero de chamadas
        int best=INT_MAX; //comeca o best BEM alto pra n ter perigo de dar erro (o Armando deixou usar INT_MAX)
        if(i+1==j) return 0; // i+1==j implica que tem so uma matriz
        for(int k=i+1; k<j; k++){
                int prox=melhor(i,k,m)+melhor(k,j,m)+m[i]*m[j]*m[k]; // calculo do custo atual
		if(best>prox){
			best=prox;
			bestK[i][j]=k; //sera utilizado para printar o melhor caminho
		}
	}
        return best;
}


void pOrd(FILE* saida, int i, int j){
	if(i+1>=j) return; // implica que so tem uma matriz
	
	pOrd(saida,i,bestK[i][j]); // esquerda
	pOrd(saida,bestK[i][j],j); // direita
	
	if(i+1==bestK[i][j]) //uma matriz a esquerda
		fprintf(saida,"   %2d x ",i+1);
	else
		fprintf(saida,"%2d-%2d x ",i+1,bestK[i][j]); // mais de uma matriz
	

	if(bestK[i][j]+1==j) //idem
		fprintf(saida,"%2d \n",j);
	else
		fprintf(saida,"%2d-%2d \n",bestK[i][j]+1,j);
}


int main(){
	
	//abre os arquivos
	FILE *entra = fopen("entrada2.txt", "r");
	FILE *saida = fopen("Lab2_Leonardo_Xavier_Dantas.txt", "w");
	
	//coleta o lixo
	char lixo[75];
	for(int i = 0; i < 5; i++){
		fgets(lixo, sizeof(lixo), entra);
	}
	
	//inicializa a matriz no esquema explicado na OBS
        int nMatriz;
	fscanf(entra,"%d ",&nMatriz);
	fgets(lixo, sizeof(lixo), entra);
	int Matriz[nMatriz+1];
	for(int i = 0; i < nMatriz; i++){
		int a,b;
		fscanf(entra,"%d %d", &a, &b);
		if(i==0)
			Matriz[0]=a;
		Matriz[i+1]=b;
	}

	
	// calcula o minimo e o numero de chamadas
	int res=melhor(0,nMatriz,Matriz);
	
	//escreve a saida
	fprintf(saida,"Exemplo de arquivo de saida \nExercicio 2\nProduto de Matrizes\n\nTotal de multiplicacoes escalares = %d\n\nChamadas aa funcao: %d\n\nMelhor ordem para realizar o produto:\n",res,chama);
	pOrd(saida,0,nMatriz);

	//fecha tudo
	fclose(entra);
	fclose(saida);
	return 0;
}

