#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define m 2
#define mm 4
#define reservado "cls"

//Nome do arquivo
const char filename[] = "arquivo.bin";

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

typedef int TipoChave;
typedef struct
{
   TipoChave Chave;
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

void Pesquisa(Registro *x, Apontador Ap)
{
   int i;

   if (Ap == NULL)
   {
      printf("Erro: Registro nao esta presente\n");
      getchar();
      getchar();
      return;
   }
   i = 1;
   while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave)
      i++;
   if (x->Chave == Ap->r[i - 1].Chave)
   {
      *x = Ap->r[i - 1];
      return;
   }
   if (x->Chave < Ap->r[i - 1].Chave)
      Pesquisa(x, Ap->p[i - 1]);
   else
      Pesquisa(x, Ap->p[i]);
} /* Pesquisa */

void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir)
{
   int k;
   int NaoAchouPosicao;

   k = Ap->n;
   NaoAchouPosicao = k > 0;
   while (NaoAchouPosicao)
   {
      if (Reg.Chave >= Ap->r[k - 1].Chave)
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
}   /*InsereNaPagina*/

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
   while (i < Ap->n && Reg.Chave > Ap->r[i - 1].Chave)
      i++;
   if (Reg.Chave == Ap->r[i - 1].Chave)
   {
      printf(" Erro: Registro ja esta presente\n");
      getchar();
      getchar();
      *Cresceu = 0;
      return;
   }
   if (Reg.Chave < Ap->r[i - 1].Chave)
      Ins(Reg, Ap->p[i - 1], Cresceu, RegRetorno, ApRetorno);
   else
      Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
   if (!*Cresceu)
      return;
   if (Ap->n < mm)
   {   /* Pagina tem espaco */
      InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = 0;
      return;
   }
   /* Overflow: Pagina tem que ser dividida */
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
}   /*Ins*/


void Insere(Registro Reg, Apontador *Ap)
{
   int Cresceu;
   Registro RegRetorno;
   Apontador ApRetorno;
   Apontador ApTemp;

   Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
   if (Cresceu) { /* Arvore cresce na altura pela raiz */
      ApTemp = (Apontador) malloc(sizeof(Pagina));
      ApTemp->n = 1;
      ApTemp->r[0] = RegRetorno;
      ApTemp->p[1] = ApRetorno;
      ApTemp->p[0] = *Ap;
      *Ap = ApTemp;
   }
}   /*Insere*/

void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, int *Diminuiu)
{
   Apontador Aux;
   int DispAux, j;

   if (PosPai < ApPai->n) {   /* Aux = Pagina a direita de ApPag */
      Aux = ApPai->p[PosPai + 1];
      DispAux = (Aux->n - m + 1) / 2;
      ApPag->r[ApPag->n] = ApPai->r[PosPai];
      ApPag->p[ApPag->n + 1] = Aux->p[0];
      ApPag->n++;
      if (DispAux > 0) {   /* Existe folga: transfere de Aux para ApPag */
         for (j = 1; j < DispAux; j++)
            InsereNaPagina(ApPag, Aux->r[j - 1], Aux->p[j]);
         ApPai->r[PosPai] = Aux->r[DispAux - 1];
         Aux->n -= DispAux;
         for (j = 0; j < Aux->n; j++)
            Aux->r[j] = Aux->r[j + DispAux];
         for (j = 0; j <= Aux->n; j++)
            Aux->p[j] = Aux->p[j + DispAux];
         *Diminuiu = 0;
      }
      else
      { /* Fusao: intercala Aux em ApPag e libera Aux */
         for (j = 1; j <= m; j++)
            InsereNaPagina(ApPag, Aux->r[j - 1], Aux->p[j]);
         free(Aux);
         for (j = PosPai + 1; j < ApPai->n; j++)
         {    /* Preenche vazio em ApPai */
            ApPai->r[j - 1] = ApPai->r[j];
            ApPai->p[j] = ApPai->p[j + 1];
         }
         ApPai->n--;
         if (ApPai->n >= m)
            *Diminuiu = 0;
      }
   }
   else
   { /* Aux = Pagina a esquerda de ApPag */
      Aux = ApPai->p[PosPai - 1];
      DispAux = (Aux->n - m + 1) / 2;
      for (j = ApPag->n; j >= 1; j--)
         ApPag->r[j] = ApPag->r[j - 1];
      ApPag->r[0] = ApPai->r[PosPai - 1];
      for (j = ApPag->n; j >= 0; j--)
         ApPag->p[j + 1] = ApPag->p[j];
      ApPag->n++;
      if (DispAux > 0) {   /* Existe folga: transfere de Aux para ApPag */
         for (j = 1; j < DispAux; j++)
            InsereNaPagina(ApPag, Aux->r[Aux->n - j], Aux->p[Aux->n - j + 1]);
         ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
         ApPai->r[PosPai - 1] = Aux->r[Aux->n - DispAux];
         Aux->n -= DispAux;
         *Diminuiu = 0;
      }
      else
      {   /* Fusao: intercala ApPag em Aux e libera ApPag */
         for (j = 1; j <= m; j++)
            InsereNaPagina(Aux, ApPag->r[j - 1], ApPag->p[j]);
         free(ApPag);
         ApPai->n--;
         if (ApPai->n >= m)
            *Diminuiu = 0;
      }
   }
}   /* Reconstitui */

