#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define m 1000
#define mm 2000

const int debug_mode = 0;

//Nome do arquivo
const char filename[] = "arquivo.bin";
const char filenamePrint[] = "arvore.txt";

const char arquivoIndiceNomeEquipe[] = "arquivo_indice_nome_equipe.bin";
const char arquivoNomeEquipe[] = "ordenado nome equipe.txt";

const char arquivoIndiceNumeroBaloes[] = "arquivo_indice_numero_baloes.bin";
const char arquivoNumeroBaloes[] = "ordenado numero baloes.txt";


typedef struct
{
    int id;
    char nome_equipe[20];

} IndiceNomeEquipe;

typedef struct
{
    int id;
    int nr_baloes;

} IndiceNrBaloes;

typedef struct
{
    int id; // sequencial

    char nome_componente_1[21];
    char nome_componente_2[21];
    char nome_componente_3[21];
    char nome_equipe[20];
    int nr_baloes;
    int nr_tentativas_falsas;

} Registro;

typedef struct Pagina_str *Apontador;
typedef struct Pagina_str
{
   int n;
   Registro r[mm];
   Apontador p[mm + 1];
} Pagina;

typedef Apontador TipoDicionario;

int qtd_registros = 0;

int main()
{
    int qtd_aux = 0, arquivo_lido = 0;

    FILE *fp;

    Apontador *arv;
    Registro reg;
    char tecla,tecla2;

    IndiceNomeEquipe nomeEquipe;
    IndiceNrBaloes nrBaloes;

    arv=(Apontador*) malloc(sizeof(Apontador));
    Inicializa(arv);

    while(1){

        qtd_registros = 0;

        cleanScreen();
        printf("Escolha uma das opcoes:\n");
        printf("-------------------------\n");
        printf("1. Ordenar pelo campo Nome da Equipe \n");
        printf("2. Ordenar pelo campo Numero de Baloes \n");
        printf("3. Mostra em tela Nomes da Equipe ordenados \n");
        printf("4. Mostra em tela Numeros de Baloes ordenados \n");
        printf("0. (zero) para sair\n");
        printf("-> ");

        scanf("%c", &tecla);

        if (tecla=='0')
            break;

        switch(tecla){
        case '1':

            *arv = NULL;

            cleanScreen();

            printf("Montando a arvore por Nome da Equipe...\n");

            if ((fp=fopen(filename,"rb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                while (1){

                    fread(&reg,sizeof(Registro),1,fp);

                    if (feof(fp)) break;

                    if (debug_mode){
                        printf("\n==> INSERINDO REGISTRO, ID: %d ", reg.id);
                        printf("\n      NOME: %s \n\n", reg.nome_equipe);
                    }

                    InserePorNomeEquipe(reg, arv);
                    qtd_registros++;

                    if (debug_mode){
                        getch();
                    }
                }

                fclose(fp);
            }

            printf("Arvore montada com sucesso!\n");
            printf("Gravando em arquivo binario...\n");

            //Grava em arquivo binario os nomes ordenados
            if ((fp=fopen(arquivoIndiceNomeEquipe,"wb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{
                impNomeEquipe(*arv, fp, &nomeEquipe);
                fclose(fp);
            }

            printf("\nArquivo de indice criado com sucesso!\n");

            getch();

        break;
        case '2':

            *arv = NULL;

            cleanScreen();

            printf("Montando a arvore por Numero de Baloes...\n");

            if ((fp=fopen(filename,"rb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                while (1){

                    fread(&reg,sizeof(Registro),1,fp);

                    if (feof(fp)) break;

                    if (debug_mode){
                        printf("\n==> INSERINDO REGISTRO, ID: %d ", reg.id);
                        printf("\n      NUMERO DE BALOES: %d \n\n", reg.nr_baloes);
                    }

                    InserePorNrBaloes(reg, arv);

                    if (debug_mode){
                        getch();
                    }
                }

                fclose(fp);
            }

            printf("Arvore montada com sucesso!\n");
            printf("Gravando em arquivo binario...\n");


            //Grava em arquivo binario os nomes ordenados
            if ((fp=fopen(arquivoIndiceNumeroBaloes,"wb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{
                impNrBaloes(*arv, fp, &nrBaloes);
                fclose(fp);
            }

            printf("\nArquivo de indice criado com sucesso!");

            getch();

         break;

        case '3':

            //Mostra em tela registros do arquivo binario de nomes ordenados

            imprimeNomesOrdem(100);
            getch();

        break;
        case '4':

            //Mostra em tela registros do arquivo binario de numero de baloes
            imprimeNrBaloesOrdem(100);
            getch();

        break;
        case '5':

            //imprime arquivo texto pelo campo Nome Equipe

            if ((fp=fopen(arquivoNomeEquipe,"w+"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{
                imprimirNomes(*arv, fp);
                fclose(fp);
            }

        break;
        case '6':

            //imprime arquivo texto pelo campo numero de baloes

            if ((fp=fopen(arquivoNumeroBaloes,"w+"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{
                imprimirNrBaloes(*arv, fp);
                fclose(fp);
            }

        break;


      }

   }

   free(arv);
   free(fp);

}

void Inicializa(TipoDicionario *Dicionario)
{
   *Dicionario = NULL;
}

/*------INICIO------
    Funções para montar a arvore B pelo campo Número de Balões(tipo inteiro)
*/

void InserePorNrBaloes(Registro Reg, Apontador *Ap)
{
   int Cresceu;
   Registro RegRetorno;
   Apontador ApRetorno;
   Apontador ApTemp;

   InsPorNrBaloes(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

   if (debug_mode == 1) printf("\n Cresceu= %d \n", Cresceu);

   if (Cresceu) {

        if (debug_mode == 1) printf("\n @@@ OK @@@ \n");

      ApTemp = (Apontador) malloc(sizeof(Pagina));
      ApTemp->n = 1;
      ApTemp->r[0] = RegRetorno;
      ApTemp->p[1] = ApRetorno;
      ApTemp->p[0] = *Ap;
      *Ap = ApTemp;
   }
}

void InsPorNrBaloes(Registro Reg, Apontador Ap, int *Cresceu, Registro *RegRetorno, Apontador *ApRetorno)
{
   Apontador ApTemp;
   int i, j;

   if (Ap == NULL)
   {
      *Cresceu = 1;
      *RegRetorno = Reg;
      *ApRetorno = NULL;
      return;
   }

   i = 1;

   if (debug_mode == 1){
       printf("\n.....Posicionando.....\n",Ap->n);
       printf("i: %d , Ap->n: %d , Reg.nr_baloes: %d , Ap->r[i - 1].nr_baloes: %d ", i,Ap->n,Reg.nr_baloes,Ap->r[i - 1].nr_baloes);
   }

   while (i < Ap->n && Reg.nr_baloes > Ap->r[i - 1].nr_baloes){
        i++;

        if (debug_mode == 1){
            printf("\ni: %d , Ap->n: %d , Reg.nr_baloes: %d , Ap->r[i - 1].nr_baloes: %d ", i,Ap->n,Reg.nr_baloes,Ap->r[i - 1].nr_baloes);
        }
   }

   if (debug_mode == 1){
        printf("\n.....Comparando com ID: %d , Nr. baloes: %d \n", Ap->r[i - 1].id, Ap->r[i - 1].nr_baloes);
   }

    if (Reg.nr_baloes == Ap->r[i - 1].nr_baloes){

        if (debug_mode)  printf("\n IGUAL!!! \n");

            while (i < Ap->n && Reg.nr_baloes == Ap->r[i].nr_baloes){
                i++;

                if (debug_mode){
                    printf("\ni: %d , Ap->n: %d , Reg.nr_baloes: %d , Ap->r[i - 1].nr_baloes: %d ", i,Ap->n,Reg.nr_baloes,Ap->r[i - 1].nr_baloes);
                }
            }

        InsPorNrBaloes(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

   }else  if (Reg.nr_baloes < Ap->r[i - 1].nr_baloes){

        if (debug_mode == 1) printf("\n MENOR!!! \n");

        InsPorNrBaloes(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);
    }else{

        if (debug_mode == 1) printf("\n MAIOR!!! \n");

        InsPorNrBaloes(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
    }

   if (!*Cresceu)
      return;

   if (Ap->n < mm)
   {
      InsereNaPaginaPorNrBaloes(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = 0;
      return;
   }

   ApTemp = (Apontador) malloc(sizeof(Pagina));
   ApTemp->n = 0;
   ApTemp->p[0] = NULL;

   if (i <= m + 1)
   {
      InsereNaPaginaPorNrBaloes(ApTemp, Ap->r[mm - 1], Ap->p[mm]);
      Ap->n--;
      InsereNaPaginaPorNrBaloes(Ap, *RegRetorno, *ApRetorno);
   }else{
      InsereNaPaginaPorNrBaloes(ApTemp, *RegRetorno, *ApRetorno);
   }

   for (j = m + 2; j <= mm; j++)
      InsereNaPaginaPorNrBaloes(ApTemp, Ap->r[j - 1], Ap->p[j]);

   Ap->n = m;
   ApTemp->p[0] = Ap->p[m + 1];
   *RegRetorno = Ap->r[m];
   *ApRetorno = ApTemp;
}

void InsereNaPaginaPorNrBaloes(Apontador Ap, Registro Reg, Apontador ApDir)
{
    int k;
    int NaoAchouPosicao;

    k = Ap->n;
    NaoAchouPosicao = k > 0;

    if (debug_mode == 1){
        printf("\n $$$$$$$$ INSERE NA PAGINA| K: %d , NaoAchouPosicao: %d \n", k, NaoAchouPosicao);
    }

    while (NaoAchouPosicao)
    {
      if (Reg.nr_baloes >= Ap->r[k - 1].nr_baloes)
      {
         NaoAchouPosicao = 0;
         break;
      }
      Ap->r[k] = Ap->r[k - 1];
      Ap->p[k + 1] = Ap->p[k];
      k--;
      if (k < 1)
         NaoAchouPosicao = 0;
   }
   Ap->r[k] = Reg;
   Ap->p[k + 1] = ApDir;
   Ap->n++;
}

/*------FIM------
    Funções para montar a arvore B pelo campo Número de Balões(tipo inteiro)
*/


/*------INICIO------
    Funções para montar a arvore B pelo campo Nome da Equipe(tipo String)
*/

void InserePorNomeEquipe(Registro Reg, Apontador *Ap)
{
   int Cresceu;
   Registro RegRetorno;
   Apontador ApRetorno;
   Apontador ApTemp;

   InsPorNomeEquipe(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

   if (debug_mode) printf("\n Cresceu= %d \n", Cresceu);

   if (Cresceu) {

        if (debug_mode) printf("\n @@@ OK @@@ \n");

        ApTemp = (Apontador) malloc(sizeof(Pagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
   }
}

void InsPorNomeEquipe(Registro Reg, Apontador Ap, int *Cresceu, Registro *RegRetorno, Apontador *ApRetorno)
{
   Apontador ApTemp;
   int i, j;

   if (Ap == NULL)
   {
      *Cresceu = 1;
      *RegRetorno = Reg;
      *ApRetorno = NULL;
      return;
   }

   i = 1;

   if (debug_mode){
       printf("\n.....Posicionando.....\n",Ap->n);
       printf("i: %d , Ap->n: %d , Ap->r[i - 1].nome_equipe: %s ", i,Ap->n,Ap->r[i - 1].nome_equipe);
   }

   while (i < Ap->n && stricmp(Reg.nome_equipe, Ap->r[i - 1].nome_equipe) == 1){
        i++;

        if (debug_mode){
            printf("\ni: %d , Ap->n: %d , Ap->r[i - 1].nome_equipe: %s ", i,Ap->n,Ap->r[i - 1].nome_equipe);
        }
   }

   if (debug_mode){
        printf("\n.....Comparando com ID: %d , nome: %s \n", Ap->r[i - 1].id, Ap->r[i - 1].nome_equipe);
   }

    if (stricmp(Reg.nome_equipe, Ap->r[i - 1].nome_equipe) == 0){

        if (debug_mode)  printf("\n IGUAL!!! \n");

        while (i < Ap->n && stricmp(Reg.nome_equipe, Ap->r[i].nome_equipe) == 0){
            i++;

            if (debug_mode){
                printf("\ni: %d , Ap->n: %d , Ap->r[i - 1].nome_equipe: %s ", i,Ap->n,Ap->r[i - 1].nome_equipe);
            }
       }

        InsPorNomeEquipe(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

   }else  if (stricmp(Reg.nome_equipe, Ap->r[i - 1].nome_equipe) < 0){

        if (debug_mode) printf("\n MENOR!!! \n");

        InsPorNomeEquipe(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);
    }else{

        if (debug_mode) printf("\n MAIOR!!! \n");

        InsPorNomeEquipe(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
    }

   if (!*Cresceu)
      return;

   if (Ap->n < mm)
   {
      InsereNaPaginaPorNomeEquipe(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = 0;
      return;
   }

   ApTemp = (Apontador) malloc(sizeof(Pagina));
   ApTemp->n = 0;
   ApTemp->p[0] = NULL;

   if (i <= m + 1)
   {
      InsereNaPaginaPorNomeEquipe(ApTemp, Ap->r[mm - 1], Ap->p[mm]);
      Ap->n--;
      InsereNaPaginaPorNomeEquipe(Ap, *RegRetorno, *ApRetorno);
   }else{
      InsereNaPaginaPorNomeEquipe(ApTemp, *RegRetorno, *ApRetorno);
   }

   for (j = m + 2; j <= mm; j++)
      InsereNaPaginaPorNomeEquipe(ApTemp, Ap->r[j - 1], Ap->p[j]);

   Ap->n = m;
   ApTemp->p[0] = Ap->p[m + 1];
   *RegRetorno = Ap->r[m];
   *ApRetorno = ApTemp;
}

void InsereNaPaginaPorNomeEquipe(Apontador Ap, Registro Reg, Apontador ApDir)
{
    int k;
    int NaoAchouPosicao;

    k = Ap->n;
    NaoAchouPosicao = k > 0;

    if (debug_mode){
        printf("\n $$$$$$$$ INSERE NA PAGINA| K: %d , NaoAchouPosicao: %d \n", k, NaoAchouPosicao);
    }

    while (NaoAchouPosicao)
    {
      if (stricmp(Reg.nome_equipe, Ap->r[k - 1].nome_equipe) == 1 || stricmp(Reg.nome_equipe, Ap->r[k - 1].nome_equipe) == 0)
      {
         NaoAchouPosicao = 0;
         break;
      }
      Ap->r[k] = Ap->r[k - 1];
      Ap->p[k + 1] = Ap->p[k];
      k--;
      if (k < 1)
         NaoAchouPosicao = 0;
   }
   Ap->r[k] = Reg;
   Ap->p[k + 1] = ApDir;
   Ap->n++;
}

/*------FIM------
    Funções para montar a arvore B pelo campo Nome da Equipe(tipo String)
*/

void Imprime(Apontador p, int Nivel)
{

   int i;

   if (p == NULL)
      return;

   for (i = 1; i <= Nivel; i++)
      printf("      ");

   for (i = 0; i < p->n; i++){
      printf("%d   ", p->r[i].id);
      //printf("%d:%d   ", p->r[i].id,p->r[i].nr_baloes);
    }

   putchar('\n');

   for (i = 0; i <= p->n; i++)
      Imprime(p->p[i], Nivel + 1);
}

void imprimirNrBaloes(Apontador p, FILE *fp){

    int i = 0;

   if (p == NULL)
      return;

   for (i = 0; i < p->n; i++){

        imprimirNrBaloes(p->p[i], fp);

        fprintf(fp,"\n");
        fprintf(fp,"ID: %d", p->r[i].id);
        fprintf(fp," / baloes: %d", p->r[i].nr_baloes);
   }

   imprimirNrBaloes(p->p[p->n], fp);
}

void imprimirNomes(Apontador p, FILE *fp){

    int i = 0;

   if (p == NULL)
      return;

   for (i = 0; i < p->n; i++){

        imprimirNomes(p->p[i], fp);

        fprintf(fp,"\n");
        fprintf(fp,"ID: %d", p->r[i].id);
        fprintf(fp," / nome: %s ", p->r[i].nome_equipe);
   }

   imprimirNomes(p->p[p->n], fp);
}
//Grava em arquivo binario para Nome Equipes
void impNomeEquipe(Apontador p, FILE *fp, IndiceNomeEquipe nomeEquipe){

    if (p == NULL)
        return;

    int i = 0;

    for (i = 0; i < p->n; i++){

        impNomeEquipe(p->p[i], fp, nomeEquipe);

        nomeEquipe.id = p->r[i].id;
        strcpy(nomeEquipe.nome_equipe, p->r[i].nome_equipe);

        if (!fwrite(&nomeEquipe,sizeof(IndiceNomeEquipe),1,fp)){
            cleanScreen();
            printf("Erro de gravacao no arquivo");
            exit(0);
        }

    }

    impNomeEquipe(p->p[p->n], fp, nomeEquipe);

}

//Faz a leitura de N linhas do arquivo binario de Nomes
void imprimeNomesOrdem(int qtd_lines)
{
    FILE *fp;
    int qtd_lines_aux = 0;

    IndiceNomeEquipe equipe[qtd_lines];

    if ((fp=fopen(arquivoIndiceNomeEquipe,"rb"))==NULL){
        cleanScreen();
        printf("Erro ao abrir aquivo");
        exit(0);
    }else{

        fread(&equipe,sizeof(IndiceNomeEquipe),qtd_lines,fp);

        while(qtd_lines_aux < qtd_lines){

            printf("ID: %i",equipe[qtd_lines_aux].id);
            printf("\nNome Equipe: %s",equipe[qtd_lines_aux].nome_equipe);
            printf("\n\n");

            qtd_lines_aux++;
        }

        fclose(fp);
    }
}

//Grava em arquivo binario
void impNrBaloes(Apontador p, FILE *fp, IndiceNrBaloes nrBaloes){

    if (p == NULL)
        return;

    int i = 0;

    for (i = 0; i < p->n; i++){

        impNrBaloes(p->p[i], fp, nrBaloes);

        nrBaloes.id = p->r[i].id;
        nrBaloes.nr_baloes = p->r[i].nr_baloes;

        if (!fwrite(&nrBaloes,sizeof(IndiceNrBaloes),1,fp)){
            cleanScreen();
            printf("Erro de gravacao no arquivo");
            exit(0);
        }
    }

    impNrBaloes(p->p[p->n], fp, nrBaloes);

}

//Faz a leitura de N linhas do arquivo de Numero de Baloes
void imprimeNrBaloesOrdem(int qtd_lines)
{
    FILE *fp;
    int qtd_lines_aux = 0;

    IndiceNrBaloes numero_baloes[qtd_lines];

    if ((fp=fopen(arquivoIndiceNumeroBaloes,"rb"))==NULL){
        cleanScreen();
        printf("Erro ao abrir aquivo");
        exit(0);
    }else{

        fread(&numero_baloes,sizeof(IndiceNrBaloes),qtd_lines,fp);

        while(qtd_lines_aux < qtd_lines){

            printf("ID: %i",numero_baloes[qtd_lines_aux].id);
            printf("\nNr. baloes: %i",numero_baloes[qtd_lines_aux].nr_baloes);
            printf("\n\n");

            qtd_lines_aux++;
        }

        fclose(fp);
    }
}

//Limpa a tela
void cleanScreen(){
    system("cls");
}
