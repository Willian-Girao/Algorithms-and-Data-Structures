#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//MAX é o número de elementos que serão inseridos
#define MAX 30



int novo_vetor[MAX];



int gera_random () {
	static int x = 0;
	int a = 1 + (rand() % 20);
	x = x + a;
	return x;
}


void popula_vetor () {
	int i;
	for (i = 0; i < MAX; ++i)
		novo_vetor[i] = gera_random();
}

void print_vetor () {
    int i;
	for (i = 0; i < MAX; ++i)
		printf("%d\n", novo_vetor[i]);
}

int buscaBinaria (int elem){
  int inicio, meio, final;
  inicio = 0;
  final = MAX-1;
  while(inicio <= final){
      meio = (inicio + final)/2;
      if(elem < novo_vetor[meio])
          final = meio - 1; //busca na metade da esquerda
      else
          if(elem > novo_vetor[meio])
              inicio = meio + 1; //busca na metade da direita
          else
             return meio;
  }
  printf("Elemento NAO encontrado.\n");
  return -1; // elemento nÃ£o encontrado
}






int gera_randomArv () {
	int a = 1 + (rand() % MAX);
	return a;
}

typedef struct NO* ArvBin;

struct NO{
  int info;
  struct NO *esq;
  struct NO *dir;
};

//raiz Ã© um NO especial que diz quem Ã© o inÃ­cil da minha Ã¡rvore
ArvBin* cria_ArvBin(){
	ArvBin* raiz = (ArvBin*) malloc (sizeof(ArvBin));
	if (raiz != NULL)
		*raiz = NULL;
	return raiz;
}

void preOrdem_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return;
	if(*raiz != NULL){
		printf("%d\n",(*raiz)->info);
		preOrdem_ArvBin(&((*raiz)->esq));
		preOrdem_ArvBin(&((*raiz)->dir));
	}
}

void emOrdem_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return;
	if(*raiz != NULL){
		emOrdem_ArvBin(&((*raiz)->esq));
		printf("%d\n",(*raiz)->info);
		emOrdem_ArvBin(&((*raiz)->dir));
	}
}

void posOrdem_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return;
	if(*raiz != NULL){
		posOrdem_ArvBin(&((*raiz)->esq));
		posOrdem_ArvBin(&((*raiz)->dir));
		printf("%d\n",(*raiz)->info);
	}
}

// InserÃ§Ã£o na AÅ•vore BinÃ¡ria de Busca
int insere_ArvBin(ArvBin *raiz, int valor){
	if(raiz == NULL)
		return 0;
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if(novo == NULL)
		return 0;
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;
	
	//Procura onde inserir
	if(*raiz == NULL)
		*raiz = novo;
	else{
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		//Navega nos nÃ³s da Ã¡rvore atÃ© chegar em um nÃ³ folha
		while(atual != NULL){
			ant = atual;
			if(valor == atual->info){
				free(novo);
				return 0; //elemento jÃ¡ existe
			}
			if(valor > atual->info)
				atual = atual->dir;
			else
				atual = atual->esq;
		}
		//Insere como filho desse nÃ³ folha
		if(valor > ant->info)
			ant->dir = novo;
		else 
			ant->esq = novo;
	}
	return 1;
}

//Consulta na AÅ•vore BinÃ¡ria de Busca
int consulta_ArvBin(ArvBin* raiz, int valor){
	if(raiz == NULL)
		return 0;
	struct NO* atual = *raiz;
	while(atual != NULL){
		if(valor == atual->info){
			printf("valor encontrado: %d \n", valor);
			return 1;
		}
		if(valor > atual->info){
			atual = atual->dir;

		}	
		else{
			atual = atual->esq;
		}	
	}
	printf("valor NAO encontrado.  \n");
	return 0;
}

//Percorre a Ã¡rvore liberando cada um dos nÃ³s
void libera_NO(struct NO* no){
	if(no == NULL)
		return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	free(no);
	no = NULL;
}
//Destruindo a Ãrvore usando libera_NO
void libera_ArvBin(ArvBin* raiz){
	if(raiz == NULL)
		return;
	libera_NO(*raiz); // libera cada nÃ³
	free(raiz); // libera a raiz
}




double tempo_execucao (clock_t inic, clock_t fina) {
	double tempo_de_execucao = (double) (fina-inic)/(CLOCKS_PER_SEC/1000);
	return tempo_de_execucao;
}




int main(){
  	
  	clock_t tempo_inicial, tempo_final, tempo_total;
  	int i, j;
  	double temp_bin_vetor = 0.0;
  	double temp_bin_arv = 0.0;

  	ArvBin* raiz = cria_ArvBin();
	
	for(i = 0; i < MAX; i++){
		insere_ArvBin(raiz, gera_randomArv());
	}
	
    printf("Pre Ordem:\n");
    preOrdem_ArvBin(raiz);
    printf("\n");
    printf("Em Ordem:\n");
    emOrdem_ArvBin(raiz);
    printf("\n");
    printf("Pos Ordem:\n");
    posOrdem_ArvBin(raiz);
    printf("\n");

	for(i = 0; i < 30; ++i){
		j = (rand() % MAX);
		tempo_inicial = clock();
		consulta_ArvBin(raiz, j);
		tempo_final = clock();
		//printf("consulta na Arvore \n");
    	tempo_execucao (tempo_inicial, tempo_final);
    	printf("Busca na Arvore: %0.20f\n", tempo_execucao (tempo_inicial, tempo_final));
		temp_bin_arv = temp_bin_arv + tempo_execucao (tempo_inicial, tempo_final);
	}		
	
	
  
	
	popula_vetor ();
	printf("\n");
	printf("Vetor\n");
	print_vetor();
	printf("\n");

	for(i = 0; i < 30; ++i){
		j = (rand() % MAX);
		tempo_inicial = clock();
    	buscaBinaria(j);
    	tempo_final = clock();
    	printf("Busca no VETOR: %0.20f \n",tempo_execucao (tempo_inicial, tempo_final));
		temp_bin_vetor = temp_bin_vetor + tempo_execucao (tempo_inicial, tempo_final);
	}
    
    printf("\n");
	printf("Busca binaria na Arvore(em Milissegundo): %0.20f\n", (temp_bin_arv/30));
	printf("Busca binaria no Vetor (em Milissegundo): %0.20f\n", (temp_bin_vetor/30));
   
    printf("\n");
    printf("Teste realizado com: %d elementos\n", MAX );
     printf("\n");    
    //libera_ArvBin(raiz);



return 0;
}
