/* Leonardo Xavier Dantas				*/
/* Turma 28.4						*/
/* Exercício 4 : Agenda Eletrônica + vetor simples	*/
/*							*/
/* Programa Compilado com G++ 9.4.0			*/
// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritimos e Estruturas de Dados
// Prof. Armando
// outubro de 2024

#include <cstdlib>
#include <cstdio>
#include <cstring>


//struct que armazena as informacoes da tarefa, deixa o codigo mais facil de mudar no futuro
struct Tarefa {
	int nP;
	char nome[45];
};


//struct da lista, possui o vetor, quantia atual (n) e quantia maxima (nMax)
struct Lista {
	Tarefa* vet;
	int n;
	int nMax;
};

// inicializar toma como parametro o tamanho da lista que eu desejo e retorna a lista ja mallocada
Lista Inicializar(int nMax){
	Lista l;
	l.vet=(Tarefa *)malloc((nMax+1)*sizeof(Tarefa)); //lembrando que comeca no 1 o vetor, logo sao necessario nMax+1 posicoes
	l.n=0;
	l.nMax=nMax;
	return l;
}
	

// retorna o maior elemento do vetor da lista dada, preferi retornar o elemento ao inves de um ponteiro pois poderia fazer alguma alteração local ao elemento
Tarefa ConsultarMax(Lista * l){
	return l->vet[l->n];
}


// so diminui o numero de elementos do vetor, deixa de lixo o que estiver la
void RemoverMax(Lista * l){
	l->n--;
}

// da free na lista, liberando o espaco mallocado
void Finalizar(Lista * l){
	free(l);
}

// se estiver vazia -> n==0 logo retorna se n==0
bool FilaVazia(Lista * l){
	return (l->n==0);
}


// se estiver cheia -> n==nMax logo retorna se n==nMax
bool FilaCheia(Lista * l){
	return (l->n==l->nMax);
}

// retorna um bool que indica se foi possivel inserir ou nao
bool Inserir(Lista * l, Tarefa * T){

	// se estiver cheia, nao foi possivel inserir, retorna falso
	if(FilaCheia(l))
		return false;

	// busca binaria, perceba que caso esteja vazia, vai pular isso pq ini==fim

	int ini=1, fim = l->n+1, mid;
	while (ini < fim){
	        mid = ini + (fim - ini) / 2; // desnecessario, mas eh bom escrever desse jeito para evitar que passe do int max a operacao (fim+ini)
	        if (T->nP >= l->vet[mid].nP)
	        	ini = mid + 1; // muda o ini para direita, elemento maior ou igual do que o do meio
	        else
	        	fim = mid; // muda o fim para a esquerda, elemento menor que o do meio
	}
	// caso seja necessario adicionar o elemento ao final da lista
	if(ini<l->n+1 && l->vet[ini].nP<=T->nP)
		ini++;
	//perceba que alem de transferir todos os elementos ao lado, esse for tambem ja aumenta a quantia de elementos na lista em l->n++
	for(int i=l->n++; i>=ini; i--)
		l->vet[i+1]=l->vet[i];
	strcpy(l->vet[ini].nome,T->nome);
	l->vet[ini].nP=T->nP;
	return true;
}
        


int main() {

	// abre a entrada e a saida, prepara a saida com o texgo inical
	FILE *entra = fopen("entrada4.txt", "r");
	FILE *saida = fopen("Lab4_Leonardo_Xavier_Dantas.txt", "w");
	fprintf(saida,"Oi, meu nome é Leonardo e esse é meu quarto código em C++\nQuando Ismália enlouqueceu,\nPôs-se na torre a sonhar...\nViu uma lua no céu,\nViu outra lua no mar.\n--------------------------------------------------\nRESPOSTAS DAS CONSULTAS\n--------------------------------------------------\n");


	//lixo para coletar o desnecesario, cod para coletar o codigo se é NOVO PROXIMO ou FIM e nome para a descricao da atividade
	char lixo[75], cod[10], nome[45];
	
	//numero maximo de entradas na agenda e numero de prioridade dos elementos
	int nMAX,nP;

	//lixo
	for(int i = 0; i < 5; i++){
		fgets(lixo, sizeof(lixo), entra);
	}
	
	//pega o maximo
	fscanf(entra, "%d", &nMAX);
	
	//inicializa com esse valor
	Lista filaP=Inicializar(nMAX);
	

	//lixo
	for(int i = 0; i < 3; i++){
		fgets(lixo, sizeof(lixo), entra);
	}
	
	//1o codigo, evita de ter que fazer do while
	fscanf(entra, "%s", cod);
	
	//para no FIM
	while(strcmp(cod, "FIM")!=0){

		
		if (strcmp(cod, "NOVA") == 0){
			fscanf(entra, "%d ", &nP);
			fgets(nome,sizeof(nome),entra);
			nome[strlen(nome)-1]='\0';  //retira o \n que foi pego desnecessariamente
			Tarefa nova;
			strcpy(nova.nome,nome);
			nova.nP=nP;
			if(!Inserir(&filaP,&nova)) //se nao conseguiu inserir, vai dar o erro e printar, se conseguiu, insere
				fprintf(saida,"ERRO\tAgenda cheia. Impossivel inserir.\n");
		}
		

		else if (strcmp(cod, "PROXIMA") == 0){
			if(FilaVazia(&filaP)) //se quiser consultar o topo, vazio, avisa
				fprintf(saida,"AVISO\tNao ha tarefas na agenda  :-)\n");
			else{
				fprintf(saida,"%2d\t%s\n",ConsultarMax(&filaP).nP,ConsultarMax(&filaP).nome); //mostra o topo e remove depois
				RemoverMax(&filaP);
			}
		}
		fscanf(entra, "%s", cod);
	}
	

	// agora vai mostrar o que sobrou na agenda
	fprintf(saida, "\n--------------------------------------------------\nFICA PARA O DIA SEGUINTE\n--------------------------------------------------\n");
	if (FilaVazia(&filaP))
		fprintf(saida, "Agenda vazia! Nao restam tarefas para o dia seguinte.");
	else{
		while (!FilaVazia(&filaP)){//retira elemento por elemento ate ficar vazio
			fprintf(saida,"%2d\t%s\n",ConsultarMax(&filaP).nP,ConsultarMax(&filaP).nome);
			RemoverMax(&filaP);
		}
	}


	//fecha os arquivos de entrada e saida
	fclose(entra);
	fclose(saida);
	return 0;
}

