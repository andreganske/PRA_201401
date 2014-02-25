#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define m 4
#define mm 8

const int debug_mode = 0;

//Nome do arquivo
const char filename[] = "arquivo.bin";
const char filenamePrint[] = "arvore.txt";

//Define os itens da estrutura
/*typedef struct {

	int id; // sequencial

    // valores aleatórios
	char nome_componente_1[21];
	char nome_componente_2[21];
	char nome_componente_3[21];
	char nome_equipe[20];
	int nr_baloes;
	int nr_tentativas_falsas;

} EquipeMaratona;*/

typedef int TipoChave;
typedef struct
{
    TipoChave Chave;
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

void Inicializa(TipoDicionario *Dicionario)
{
   *Dicionario = NULL;
}   /* Inicializa */




void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir)
{
   int k;
   int NaoAchouPosicao;


   k = Ap->n;
   NaoAchouPosicao = k > 0;


    if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63)){

        printf("\n $$$$$$$$ INSERE NA PAGINA| K: %d , NaoAchouPosicao: %d \n", k, NaoAchouPosicao);
    }


   while (NaoAchouPosicao)
   {
      //if (Reg.Chave >= Ap->r[k - 1].Chave)
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
   if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63)){
       printf("\n.....Posicionando.....\n",Ap->n);
       printf("i: %d , Ap->n: %d , Reg.nr_baloes: %d , Ap->r[i - 1].nr_baloes: %d ", i,Ap->n,Reg.nr_baloes,Ap->r[i - 1].nr_baloes);
   }
   while (i < Ap->n && Reg.nr_baloes > Ap->r[i - 1].nr_baloes){
        i++;
        if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63))
            printf("\ni: %d , Ap->n: %d , Reg.nr_baloes: %d , Ap->r[i - 1].nr_baloes: %d ", i,Ap->n,Reg.nr_baloes,Ap->r[i - 1].nr_baloes);
   }

   if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63)){
        printf("\n.....Comparando com ID: %d , Nr. baloes: %d \n", Ap->r[i - 1].id, Ap->r[i - 1].nr_baloes);
   }

   if (Reg.nr_baloes == Ap->r[i - 1].nr_baloes)
   {


    //Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

//     original
        if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63)){
            printf("\n IGUAL!!! \n");
            //getch();
        }

        Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
        //Ins(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);

      /*Cresceu = 0;
      return;*/


   }else  if (Reg.nr_baloes < Ap->r[i - 1].nr_baloes){

         if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63))
            printf("\n MENOR!!! \n");

          Ins(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);
       }else{

          if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63))
             printf("\n MAIOR!!! \n");

          Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
       }

  if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63))
     printf("\n Cresceu= %d \n", *Cresceu);

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
   }
   else
      InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

   for (j = m + 2; j <= mm; j++)
      InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);

   Ap->n = m;
   ApTemp->p[0] = Ap->p[m + 1];
   *RegRetorno = Ap->r[m];
   *ApRetorno = ApTemp;

   if (debug_mode == 1 && (Reg.id==15||Reg.id==7||Reg.id==52||Reg.id==63)){
       // printf("\n ***** REGISTRO %d INSERIDO EM %d \n", Reg.id,  Ap->n);
   }


}


void Insere(Registro Reg, Apontador *Ap)
{
   int Cresceu;
   Registro RegRetorno;
   Apontador ApRetorno;
   Apontador ApTemp;

   Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
   if (Cresceu) {
      ApTemp = (Apontador) malloc(sizeof(Pagina));
      ApTemp->n = 1;
      ApTemp->r[0] = RegRetorno;
      ApTemp->p[1] = ApRetorno;
      ApTemp->p[0] = *Ap;
      *Ap = ApTemp;
   }
}

void Busca(TipoChave Ch, Apontador *Ap)
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

}

