#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NOME "Nome"
#define DESCRICAO "Descricao"
#define PRECO 5.4
#define MAXi 9
#define MAXj 9
#define INDEX_LEN 100			// Tamanho da tabela hash.
#define HASH_PRIME 79			// Numero primo escolhido para a funcao hash.
#define DEFAULT_VALUE 1000		// Valor default para posicoes da tabela hash na utilizadas.

int numero_de_colisoes = 0;									// Contador para casos de colisao.
int busca_mec = 0;
int busca_mecanizada[MAXi*MAXj];

typedef struct produto_ {
	int codigo;
	char* nome;
	char* descricao;
	float preco;
} produto;

produto* novo_vetor[MAXi][MAXj];							// Matriz "Banco de Dados".

typedef struct local_ {	// Estrutura usada na indexacao dos produtos.

	int hashIndex;		// Index resultado da funcao hash.
	int Mi;				// Valor linha da matriz.
	int Mj;				// Valor coluna da matriz.
	struct local* lista_colisao;
} local;

local* vetor_tabela_hash[INDEX_LEN];						// Tabela hash.

int gera_random();
void popula_matriz();
void print_matriz ();
int funcao_hash (int key);
void hashing();
local* inicializa_estrutura_colidida(int x, int i, int j);
void tratamento_colisao(int x, int i, int j);
void print_table_element(int w);
void print_hashtable();
void inicializar();
void busca_produto(int p);
void busca_mecanizada_func();

int main () {

	popula_matriz ();
	printf("DATA MATRIX: INITIALIZED.\n");
		
	printf("Initializing hash table...\n");
	inicializar ();
	printf("Hash table initialzized.\n");
	printf("\n");
	
	printf("Populating tabela hash...\n");
	printf("\n");
	hashing ();

	printf("Tabela hash populated.\n");
	printf("\n");
	printf("\n");

	printf("Collisions total count: %d\n", numero_de_colisoes);

	printf("\n");
	printf("\n");

	/* Iniciar cronometragem do tempo aqui*/
	busca_mecanizada_func ();
	/* Finalizar cronometragem do tempo aqui*/

	return 0;
}

int gera_random () {
	
	static int x = 0;
	int a = 1 + (rand() % 100);
	x = x + a;
	return x;
}

void popula_matriz () {
	int i;
	int j;
	for (i = 0; i < MAXi; ++i) {
		for (j = 0; j < MAXj; ++j) {
			novo_vetor[i][j] = malloc(sizeof(produto));

			novo_vetor[i][j]->codigo = gera_random ();
			
			busca_mecanizada[busca_mec] = novo_vetor[i][j]->codigo;		// Preenche busa_mecanizada com os codigos de todos os produtos para depois ser utilizada para mecanizar 30 consulta a tabela hash.
			busca_mec++;												
			
			novo_vetor[i][j]->nome = NOME;
			novo_vetor[i][j]->descricao = DESCRICAO;
			novo_vetor[i][j]->preco = PRECO;
		}
	}
}

void print_matriz () {
    int i,j;
	for (i = 0; i < MAXi; ++i)	{
		for (j = 0; j < MAXj; ++j) {
			printf("Product code: %d\n",  novo_vetor[i][j]->codigo);
			printf("Product name: %s\n",  novo_vetor[i][j]->nome);
			printf("Product description: %s\n",  novo_vetor[i][j]->descricao);
			printf("Product price: %f\n",  novo_vetor[i][j]->preco);
			printf("\n");
			printf("\n");
		}
	}
}

int funcao_hash (int key) {		// Calcula e retorna o resultado da funcao hash para a chave key.

	int index;					// Posicao do elento x na hashtable.
	index = key % HASH_PRIME;	// Funcao hash: resto da divisao da chave por HASH_PRIME (numero primo maior que INDEX_LEN).
	return index;				// Valor da indexacao (posicao do elemento na tabela hash).
}

void hashing () {				// Gera tabela hash da matriz de produtos.

	int i,j,posicao;
	for (i = 0; i < MAXi; ++i)	{			// Loop pelos elementos
		for (j = 0; j < MAXj; ++j) {		//da matriz dos produtos.

			posicao = funcao_hash(novo_vetor[i][j]->codigo);		// "posicao" recebe o resultado da funcao hash (index da tabela) para a dada chave.
			
			tratamento_colisao (posicao, i, j);
			

			
		}
	}
}

local* inicializa_estrutura_colidida (int x, int i, int j) {		// Inicializa nova estrutura do tipo "local" para receber dados do registro colidido.

	local* novo = (local *) malloc(sizeof(local));
	novo->hashIndex = x;
	novo->Mi = i;
	novo->Mj = j;
	novo->lista_colisao = NULL;

	return novo;
}

