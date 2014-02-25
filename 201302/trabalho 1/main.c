#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Textos aleatórios para gerar dados aleatórios no arquivo
char NamePrefix[][8] = {
	"", "belpfei", "narton", "xanwwr", "bellpe","natr", "evon",
};
char NameSuffix[][5] = {
	"", "usas", "ixuc", "oxi", "ith","ath", "umdo", "ator", "or", "axia",
	"imus", "ais", "itur", "orex", "olod","ype"
};
const char NameStems[][10] = {
	"adurino", "aes", "anim", "apollo", "imacaco",
	"educacao", "equis", "extreme", "guius", "hannsapo",
	"equipe", "amora", "hummmmm", "iace", "ille",
	"inept", "iuvo", "obeso", "oculto", "orbis"
};

//Nome do arquivo
const char filename[] = "arquivo.bin";

//Declaração de todas as funções
void NameGen(char *PlayerName);
void createFile(int qtd_lines);
void writeOneLine();
void writeNLines(int qtd_lines);
void readOneRegistry(int idEquipe);
void readNRegistry(int qtd_lines);
void cleanScreen();
long linesFileCount();

//quantidade total de registros no arquivo atualmente
unsigned int qtd_total_lines;

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

int main()
{
    int option; //opções do menu
    int qtd_lines; //auxiliar para tratar quantidade de linhas do arquivo

    int qtd_lines_to_create; //quantidade de linhas para criação padrão do arquivo
    qtd_lines_to_create = 11000000;

    int status=1,temp; //Variaveis para auxiliar a visualização em tela

    int idEquipe;//Para leitura do ID da equipe

    while(option != 0){

        qtd_total_lines = linesFileCount(); //Recalcular a quantidade de linhas no arquivo
        cleanScreen();

        printf("Escolha uma das opcoes:");
        printf("\n1 - Geracao aleatoria de registros(%d linhas)",qtd_lines_to_create);
        printf("\n2 - Gravacao de um registro individual");
        printf("\n3 - Gravacao de um bloco de N registros");
        printf("\n4 - Leitura de um registro individual");
        printf("\n5 - Leitura de um bloco de N registros");
        printf("\n0 - Sair");
        if (qtd_total_lines == 0)
            printf("\n*Arquivo sem registros ou inexistente");
        else
            printf("\n*O arquivo possui %d registros", qtd_total_lines);
        printf("\n\n");

        scanf("%i", &option);

        cleanScreen();
        switch(option){
            case 1:
                printf("Criando arquivo...");
                createFile(qtd_lines_to_create);
                getch();
            break;
            case 2:
                writeOneLine();
                getch();
            break;
            case 3:
                qtd_lines = 0;

                do{
                    cleanScreen();

                    if (status != 1)printf("**Por favor, digite somente numeros...\n");
                    if (qtd_lines<0 && status == 1)
                        printf("**Por favor, digite numeros maior do que zero(0)...\n");

                    printf("*Informe zero(0) para voltar.\nDigite quantidade de linhas:");
                    status = scanf("%d", &qtd_lines);

                    if (status != 1){
                        while((temp=getchar()) != EOF && temp != '\n');
                    }
                }while(status!=1 || qtd_lines<0);

                if (qtd_lines > 0) {
                    writeNLines(qtd_lines);
                    getch();
                }

            break;
            case 4: //Busca o registro por ID da equipe

                printf("Digite o codico (ID) da equipe:");
                scanf("%i", &idEquipe);

                readOneRegistry(idEquipe);
                getch();
            break;
            case 5:
                qtd_lines = 0;

                do{
                    cleanScreen();

                    if (status != 1)printf("**Por favor, digite somente numeros...\n");

                    if (qtd_lines > qtd_total_lines && status == 1)
                        printf("**Existem somente %d registros...\n",qtd_total_lines);
                    if (qtd_lines<0 && status == 1)
                        printf("**Por favor, digite numero maior do que zero(0)...\n");

                    printf("*Digite 0 (zero) para sair.\nDigite quantidade de linhas:");
                    status = scanf("%d", &qtd_lines);

                    if (status != 1){
                        while((temp=getchar()) != EOF && temp != '\n');
                    }
                }while(status!=1 || qtd_lines<0 || qtd_lines > qtd_total_lines);

                if (qtd_lines > 0){
                    readNRegistry(qtd_lines);
                    getch();
                }
            break;
            default:
                exit(0);
            break;
        }

        cleanScreen();
    }

    return 0;
}
//Função para criar o arquivo
void createFile(int qtd_lines){

    FILE *fp;
    int i;

    EquipeMaratona equipe;

    char NomeComponente[21];
    char NomeEquipe[21];

    if ((fp=fopen(filename,"wb"))==NULL){
        cleanScreen();
        printf("Erro ao criar aquivo");
        exit(0);
    }else{

        for (i=0;i<qtd_lines;i++){

            NameGen(NomeComponente);
            strcpy(equipe.nome_componente_1,NomeComponente);
            NameGen(NomeComponente);
            strcpy(equipe.nome_componente_2,NomeComponente);
            NameGen(NomeComponente);
            strcpy(equipe.nome_componente_3,NomeComponente);

            NameGen(NomeEquipe);
            strcpy(equipe.nome_equipe,&NomeEquipe);
            equipe.id = (i+1);

            equipe.nr_baloes = (rand() % 10);
            equipe.nr_tentativas_falsas = (rand() % 10);

            if (!fwrite(&equipe,sizeof(EquipeMaratona),1,fp)){
                cleanScreen();
                printf("Erro de gravacao no arquivo");
                exit(0);
            }
        }
        cleanScreen();
        printf("Arquivo de %d registros criado com sucesso! ",i);
        fclose(fp);
    }
}

