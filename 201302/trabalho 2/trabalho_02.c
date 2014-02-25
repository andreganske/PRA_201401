/*
 ============================================================================
 Name        : trabalho_02.c
 Author      : Andre Ganske & Gustavo Pereira | 2013
 Version     :
 Copyright   : Code licensed under Apache Licence v2.0, documentation under CC BY 3.0
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Define os itens da estrutura*/
typedef struct {

	int id; // sequencial

	char nome_componente_1[21];
	char nome_componente_2[21];
	char nome_componente_3[21];

	char nome_equipe[20]; // aleatório
	int nr_baloes;
	int nr_tentativas_falsas;

} EquipeMaratona;

typedef struct {

	struct EquipeMaratona * equipe;
	struct TDA * anterior;
	struct TDA * proximo;

	int id;

} TDA;

char filename[] = "arquivo.bin";
char temp[] = "temp.bin";
char finalfile[] = "finish.txt";

/********************************************************************************************************************************************************/

// read blocks
TDA * readBlock (FILE * fp, long inicial, long final, int tam_bloco, TDA * raiz);

// read item from base file
TDA * readFromBase (int tam_bloco, FILE * fp, TDA * raiz);

// read item from temp file
TDA * readFromTemp (FILE * fp, TDA * raiz, int tam_bloco, int vetor[]);

void sortByNomeEquipe();

void sortByNrBaloes();

void sortByNrTentativas();

void sortByNomeComponenteUm();

void sortByNomeComponenteDois();

void sortByNomeComponenteTres();

// sort items
void sortVector(TDA * raiz, int array_size, int sort_kind);

// create temp file
FILE * createFile(char name[]);

// save on temp file
void saveBlock (FILE * ft, TDA * raiz);

/********************************************************************************************************************************************************/

TDA * readBlock (FILE * fp, long inicial, long final, int tam_bloco, TDA * raiz) {
	int i;
	sot()
	TDA * runner = NULL;

	fseek(fp, final, inicial);

	for (i = 1; i <= tam_bloco; i ++) {

		EquipeMaratona * temp = (EquipeMaratona *) malloc (sizeof(EquipeMaratona));
		fread(temp, 1, sizeof(EquipeMaratona), fp);

		if (raiz == NULL) {

			raiz = (TDA *) malloc (sizeof(TDA));
			raiz -> anterior = NULL;
			raiz -> equipe = temp;

		} else {

			TDA * new = (TDA *) malloc (sizeof(TDA));
			new -> equipe = temp;
			new -> anterior = new -> proximo = NULL;
			// salva o bloco no arquivo temporario
			runner = raiz;

			while (runner -> proximo) {
				runner = runner -> proximo;
			}

			runner -> proximo = new;
			new -> anterior = runner;

		}
	}
	return raiz;
}


TDA * readFromBase (int tam_bloco, FILE * fp, TDA * raiz) {

	long inicial = ftell(fp) * sizeof(EquipeMaratona);
	long final = inicial + (tam_bloco * sizeof(EquipeMaratona));

	return readBlock(fp, inicial, final, tam_bloco, raiz);
}

// read item from temp
TDA * readFromTemp (FILE * fp, TDA * raiz, int tam_bloco, int vetor[]) {
	int i = 0;

	while (!feof(fp)) {

		long final = ((vetor[i] * tam_bloco) * sizeof(EquipeMaratona));

		raiz -> id = i;
		raiz = readBlock(fp, 0, final, 1, raiz);

		i++;
	}

	return raiz;
}

void swap (TDA * a, TDA * b) {
	TDA * temp = (TDA *) malloc (sizeof(TDA));
	temp = a;
	a = b;
	b = temp;
	free(temp);
}

int partition(TDA * raiz, int left, int right) {
	int i, j;

	i = left;
	for (j = left + 1; j <= right; ++j) {
		if (vec[j] < vec[left]) {
			++i;
			swap(&vec[i], &vec[j]);
		}
	}
	swap(&vec[left], &vec[i]);

	return i;
}


// caracter
void sortByNomeEquipe() {

}

