#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 4000 //Tamanho da tabela hash

//Nome dos arquivos
const char arquivo_leitura[] = "arquivo.bin";
const char arquivo_impressao[] = "relatorio.txt";

struct palavra {
    char nome_equipe[20];
    int n;
    struct palavra* prox; /* tratamento de colisao com listas */
};

typedef struct palavra Palavra;

/* tipo que representa a tabela de dispersão */
typedef Palavra* Hash[MAX];

//Define os itens da estrutura
typedef struct {

	int id; // sequencial

    // valores aleatórios
	char nome_componente_1[21];
	char nome_componente_2[21];
	char nome_componente_3[21];
	char nome_equipe[20];
	int nr_baloes;
	int nr_tentativas_falsas;

} EquipeMaratona;

void inicializa (Hash tab)
{
    int i;
    for (i=0; i<MAX; i++)
        tab[i] = NULL;
}

int hash (char* s)
{
    int i,total=0;

    for (i=0; s[i]!='\0'; i++)
        total += s[i];

    return total%MAX;
}

Palavra *acessa (Hash tab, char* s)
{
    int h = hash(s);
    Palavra* p;

    for (p=tab[h]; p!=NULL; p=p->prox) {
        //Caso encontre palavras iguais, retorna ela mesma
        if (strcmp(p->nome_equipe,s) == 0){
            return p;
        }
    }

    /* insere nova palavra */
    p = (Palavra*) malloc(sizeof(Palavra));
    strcpy(p->nome_equipe,s);
    p->n = 0;
    p->prox = tab[h];
    tab[h] = p;

    return p;
}

int conta_elems (Hash tab)
{
    int i, total = 0;
    Palavra* p;

    for (i=0; i<MAX; i++) {
        for (p=tab[i]; p!=NULL; p=p->prox)
            total++;
    }
    return total;
}

Palavra** cria_vetor (int n, Hash tab)
{
    int i, j=0;
    Palavra* p;
    Palavra** vet = (Palavra**) malloc(n*sizeof(Palavra*));

    /* percorre tabela preenchendo vetor */
    for (i=0; i<MAX; i++) {
        for (p=tab[i]; p!=NULL; p=p->prox)
            vet[j++] = p;
    }
    return vet;
}

int compara (const void* v1, const void* v2)
{
    Palavra** pp1 = (Palavra**)v1;
    Palavra** pp2 = (Palavra**)v2;
    Palavra* p1 = *pp1;
    Palavra* p2 = *pp2;

    //Ordena primeio pela quantidade de colisões, depois por ordem alfabetica
    /*if (p1->n > p2->n) return -1;
    else if (p1->n < p2->n) return 1;
    else return strcmp(p1->nome_equipe,p2->nome_equipe);*/

    //Compara para ordenar em ordem alfabetica
    return strcmp(p1->nome_equipe,p2->nome_equipe);
}


void imprime (Hash tab, FILE* fp2)
{
    int i, n;

    Palavra** vet;

    //Retorna quantidade de elementos armazenados na tabela
    n = conta_elems(tab);

    printf("\nQuantidade de palavras diferentes: %i \n",n);

    vet = cria_vetor(n,tab);
    qsort(vet,n,sizeof(Palavra*),compara);

    //Imprime no arquivo as palavras ordenadas e com o número de colisoes
    for (i=0; i<n; i++)
        fprintf(fp2,"%s     -> %i \n",vet[i]->nome_equipe,vet[i]->n);

    free(vet);
}

int main ()
{
    EquipeMaratona equipe;

    FILE* fp;
    FILE* fp2;

    Hash tab;

    //Abre arquivo com registros para leitura
    if ((fp=fopen(arquivo_leitura,"rb"))==NULL){
        printf("Erro na abertura do arquivo.\n");
        return 0;
    }

    //Atribui NULL em todas as posições do mapa
    inicializa(tab);

    printf("\n\nAguarde enquanto esta sendo gerado o hashmap...");

    while(1){

        fread(&equipe,sizeof(EquipeMaratona),1,fp);

        if (feof(fp)) break;

        Palavra* p = acessa(tab,equipe.nome_equipe);
        p->n++;
    }

    //cleanScreen();
    printf("\n\nGerado com sucesso!!");

    // abre arquivo para gravação
    fp2 = fopen(arquivo_impressao,"wt");
    if (fp2 == NULL) {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    }

    // imprime ordenado
    imprime (tab,fp2);

    printf("\n\nFoi gerado o arquivo relatorio.txt com informacoes mais detalhadas.\n\n");

    //printf("\nQuantidade de elementos: %i ", conta_elems(tab));

    return 0;
}

//Limpa a tela
void cleanScreen(){
    system("cls");
}