void writeOneLine(){

    FILE *fp;
    int i;

    EquipeMaratona equipe;

    char NomeComponente[21];
    char NomeEquipe[28];

    if ((fp=fopen(filename,"ab"))==NULL){
        cleanScreen();
        printf("Erro ao criar aquivo");
        exit(0);
    }else{

        NameGen(NomeComponente);
        strcpy(equipe.nome_componente_1,NomeComponente);
        NameGen(NomeComponente);
        strcpy(equipe.nome_componente_2,NomeComponente);
        NameGen(NomeComponente);
        strcpy(equipe.nome_componente_3,NomeComponente);

        NameGen(NomeEquipe);
        strcpy(equipe.nome_equipe,&NomeEquipe);
        equipe.id = (qtd_total_lines+1);

        equipe.nr_baloes = (rand() % 10);
        equipe.nr_tentativas_falsas = (rand() % 10);

        if (!fwrite(&equipe,sizeof(EquipeMaratona),1,fp)){
            cleanScreen();
            printf("Erro de gravacao no arquivo");
            exit(0);
        }

        printf("Adicionado registro com sucesso!");
        fclose(fp);
    }
}
//Grava N registros após o ultimo registro do arquivo
void writeNLines(int qtd_lines){

    FILE *fp;
    int i;

    EquipeMaratona equipe;

    char NomeComponente[21];
    char NomeEquipe[28];

    if ((fp=fopen(filename,"ab"))==NULL){
        cleanScreen();
        printf("Erro ao criar aquivo");
        exit(0);
    }else{
        for (i=0;i<qtd_lines;i++){

            NameGen(NomeComponente);
            strcpy(equipe.nome_componente_1,NomeComponente);
            NameGen(NomeComponente);
            strcpy(equipe.nome_componente_2,NomeComponente);
            NameGen(NomeComponente);
            strcpy(equipe.nome_componente_3,NomeComponente);

            NameGen(NomeEquipe);
            strcpy(equipe.nome_equipe,&NomeEquipe);
            equipe.id = (qtd_total_lines+1);

            equipe.nr_baloes = (rand() % 10);
            equipe.nr_tentativas_falsas = (rand() % 10);

            if (!fwrite(&equipe,sizeof(EquipeMaratona),1,fp)){
                cleanScreen();
                printf("Erro de gravacao no arquivo");
                exit(0);
            }
        }

        printf("Adicionado %d registros com sucesso! ",i);
        fclose(fp);
    }
}

void readOneRegistry(int idEquipe){

    FILE *fp;
    int found = 0; // 0 - não encontrado | 1 - encontrado
    EquipeMaratona equipe;

    if ((fp=fopen(filename,"rb"))==NULL){
        cleanScreen();
        printf("Erro ao abrir aquivo");
        exit(0);
    }else{

        while(1){

            fread(&equipe,sizeof(EquipeMaratona),1,fp);

            if (feof(fp)) break;

            if (equipe.id != idEquipe) continue;

            cleanScreen();
            printf("Registro encontrado: \n\n");

            printf("ID: %i",equipe.id);
            printf("\nNome Equipe: %s",equipe.nome_equipe);
            printf("\nNome Componente 1: %s",equipe.nome_componente_1);
            printf("\nNome Componente 2: %s",equipe.nome_componente_2);
            printf("\nNome Componente 3: %s",equipe.nome_componente_3);
            printf("\nNumero baloes: %i",equipe.nr_baloes);
            printf("\nTentativas falsas: %i",equipe.nr_tentativas_falsas);

            printf("\n\n");

            found = 1;
            break;
        }
        fclose(fp);
    }

    if (found == 0)
        printf("Nenhum registro encontrado...");
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
//Conta quantas linhas tem o arquivo
long linesFileCount(){

    printf("Calculando quantidade de registros no arquivo, aguarde...");

    FILE *fp;

    unsigned int qtd_file_lines = 0;

    EquipeMaratona equipe;

    if ((fp=fopen(filename,"rb"))==NULL){
        cleanScreen();
        printf("aquivo não encontrado: %s", filename);
        return 0;
    }else{

        while (1){
            fread(&equipe,sizeof(EquipeMaratona),1,fp);
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
//Concatena as strings aleatórias para gerar um texto aleatório
void NameGen(char* PlayerName)
{
	PlayerName[0]=0;
	strcat(PlayerName, NamePrefix[(rand() % 7)]);
	strcat(PlayerName, NameStems[(rand() % 20)]);
	strcat(PlayerName, NameSuffix[(rand() % 16)]);
	PlayerName[0]=toupper(PlayerName[0]);
	return;
}
