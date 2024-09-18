#include <bits/stdc++.h>

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
	BubbleSort(V,tam);
	fim=clock();
	printf("%d %.3f",contador, (fim - inicio)/ (float) CLOCKS_PER_SEC);


	return 0;
}
