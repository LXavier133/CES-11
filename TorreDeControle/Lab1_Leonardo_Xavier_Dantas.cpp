/* Leonardo Xavier Dantas		*/
/* Turma 28.4				*/
/* Exercício 1 : Torre de Controle	*/
/*					*/
/* Programa Compilado com G++ 9.4.0	*/
// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritimos e Estruturas de Dados
// Prof. Armando
// agosto de 2024



//declaracao de bibliotecas

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>




//estrutura guarda numero do voo, nome e proximo da fila
struct fila {
	int nVoo;
	char nome[35];
	fila *prox=NULL; //por padrao, o proximo é NULL
};


//ponteiros que apontam ao inicio, ultimo elemento e ultimo elemento urgente
fila *frente = NULL;
fila *fim = NULL;
fila *fimURG = NULL;

//poe elemento depois da posicao ultimo
void poe_fim(int n, char name[35]) {
	
	//aloca espaco e copia as info
	fila *novo = (fila *)malloc(sizeof(fila));
	novo->nVoo = n;
	novo->prox= NULL;
	strcpy(novo->nome, name);
	//caso nao tenha ninguem no ultimo, ou nao tem urgencia, ou nao tem ninguem, ambos os casos, frente=novo
	if(fim==NULL){
		fim=novo;
		frente=novo;
	}
	else{//mesma coisa, atualiza o novo ultimo
		fim->prox=novo;
		fim=novo;
	}
}


//remove o elemento da frente e atualiza os outros ponteiros globais de acordo com o processo
void remove() {
	fila *aux = frente;
	if(frente==fimURG)//caso so um esteja de urgencia
		fimURG=NULL;
	frente = frente->prox;
	if (frente==NULL){//caso acabe os elementos
		fim = NULL;
		fimURG=NULL;
	}
	free(aux);
}



//move o elemento depois do atual pro fimURG
void move_prox(fila *atual){
	fila *aux=atual->prox;
	if(atual == fimURG){//lida com o caso de ser logo o proximo
		fimURG=atual->prox;
		return;}
	if(fim==aux) //lida com o caso de mover o ultimo
		fim=atual;
	if(fimURG==NULL){//lida com o caso de quando nao tem urgencia
		atual->prox=atual->prox->prox;
		fimURG=aux;
		aux->prox=frente;
		frente=aux;
	}
	else{
		atual->prox=aux->prox;
		aux->prox=fimURG->prox;
		fimURG->prox=aux;
	}
	fimURG=aux;
}




int main() {
	//abertura dos arquivos de entrada e saida e mensagens iniciais escritas
	FILE *entra = fopen("entrada1.txt", "r");
	FILE *saida = fopen("Lab1_Leonardo_Xavier_Dantas.txt", "w");
	fprintf(saida,"Oi, meu nome é Leonardo e esse é meu primeiro código em C++\nBanana\'s Enterprise ltda. >>>>>>>>>> Teclado Mecanico\nAUTORIZACOES DE POUSO\n=========================================\nFLIGHT  FROM\n\n");

	//declaracao, lixo para recolher as linhas inicias, cod para o comando da pist, nome para o nome da cidade e nVoo para numero do voo
	char lixo[75], cod[55], nome[35];
	int nVoo;
	
	//recolhe o lixo
	for(int i = 0; i < 8; i++){
		fgets(lixo, sizeof(lixo), entra);
	}

	//leitura inicial dos valores
	fscanf(entra, "%s %d ", cod, &nVoo);
	fgets(nome,sizeof(nome),entra);

	while(strcmp(cod, "FIM")!=0){//o loop vai parar quando o comando FIM for dado
		nome[strlen(nome)-1]='\0'; //retira o \n do nome lido
		if (strcmp(cod, "pede_pouso") == 0)
			poe_fim(nVoo, nome); //poe no fim


		else if (strcmp(cod, "pista_liberada") == 0){
			if (frente != NULL){//lida com o caso de nenhum aviao pousando
				fprintf(saida, "%04d	%s\n", frente->nVoo, frente->nome);
				remove();
			}
			else
				fprintf(saida, "0000	Nenhum aviao pousando\n");
		}

		else if (strcmp(cod, "URGENCIA") == 0){
			fila *itera = frente;
			if (frente != NULL && frente->nVoo == nVoo)//lida com o caso do primeiro querer urgencia
				fimURG = frente;
			else{
				while (itera != NULL && itera->prox != NULL && itera->prox->nVoo != nVoo) //busca qual elemento tem que ser movido para urgencia
					itera = itera->prox;
				move_prox(itera);
			}
		}

		//rele os valores, dando continuidade ao loop
		fscanf(entra, "%s %d ", cod, &nVoo);
		fgets(nome,sizeof(nome),entra);
	}

	fprintf(saida, "\nSituacao da fila\n\n");
	if (frente == NULL) //caso nao tenha mais ninguem na pista
		fprintf(saida, "Nada a ser visto por aqui");
	else{
		while (frente != NULL){//retira elemento por elemento ate ficar vazio
			fprintf(saida, "%04d	%s\n", frente->nVoo, frente->nome);
			remove();
		}
	}


	//fecha os arquivos de entrada e saida
	fclose(entra);
	fclose(saida);
	return 0;
}

