/* Leonardo Xavier Dantas		*/
/* Turma 28.4				*/
/* Exercício 6 : Caminho Crítico	*/
/*					*/
/* Programa Compilado com G++ 9.4.0	*/
// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritimos e Estruturas de Dados
// Prof. Armando
// dezembro de 2024


#include <stdio.h>
#include <cstring>

typedef struct{
	int quant=0;
	int arr[60];
} vet; //uma estrutura bem basicona de vetor

bool 	adj[60][60],	imp; //matriz de adj e define se tem ciclo, imp de impossivel achar ordem topologica hehe
vet 	oTop;  //ordenacao topologica
int 	seen[60],	pai[60],	sem[60],	pMax[60],	ult; //respectivamente, visto no dfs, pai pra no caso de ciclo, numero de semanas, pai de maior duracao para caminho critico
char	dc[60][31]; //descricao da atividade

FILE *entra, *saida;


//declarei tanta coisa como global para evitar chamar constantemente por referencia, essas chamadas, ao meu ver, poluem o codigo

void put(vet* a, int n){
	a->arr[a->quant++]=n;
}  // funcao bem basicona de inserir em vetor

void dfs(int s){
	if(seen[s]==1) // esse e o caso que foi visto e percorrido por completo
		return;
	if(seen[s]==-1){ //esse e o caso que foi visto mas ainda ta sendo percorrido -> ciclo
		imp=true;
		ult=s; // ultimo do ciclo, sera importante la na frente para printar o ciclo
		return;
	}
	seen[s]=-1;
	for(int i=0; i<60 && !imp; i++)
		if(adj[s][i]){ //percorre os filhos
			pai[i]=s;
			dfs(i);
		}
	seen[s]=1;
	put(&oTop, s); 
}

void pCiclo(int s){ //printa o ciclo recursivamente
	if(s==ult){
		fprintf(saida, "%c ",s+'A');
		return;
	}
	pCiclo(pai[s]);
	fprintf(saida,"%c ",s+'A');
}

void pCC(int s){ //printa o caminho critico recusrivamente
	if(s==-1)
		return;
	pCC(pMax[s]);
	fprintf(saida,"  %c   %s   %4d\n",s+'A',dc[s],sem[s]);
}


int main(){
	
	//abre os arquivos
	entra = fopen("entrada6.txt", "r");
	saida = fopen("Lab6_Leonardo_Xavier_Dantas.txt", "w");
	
	//cabecalho, obrigado pelo ano
	fprintf(saida,"Fim do 1o FUND, foi um prazer cursar essa materia\nObrigado Armando e obrigado gala\n(se nao for o gala corrigindo o lab, obrigado a vc tbm)\nCertamente sentirei saudades de CES-11, gostei muito de programar\nBanana's Enterprise Ltda.\n------------------------------------------------------------\n\n");

	//coleta o lixo
	char lixo[75];
	for(int i = 0; i < 7; i++){
		fgets(lixo, sizeof(lixo), entra);
	}
	
	vet no; //lista das letras que aparecem
	char letra, desc[31], precede[60]; //coleta a letra, descricao e todos os nos pais
	int nSem; // coleta o n de semanas
	
	fscanf(entra," %c",&letra);
	while(letra!='-'){ // para so na linha de ------
		fgets(desc, sizeof(desc), entra);
		fscanf(entra,"%d",&nSem);
		fgets(precede, sizeof(precede), entra);
		for(int i=5; precede[i]!='\n' && precede[i]!='\0' && precede[i]!='.'; i+=2){//coleta as letras dos nos pais, i+=2 para pular a ','
			adj[int(precede[i]-'A')][int(letra-'A')]=true; //add a letra nos filhos do pai
		}
		put(&no,int(letra-'A')); //add a letra como no aparecido
		sem[int(letra-'A')]=nSem;
		strcpy(dc[int(letra-'A')],desc);
		fscanf(entra," %c",&letra);
	}
	for(int i=0; i<no.quant; i++)
		dfs(no.arr[i]); // isso garante que ate elementos disconexos irao ser percorridos ou no caso de nao se ter uma raiz
	
	if(imp){// caso do ciclo, nao sabia muito bem oq escrever por falta de exemplo no classroom
		fprintf(saida,"CICLO DETECTADO:\n\n");	
		pCiclo(pai[ult]);
		fprintf(saida,"%c\n\nIMPOSSIVEL ENCONTRAR CAMINHO CRITICO",ult+'A');
	}
	else{
		fprintf(saida,"UMA ORDENACAO TOPOLOGICA:\n\n");
		int tVal[60], tct=oTop.arr[oTop.quant-1]; //valor minimo para completar cada tarefa e o no do tempo critico, tct
		for(int i=oTop.quant-1; i>=0; i--){ // percorre o vetor de ordenacao topologica ao contrario
			int al=oTop.arr[i]; // so pra despoluir essa variavel
			pMax[al]=-1;
			tVal[al]=0;
			for(int i=0; i<60; i++)
				if(adj[i][al] && tVal[i]>=tVal[al]){
					pMax[al]=i;
					tVal[al]=tVal[i];
				}
			tVal[al]+=sem[al];
			if(tVal[al]>=tVal[tct])
				tct=al;
			fprintf(saida,"%c ", al+'A');
		}
		fprintf(saida,"\n\n------------------------------------------------------------\n\nTEMPO MINIMO PARA O PROJETO: %4d semanas\n\n------------------------------------------------------------\n\nCAMINHO CRITICO:\n\nTAREFA        DESCRICAO           DURACAO\n\n",tVal[tct]);
		pCC(tct);
			
	}
	
	
	fprintf(saida, "\n\n------------------------------------------------------------");

	//fecha tudo
	fclose(entra);
	fclose(saida);
	return 0;
}