void Antecessor(Apontador Ap, int Ind, Apontador ApPai, int *Diminuiu)
{
   if (ApPai->p[ApPai->n] != NULL)
   {
      Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
      if (*Diminuiu)
         Reconstitui(ApPai->p[ApPai->n], ApPai, ApPai->n, Diminuiu);
      return;
   }
   Ap->r[Ind - 1] = ApPai->r[ApPai->n - 1];
   ApPai->n--;
   *Diminuiu = ApPai->n < m;
}   /* Antecessor */

void Ret(TipoChave Ch, Apontador *Ap, int *Diminuiu)
{
   int Ind, j;
   Apontador WITH;

   if (*Ap == NULL)
   {
      printf("Erro: registro nao esta na arvore\n");
      getchar();
      getchar();
      *Diminuiu = 0;
      return;
   }
   WITH = *Ap;
   Ind = 1;
   while (Ind < WITH->n && Ch > WITH->r[Ind - 1].Chave)
      Ind++;
   if (Ch == WITH->r[Ind - 1].Chave)
   {
      if (WITH->p[Ind - 1] == NULL) {   /* Pagina folha */
         WITH->n--;
         *Diminuiu = WITH->n < m;
         for (j = Ind; j <= WITH->n; j++)
         {
            WITH->r[j - 1] = WITH->r[j];
            WITH->p[j] = WITH->p[j + 1];
         }
         return;
      }
      Antecessor(*Ap, Ind, WITH->p[Ind - 1], Diminuiu);
      if (*Diminuiu)
         Reconstitui(WITH->p[Ind - 1], *Ap, Ind - 1, Diminuiu);
      return;
   }
   if (Ch > WITH->r[Ind - 1].Chave)
      Ind++;
   Ret(Ch, &WITH->p[Ind - 1], Diminuiu);
   if (*Diminuiu)
      Reconstitui(WITH->p[Ind - 1], *Ap, Ind - 1, Diminuiu);
}   /* Ret */


void Retira(TipoChave Ch, Apontador *Ap)
{
   int Diminuiu;
   Apontador Aux;

   Ret(Ch, Ap, &Diminuiu);
   if (Diminuiu && (*Ap)->n == 0) { /* Arvore diminui na altura */
      Aux = *Ap;
      *Ap = Aux->p[0];
      free(Aux);
   }
}   /* Retira */


void Busca(TipoChave Ch, Apontador *Ap)
{

   int Ind, j;
   Apontador WITH;

   if (*Ap == NULL)
   {
      printf("Erro: registro nao esta na arvore\n");
      //getchar();
      //getchar();
      return;
   }

//teste

//   printf("Chave: %d", Ap->n);


   WITH = *Ap;
   Ind = 1;

//printf("n: %d", WITH->n);

   while (Ind < WITH->n && Ch > WITH->r[Ind - 1].Chave)
      Ind++;

   if (Ch == WITH->r[Ind - 1].Chave)
   {
      printf("Valor encontrado!");

      return;
   }

   if (Ch > WITH->r[Ind - 1].Chave)
      Ind++;
   Busca(Ch, &WITH->p[Ind - 1]);

}   /* Busca */