void tratamento_colisao (int x, int i, int j) {
	
	if (vetor_tabela_hash[x]->hashIndex != DEFAULT_VALUE) {		// Se hashIndex possuir valor diferen DEFAULT_VALUE significa que ha registro alocado na dada posicao e tratamento de colisao sera iniciado.
		
		if (vetor_tabela_hash[x]->lista_colisao == NULL) {		// Caso em que houve a primeira colisao na posicao dada.

			numero_de_colisoes++;								// Incremento do contador de colisoes.
			vetor_tabela_hash[x]->lista_colisao = inicializa_estrutura_colidida (x, i, j);
			
		} else {												// Caso em que ja houveram colisoes na dada posicao.

			numero_de_colisoes++;								// Incremento do contador de colisoes.
			local* aux = vetor_tabela_hash[x];
			
			while (aux->lista_colisao != NULL) {				// Loop atraves dos elementos na lista encadeada de colisoes ja alocadas.
				
				aux = aux->lista_colisao;
			}
			
			aux->lista_colisao = inicializa_estrutura_colidida (x, i, j);			
		}
		
	} else {													// hashIndex possui valor igual a DEFAULT_VALUE (nao ha registo alocado na posicao - livre para indexacao).
		
		vetor_tabela_hash[x] = malloc(sizeof(local));			// Alocacao de memoria na x "x" para receber estrutura "local".
		vetor_tabela_hash[x]->hashIndex = x;					// Valor da funcao hash associado a chave.
		vetor_tabela_hash[x]->Mi = i;							// x i na matriz para a dada chave.
		vetor_tabela_hash[x]->Mj = j;							// x j na matriz para a dada chave.
		vetor_tabela_hash[x]->lista_colisao = NULL;				// Ponteriro para lista encadeada que aloca colisoes.
		
	}	
}

void print_table_element (int w) {								// Mostra registro de um elemento dado sua indexacao na tabela hash.

	int x,y;
	x = vetor_tabela_hash[w]->Mi;
	y = vetor_tabela_hash[w]->Mj;
	printf("Product code: %d\n",  novo_vetor[x][y]->codigo);
	printf("Product name: %s\n",  novo_vetor[x][y]->nome);
	printf("Product description: %s\n",  novo_vetor[x][y]->descricao);
	printf("Product price: %f\n",  novo_vetor[x][y]->preco);
	printf("\n");
	printf("\n");
}

void print_hashtable () {										// Mostra todos elementos pertencentes a tabela.

	int i;
	for (i = 0; i < INDEX_LEN; ++i) {
		printf("Index (resultado funcao hash): %d\n", vetor_tabela_hash[i]->hashIndex);
		printf("Mi: %d\n", vetor_tabela_hash[i]->Mi);
		printf("Mj: %d\n", vetor_tabela_hash[i]->Mj);
		printf("\n");
		printf("\n");
	}
}

void inicializar () {											// Inicializa a tabela designando valores default (flags - posicao nao ocupada) para suas estruturas constituintes.

	int b;
	for (b = 0; b < INDEX_LEN; ++b) {		
			
			vetor_tabela_hash[b] = malloc(sizeof(local));			// Alocacao de memoria na posicao "posicao" para receber estrutura "local".
			vetor_tabela_hash[b]->hashIndex = DEFAULT_VALUE;		// Valor da funcao hash associado a chave (default).
			vetor_tabela_hash[b]->Mi = DEFAULT_VALUE;				// Posicao i na matriz para a dada chave (default).
			vetor_tabela_hash[b]->Mj = DEFAULT_VALUE;				// Posicao j na matriz para a dada chave (default).
			vetor_tabela_hash[b]->lista_colisao = NULL;				// Ponteriro para lista encadeada que aloca colisoes.
	}
}

void busca_produto (int p) {

	int func_hash, i, j;
	
	func_hash = funcao_hash (p);
	i = vetor_tabela_hash[func_hash]->Mi;
	j = vetor_tabela_hash[func_hash]->Mj;

	if (novo_vetor[i][j]->codigo == p) {
		printf("No collision\n\n");
		print_table_element (func_hash);
	} else {
		
		local* aux = vetor_tabela_hash[func_hash];

		int x, y, procurado;

		x = i;
		y = j;
		procurado = novo_vetor[x][y]->codigo;
		
		while (procurado != p) {
			
			aux = aux->lista_colisao;
			x = aux->Mi;
			y = aux->Mj;

			procurado = novo_vetor[x][y]->codigo;			
		}

		printf("Collision\n\n");
		printf("Product code: %d\n",  novo_vetor[x][y]->codigo);
		printf("Product name: %s\n",  novo_vetor[x][y]->nome);
		printf("Product description: %s\n",  novo_vetor[x][y]->descricao);
		printf("Product price: %f\n",  novo_vetor[x][y]->preco);
		printf("\n");
		printf("\n");
	}
	
}

void busca_mecanizada_func () {

	int x = 0;
	int w;
	
	while (x < 30) {

		w = rand() % MAXi*MAXj;

		printf("%d - Searched register: %d | ",x+1 ,busca_mecanizada[w]);

		busca_produto(busca_mecanizada[w]);
		x++;
	}	
}