// inteiro
void sortByNrBaloes(TDA * raiz, int left, int right) {

	int r;

	TDA * tdaTemp = raiz -> equipe;
	EquipeMaratona * equipeLeft = tdaTemp -> equipe;
	left = equipeLeft -> nr_baloes;

	tdaTemp = raiz -> proximo;
	EquipeMaratona * equipeRight = tdaTemp -> equipe;
	right = equipeRight -> nr_baloes;

	if (right > left) {
		r = partition(raiz, left, right);
		sortByNrBaloes(raiz, left, r - 1);
		sortByNrBaloes(raiz, r + 1, right);
	}

}

// inteiro
void sortByNrTentativas() {

}

// caracter
void sortByNomeComponenteUm() {

}

// caracter
void sortByNomeComponenteDois() {

}

// caracter
void sortByNomeComponenteTres(){

}

// sort items
void sortVector(TDA * raiz, int array_size, int opcao) {

	switch (opcao) {

	case 1:
		sortByNomeEquipe();
		break;
	case 2:
		sortByNrBaloes();
		break;
	case 3:
		sortByNrTentativas();
		break;
	case 4:
		sortByNomeComponenteUm();
		break;
	case 5:
		sortByNomeComponenteDois();
		break;
	case 6:
		sortByNomeComponenteTres();
		break;

	}
}


// create temp file
FILE * createFile(char name[]) {
	return fopen(name, "wb+");
}

// save on temp file
void saveBlock (FILE * ft, TDA * raiz) {
	TDA * runner = raiz;
	// salva o bloco no arquivo temporario
	fseek(ft, 0, 0);

	while (runner) {
		EquipeMaratona * temp = runner -> equipe;
		fwrite(temp, sizeof(EquipeMaratona), 1, ft);

		runner = runner -> proximo;
		free (raiz);
		raiz = runner;
	}
}

/********************************************************************************************************************************************************/

int menu() {
	int opcao = 0;

	printf("\n\n*****************");

	printf("\n Selecione por qual campo voce deseja ordenar:");
	printf("\n [1] - Nome da equipe");
	printf("\n [2] - Nr de baloes");
	printf("\n [3] - Nr de tentativas");
	printf("\n [4] - Nome do componente um");
	printf("\n [5] - Nome do componente dois");
	printf("\n [6] - Nome do componente tres");
	printf("\n");

	scanf(" %d", &opcao);

	return opcao;

}

/********************************************************************************************************************************************************/


int main(void) {

	int opcao = menu();

	int i, count = 0;

	TDA * raiz = NULL;

	FILE * fp;
	FILE * ft = createFile(temp);

	// abre o arquivo de equipes
	if ((fp = fopen(filename, "rb")) == NULL) {
		printf("\n[error] cannot create file");
		return 0;
	}

	while (!feof(fp)) {

		raiz = readFromBase(256, fp, raiz); // le os dados em pacotes de 256 itens

		sortVector(raiz, 256, opcao); // faz a ordenacao

		saveBlock(ft, raiz); // salva o bloco no arquivo temporario

		raiz = NULL; // para evitar erros

		count ++; // conta quantas pilhas foram criadas
	}

	fclose(fp);// salva o bloco no arquivo temporario
	fclose(ft);

	// abre o arquivo temporario
	if ((ft = fopen(filename, "rb")) == NULL) {
		printf("\n[error] cannot open file");
		return 0;
	}

	// cria um vetor com a quantidade de pilhas - será utilizado como controle
	int vetor[count];

	// seta zero em todos os itens do vetor - para controlar os itens que ja foram ordenados
	while (i <= count){
		vetor[i] = 0;
	}

	while (1) {
		// le o primeiro item de cada uma das pilhas
		raiz = readFromTemp(ft, raiz, 256, vetor);

		// ordena o vetor
		//raiz = sortVector(raiz);

		// salva apenas o primeiro item no arquivo
		saveItem(raiz -> equipe);

		// incrementa o vetor da raiz
		vetor[raiz -> id] ++;
	}

	return EXIT_SUCCESS;
}