void Imprime(Apontador p, int Nivel)
{
   int i;

   if (p == NULL)
      return;
   for (i = 1; i <= Nivel; i++)
      printf("      ");
   for (i = 0; i < p->n; i++)
      printf("%5d", p->r[i].id);

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

int main()
{
    int qtd_aux = 0,
        arquivo_lido = 0;

    int linhas_arquivo = linesFileCount();

    int qtd_lines = 30;

    FILE *fp;
    int qtd_lines_aux = 0;

    //EquipeMaratona equipe[qtd_lines];

   Apontador *arv;
   Registro reg;
   char tecla;
   cleanScreen();
   arv=(Apontador*) malloc(sizeof(Apontador));
   Inicializa(arv);

   cleanScreen();
   printf("MENU DE OPCOES\n");
   printf("--------------\n");
   while(1)
   {
      cleanScreen();
      printf("MENU DE OPCOES\n");
      printf("Digite 0 (zero) para sair\n");
      printf("--------------\n");
      printf("1. Insere\n");
      printf("2. Visualizar\n");
      printf("3. Busca (qtd. linhas: %d )\n",linhas_arquivo);
      printf("--Com arquivo----------\n");
      printf("4. Ler arquivo\n");
      printf("5. Gravar arquivo com arvore\n");
      printf("6. Gerar arquivo indice\n");
      printf("--> ");

      scanf("%c", &tecla);

      if (tecla=='0')
         break;
      switch(tecla)
      {
         case '1':
                cleanScreen();

                printf("....INICIO INSERCAO...\n");

                if ((fp=fopen(filename,"rb"))==NULL){
                    cleanScreen();
                    printf("Erro ao abrir aquivo");
                    exit(0);
                }else{

                    int nrChave = 0;

                    //while (nrChave<11){
                    while (1){

                        fread(&reg,sizeof(Registro),1,fp);

                        if (feof(fp)) break;

                        //reg.Chave = nrChave++;

                        if (debug_mode == 1 && (reg.id==15||reg.id==7||reg.id==52||reg.id==63)){
                            printf("\n==> INSERINDO REGISTRO %d ", reg.id);
                            printf("\n      NUMERO DE BALOES: %d \n\n", reg.nr_baloes);
                        }

                        Insere(reg, arv);
                    }

                    fclose(fp);

                }

                //cleanScreen();
                printf("\n\n----------------\nArvore montada com sucesso!");
                getch();


                /*
                while(1)
                    {

                    printf("INSERCAO\n");
                    printf("--------\n");
                    printf("Digite o valor da chave a ser inserida: (999 para finalizar)\n--> ");
                    scanf("%d", &reg.Chave);

                    reg.id = reg.Chave;

                    strcpy(reg.nome_componente_1,"joao");

                    if (reg.Chave==9999)
                       break;
                    Insere(reg, arv);
                 }
             */

         break;
         case '2':
            cleanScreen();
            printf("IMPRESSAO\n");
            printf("---------\n");
            //Imprime(*arv, mm);
            Imprime(*arv, 1);

            getch();

         break;
         case '3': //TESTE
            cleanScreen();
            printf("BUSCA\n");

            printf("-------\n");
            printf("Digite o valor da chave a ser consultado: (999 para finalizar)\n--> ");
            scanf("%d", &reg.Chave);
            if (reg.Chave==9999)
               break;

            Busca(reg.Chave, arv);

            getch();

        break;
        case '4':
            readOneRegistry(5);
            /*
            if ((fp=fopen(filename,"rb"))==NULL){
                cleanScreen();
                printf("Erro ao abrir aquivo");
                exit(0);
            }else{

                fread(&equipe,sizeof(EquipeMaratona),qtd_lines,fp);
                fclose(fp);

                arquivo_lido = 1;
                printf("Arquivo lido com sucesso!");
            }

            getch();

*/
             getch();
            break;
        case '5':




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





            /*if (arquivo_lido == 0){
                printf("Arquivo ainda nao lido!");
                getch();
                break;
            }*/

            /*while(qtd_aux < qtd_lines){

                printf("ID: %i",equipe[qtd_aux].id);
                printf("\nNome Equipe: %s",equipe[qtd_aux].nome_equipe);
                printf("\nNome Componente 1: %s",equipe[qtd_aux].nome_componente_1);
                printf("\nNome Componente 2: %s",equipe[qtd_aux].nome_componente_2);
                printf("\nNome Componente 3: %s",equipe[qtd_aux].nome_componente_3);
                printf("\nNumero baloes: %i",equipe[qtd_aux].nr_baloes);
                printf("\nTentativas falsas: %i",equipe[qtd_aux].nr_tentativas_falsas);

                printf("\n\n");

                qtd_aux++;
            }*/



            //Insere2(equipe, arv);





            break;
            case '6':

                //if ((fp=fopen(filenamePrint,"wb"))==NULL){
                if ((fp=fopen(filenamePrint,"w+"))==NULL){
                    cleanScreen();
                    printf("Erro ao abrir aquivo");
                    exit(0);
                }else{

                    geraArquivoBinario(*arv, fp);

                    fclose(fp);

                }

            break;
      }
   }
}

void geraArquivoBinario(Apontador p, FILE *fp){

    int i = 0;

   if (p == NULL)
      return;

   for (i = 0; i < p->n; i++){

        geraArquivoBinario(p->p[i], fp);

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

   geraArquivoBinario(p->p[p->n], fp);



    /*if(raiz!=NULL){

        printf("%d\n", raiz->dado);
        consulta(raiz->esq);
        consulta(raiz->dir);
    }*/

}

/*
void InsereNaPagina2(Apontador Ap, EquipeMaratona Reg, Apontador ApDir)
{
   int k;
   int NaoAchouPosicao;

   k = Ap->n;
   NaoAchouPosicao = k > 0;
   while (NaoAchouPosicao)
   {
      if (Reg.nr_baloes >= Ap->r2[k - 1].nr_baloes)
      {
         NaoAchouPosicao = 0;
         break;
      }
      Ap->r2[k] = Ap->r2[k - 1];
      Ap->p[k + 1] = Ap->p[k];
      k--;
      if (k < 1)
         NaoAchouPosicao = 0;
   }
   Ap->r2[k] = Reg;
   Ap->p[k + 1] = ApDir;
   Ap->n++;
}

void Ins2(EquipeMaratona Reg, Apontador Ap, int *Cresceu, EquipeMaratona *RegRetorno, Apontador *ApRetorno)
{


   Apontador ApTemp;
   int i, j;
printf("---2---");
   if (Ap == NULL)
   {
      *Cresceu = 1;
      *RegRetorno = Reg;
      *ApRetorno = NULL;
      return;
   }

//printf("-> %d", Ap->n);
   i = 1;
   printf("---2.1---");
   while (i < Ap->n && Reg.nr_baloes > Ap->r2[i - 1].nr_baloes)
      i++;

printf("---2.2---");

   if (Reg.nr_baloes == Ap->r2[i - 1].id)
   {
      printf(" Erro: Registro ja esta presente\n");
      getchar();
      getchar();
      *Cresceu = 0;
      return;
   }
   if (Reg.nr_baloes < Ap->r2[i - 1].nr_baloes)
      Ins2(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);
   else
      Ins2(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
   if (!*Cresceu)
      return;
   if (Ap->n < mm)
   {
      InsereNaPagina2(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = 0;
      return;
   }

   ApTemp = (Apontador) malloc(sizeof(Pagina));
   ApTemp->n = 0;
   ApTemp->p[0] = NULL;
   if (i <= m + 1)
   {
      InsereNaPagina2(ApTemp, Ap->r2[mm - 1], Ap->p[mm]);
      Ap->n--;
      InsereNaPagina2(Ap, *RegRetorno, *ApRetorno);
   }
   else
      InsereNaPagina2(ApTemp, *RegRetorno, *ApRetorno);
   for (j = m + 2; j <= mm; j++)
      InsereNaPagina2(ApTemp, Ap->r2[j - 1], Ap->p[j]);
   Ap->n = m;
   ApTemp->p[0] = Ap->p[m + 1];
   *RegRetorno = Ap->r2[m];
   *ApRetorno = ApTemp;
}

void Insere2(EquipeMaratona Reg, Apontador *Ap)
{
   int Cresceu;
   EquipeMaratona RegRetorno;

   Apontador ApRetorno;
   Apontador ApTemp;

printf("---1---");


   if (Ap == NULL)
   {
      //*RegRetorno = Reg;
      //*ApRetorno = NULL;
printf("---NULL---");
      ApTemp = (Apontador) malloc(sizeof(Pagina));
      ApTemp->n = 1;
      ApTemp->r2[0] = Reg;
      ApTemp->p[1] = ApRetorno;
      ApTemp->p[0] = *Ap;
      *Ap = ApTemp;

      return;
   }



    //testeabc(Reg, Ap, &Cresceu, &RegRetorno, &ApRetorno);

    //Ins(Registro Reg, Apontador Ap, int *Cresceu, Registro *RegRetorno, Apontador *ApRetorno)

    //Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
   Ins2(Reg, Ap, &Cresceu, &RegRetorno, &ApRetorno);

printf("---3---");

   if (Cresceu) {
      ApTemp = (Apontador) malloc(sizeof(Pagina));
      ApTemp->n = 1;
      ApTemp->r2[0] = RegRetorno;
      ApTemp->p[1] = ApRetorno;
      ApTemp->p[0] = *Ap;
      *Ap = ApTemp;
   }
}

//void testeabc(Apontador Ap)
void testeabc(EquipeMaratona Reg, Apontador Ap, int *Cresceu, EquipeMaratona *RegRetorno, Apontador *ApRetorno)
{
    printf("aeeee");
}
*/

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
        printf("Chave: %i",equipe[aux].Chave);
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
