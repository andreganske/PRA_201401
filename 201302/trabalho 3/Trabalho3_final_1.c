#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define m 4
#define mm 8

const int debug_mode = 0;

//Nome do arquivo
const char filename[] = "arquivo.bin";
const char filenamePrint[] = "arvore.txt";

const char arquivoDeIndice[] = "indice_arquivo.bin";

const char arquivoNumeroBaloes[] = "ordenado numero baloes.txt";
const char arquivoNomeEquipe[] = "ordenado nome equipe.txt";

typedef struct
{
    int id;

    //criar estrutura para gravar indice no arquivo


} Indice;

typedef struct
{
    int id; // sequencial

    // valores aleatórios
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

int main()
{
    int qtd_aux = 0, arquivo_lido = 0;

    int linhas_arquivo = linesFileCount();

    int qtd_lines = 30;

    FILE *fp;
    int qtd_lines_aux = 0;

    Apontador *arv;
    Registro reg;
    char tecla,tecla2;

    arv=(Apontador*) malloc(sizeof(Apontador));
    Inicializa(arv);

    while(1){

        cleanScreen();
        printf("Escolha uma das opcoes:\n");
        printf("-------------------------\n");
        printf("Montar arvore B em memoria com dados do arquivo \n");
        printf(" > 1. Ordenar pelo campo Nome da Equipe \n");
        printf(" > 2. Ordenar pelo campo Numero de Baloes \n");
        printf("Gerar arquivo de indice\n");
        printf(" > 3. Por Nome de Equipe\n");
        printf(" > 4. Por Numero de Baloes\n");
        printf(" > 0. (zero) para sair\n");

        /*printf("3. Visualizar arvore B\n");
        printf("4. Gravar arquivo texto com arvore(Numero de baloes)\n");
        printf("5. Gerar arquivo texto com Numero de baloes\n");
        printf("6. Gera arquivo texto com Nomes....\n");
        printf("7. Gera arquivo de indice....\n");
        */
        printf("-> ");

        scanf("%c", &tecla);

        if (tecla=='0')
            break;

        switch(tecla){
        case '1':

            *arv = NULL;

            cleanScreen();

            printf("....INICIO INSERCAO...\n");

            if ((fp=fopen(filename,"rb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                while (1){

                    fread(&reg,sizeof(Registro),1,fp);

                    if (feof(fp)) break;

                    if (debug_mode == 1){
                        printf("\n==> INSERINDO REGISTRO, ID: %d ", reg.id);
                        printf("\n      NOME: %s \n\n", reg.nome_equipe);
                    }

                    InserePorNomeEquipe(reg, arv);

                    if (debug_mode == 1){
                        getch();
                    }

                    //cleanScreen();
                    //Imprime(*arv, 1);
                    //getch();
                }

                fclose(fp);
            }


            printf("\n\n------------------\nArvore montada com sucesso!\n------------------\n");
            getch();


        break;
        case '2':

            *arv = NULL;

            cleanScreen();

            printf("....INICIO INSERCAO...\n");

            if ((fp=fopen(filename,"rb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                while (1){

                    fread(&reg,sizeof(Registro),1,fp);

                    if (feof(fp)) break;

                    if (debug_mode == 1){
                        printf("\n==> INSERINDO REGISTRO, ID: %d ", reg.id);
                        printf("\n      NUMERO DE BALOES: %d \n\n", reg.nr_baloes);
                    }

                    Insere(reg, arv);

                    if (debug_mode == 1){
                        getch();
                    }

                    //cleanScreen();
                    //Imprime(*arv, 1);
                    //getch();
                }

                fclose(fp);
            }


            printf("\n\n------------------\nArvore montada com sucesso!\n------------------\n");
            getch();


         break;
         case '3':
            cleanScreen();
            printf("VISUALIZANDO ARVORE B\n");
            printf("---------------------\n");

            Imprime(*arv, 1);

            getch();

         break;
         case '4':

            if ((fp=fopen(filenamePrint,"w+"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                ImprimeArquivo(*arv, 1, fp);

                fclose(fp);
            }

            printf("Arquivo texto gerado com sucesso...");
            getch();

        break;
        case '5':

            if ((fp=fopen(arquivoNumeroBaloes,"w+"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                imprimirNrBaloes(*arv, fp);

                fclose(fp);

            }

        break;
        case '6':

            if ((fp=fopen(arquivoNomeEquipe,"w+"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                imprimirNomes(*arv, fp);

                fclose(fp);

            }

        break;
        case '7':

            if ((fp=fopen(arquivoDeIndice,"wb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                geraIndiceBinarioNomes(*arv, fp);

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
}   /* Inicializa */

void Insere(Registro Reg, Apontador *Ap)
{
   int Cresceu;
   Registro RegRetorno;
   Apontador ApRetorno;
   Apontador ApTemp;

   Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

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

void Ins(Registro Reg, Apontador Ap, int *Cresceu, Registro *RegRetorno, Apontador *ApRetorno)
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




        *Cresceu = 1;

        Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

   }else  if (Reg.nr_baloes < Ap->r[i - 1].nr_baloes){

        if (debug_mode == 1) printf("\n MENOR!!! \n");

        Ins(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);
    }else{

        if (debug_mode == 1) printf("\n MAIOR!!! \n");

        Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
    }



   if (!*Cresceu)
      return;

   if (Ap->n < mm)
   {
      InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = 0;
      return;
   }

   ApTemp = (Apontador) malloc(sizeof(Pagina));
   ApTemp->n = 0;
   ApTemp->p[0] = NULL;

   if (i <= m + 1)
   {
      InsereNaPagina(ApTemp, Ap->r[mm - 1], Ap->p[mm]);
      Ap->n--;
      InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
   }else{
      InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
   }

   for (j = m + 2; j <= mm; j++)
      InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);

   Ap->n = m;
   ApTemp->p[0] = Ap->p[m + 1];
   *RegRetorno = Ap->r[m];
   *ApRetorno = ApTemp;
}

void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir)
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



void InserePorNomeEquipe(Registro Reg, Apontador *Ap)
{
   int Cresceu;
   Registro RegRetorno;
   Apontador ApRetorno;
   Apontador ApTemp;

   InsPorNomeEquipe(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

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

   if (debug_mode == 1){
        printf("\n.....Comparando com ID: %d , nome: %s \n", Ap->r[i - 1].id, Ap->r[i - 1].nome_equipe);
   }

    if (stricmp(Reg.nome_equipe, Ap->r[i - 1].nome_equipe) == 0){

        if (debug_mode)  printf("\n IGUAL!!! \n");

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




/*void Busca(TipoChave Ch, Apontador *Ap)
{
   int Ind, j;
   Apontador WITH;

   if (*Ap == NULL)
   {
      printf("Erro: registro nao esta na arvore\n");
      return;
   }

   WITH = *Ap;
   Ind = 1;

   while (Ind < WITH->n && Ch > WITH->r[Ind - 1].Chave)
      Ind++;

   if (Ch == WITH->r[Ind - 1].Chave)
   {
      printf("Chave: %d ID: %d", WITH->r[Ind - 1].Chave, WITH->r[Ind - 1].id);

      printf("\nNome equipe: %s", WITH->r[Ind - 1].nome_equipe);
      printf("\nNome comp.1: %s", WITH->r[Ind - 1].nome_componente_1);
      printf("\nNome comp.2: %s", WITH->r[Ind - 1].nome_componente_2);
      printf("\nNome comp.3: %s", WITH->r[Ind - 1].nome_componente_3);
      printf("\nQtde. baloes: %d", WITH->r[Ind - 1].nr_baloes);
      printf("\nNr. tentati: %d", WITH->r[Ind - 1].nr_tentativas_falsas);

      return;
   }

   if (Ch > WITH->r[Ind - 1].Chave)
      Ind++;
   Busca(Ch, &WITH->p[Ind - 1]);

}*/

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

void ImprimeArquivo(Apontador p, int Nivel, FILE *fp)
{

   int i;
//fprintf(fp,"%d \n",rand() % (count*10000));
   if (p == NULL)
      return;
   for (i = 1; i <= Nivel; i++)
     fprintf(fp,"----------------");

   for (i = 0; i < p->n; i++){

    //fprintf(fp,"%5d",p->r[i].Chave);
        fprintf(fp,"\n");
        //fprintf(fp,"Chave: %d ", p->r[i].Chave);
        fprintf(fp,"ID: %d", p->r[i].id);
        //fprintf(fp,"\nNome equipe: %s", p->r[i].nome_equipe);
        //fprintf(fp,"\nNome comp.1: %s", p->r[i].nome_componente_1);
        //fprintf(fp,"\nNome comp.2: %s", p->r[i].nome_componente_2);
        //fprintf(fp,"\nNome comp.3: %s", p->r[i].nome_componente_3);
        fprintf(fp," / baloes: %d", p->r[i].nr_baloes);
        //fprintf(fp,"\nNr. tentati: %d", p->r[i].nr_tentativas_falsas);

   }


    fprintf(fp,"\n\n\n");
   //putchar('\n');

   for (i = 0; i <= p->n; i++)
      ImprimeArquivo(p->p[i], Nivel + 1, fp);
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

void geraIndiceBinarioNomes(Apontador p, FILE *fp){

    int i = 0;

    if (p == NULL)
        return;

    for (i = 0; i < p->n; i++){

        geraIndiceBinarioNomes(p->p[i], fp);

        fprintf(fp,"\n");
        fprintf(fp,"ID: %d", p->r[i].id);
        fprintf(fp," / nome: %s ", p->r[i].nome_equipe);
    }

    geraIndiceBinarioNomes(p->p[p->n], fp);


    /*if (!fwrite(&equipe,sizeof(EquipeMaratona),1,fp)){
        cleanScreen();
        printf("Erro de gravacao no arquivo");
        exit(0);
    }*/

}

void readOneRegistry(int idEquipe){

    FILE *fp;
    int found = 0; // 0 - não encontrado | 1 - encontrado

    int aux, qtd_registros = 100;
    Registro equipe[qtd_registros];

    if ((fp=fopen(filename,"rb"))==NULL){
        cleanScreen();
        printf("Erro ao abrir aquivo");
        exit(0);
    }else{

        while(1){

            fread(&equipe,sizeof(Registro),qtd_registros,fp);

            if (feof(fp)) break;

            //if (equipe.id != idEquipe) continue;

            //cleanScreen();

            printf("\n\n");

            found = 1;
            break;
        }
        fclose(fp);
    }

    if (found == 0)
        printf("Nenhum registro encontrado...");

    for(aux=0;aux<qtd_registros;aux++){
        printf("\n----------------------\n");
        //printf("Chave: %i",equipe[aux].Chave);
        printf("\nID: %i",equipe[aux].id);
        printf("\nNome Equipe: %s",equipe[aux].nome_equipe);
        printf("\nNome Componente 1: %s",equipe[aux].nome_componente_1);
        printf("\nNome Componente 2: %s",equipe[aux].nome_componente_2);
        printf("\nNome Componente 3: %s",equipe[aux].nome_componente_3);
        printf("\nNumero baloes: %i",equipe[aux].nr_baloes);
        printf("\nTentativas falsas: %i",equipe[aux].nr_tentativas_falsas);
    }
}

//Conta quantas linhas tem o arquivo
int linesFileCount(){

    printf("Calculando quantidade de registros no arquivo, aguarde...");

    FILE *fp;

    unsigned int qtd_file_lines = 0;

    Registro equipe;

    if ((fp=fopen(filename,"rb"))==NULL){
        cleanScreen();
        printf("aquivo não encontrado: %s", filename);
        return 0;
    }else{

        while (1){
            fread(&equipe,sizeof(Registro),1,fp);
            if (feof(fp)) break;
            qtd_file_lines++;
        }
        fclose(fp);
    }

    return qtd_file_lines;
}


//Limpa a tela
void cleanScreen(){
    system("cls");
}