void Imprime(Apontador p, int Nivel)
{
   int i;

   if (p == NULL)
      return;
   for (i = 1; i <= Nivel; i++)
      printf("      ");
   for (i = 0; i < p->n; i++)
      printf("%4d", p->r[i].Chave);
   putchar('\n');
   for (i = 0; i <= p->n; i++)
      Imprime(p->p[i], Nivel + 1);
}

int main()
{

   Apontador *arv;
   Registro reg;
   char tecla;
   system(reservado);
   arv=(Apontador*) malloc(sizeof(Apontador));
   Inicializa(arv);

   system(reservado);
   printf("MENU DE OPCOES\n");
   printf("--------------\n");
   while(1)
   {
      system(reservado);
      printf("MENU DE OPCOES\n");
      printf("--------------\n");
      printf("1. Insere\n");
      printf("2. Remocao\n");
      printf("3. Visualizar\n");
      printf("4. Busca\n");
      printf("5. Sair\n");
      printf("--> ");
      scanf("%c", &tecla);
      if (tecla=='5')
         break;
      switch(tecla)
      {
         case '1':
            while(1)
            {
                system(reservado);
                printf("INSERCAO\n");
                printf("--------\n");
                printf("Digite o valor da chave a ser inserida: (999 para finalizar)\n--> ");
                scanf("%d", &reg.Chave);
                if (reg.Chave==999)
                   break;
                Insere(reg, arv);
             }
         break;
         case '2':
            while(1)
            {
                system(reservado);
                printf("REMOCAO\n");
                printf("-------\n");
                printf("Digite o valor da chave a ser removida: (999 para finalizar)\n--> ");
                scanf("%d", &reg.Chave);
                if (reg.Chave==999)
                   break;
                Retira(reg.Chave, arv);
             }
         break;
         case '3':
            system(reservado);
            printf("IMPRESSAO\n");
            printf("---------\n");
            Imprime(*arv, mm);
            getchar();
            getchar();
         break;
         case '4': //TESTE
            system(reservado);
            printf("BUSCA\n");

            printf("-------\n");
            printf("Digite o valor da chave a ser consultado: (999 para finalizar)\n--> ");
            scanf("%d", &reg.Chave);
            if (reg.Chave==999)
               break;

            Busca(reg.Chave, arv);

            getchar();
            getchar();

        break;
        case '6':

            readNRegistry(100);

            getchar();
            getchar();

            break;
      }
   }
   getchar();
}

//Faz a leitura de N linhas do arquivo
void readNRegistry(int qtd_lines)
{
    FILE *fp;
    int qtd_lines_aux = 0;

    EquipeMaratona equipe[qtd_lines];//Vetor da struct EquipeMaratona

    if ((fp=fopen(filename,"rb"))==NULL){
        cleanScreen();
        printf("Erro ao abrir aquivo");
        exit(0);
    }else{

        fread(&equipe,sizeof(EquipeMaratona),qtd_lines,fp);

        while(qtd_lines_aux < qtd_lines){

            printf("ID: %i",equipe[qtd_lines_aux].id);
            printf("\nNome Equipe: %s",equipe[qtd_lines_aux].nome_equipe);
            printf("\nNome Componente 1: %s",equipe[qtd_lines_aux].nome_componente_1);
            printf("\nNome Componente 2: %s",equipe[qtd_lines_aux].nome_componente_2);
            printf("\nNome Componente 3: %s",equipe[qtd_lines_aux].nome_componente_3);
            printf("\nNumero baloes: %i",equipe[qtd_lines_aux].nr_baloes);
            printf("\nTentativas falsas: %i",equipe[qtd_lines_aux].nr_tentativas_falsas);

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
