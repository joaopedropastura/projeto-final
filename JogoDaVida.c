#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define ORG 'X'
#define VAZ '.'
#define TAM 101
#define MAX_LINHA 1024
typedef struct tab{
    char nomeJogo[TAM];
    int ciclosVida;
    int dim1,dim2;
    char **m;
}Tab;

void limpaMatriz(Tab *dados_jogos);
void alocaMatriz(Tab *dados_jogos);
char** alocaMatrizAnterior(int nl, int nc);
void desalocaMatriz(Tab *dados_jogos);
void desalocaMatrizAnterior(char **mat, int nl);
void imprimeMatriz(Tab *dados_jogos);
void copiaMatriz(char **mAnt, Tab *dados_jogos);
void atualizaMat(char **mAnt, Tab *dados_jogosc);
void leInicializador(const char *arquivo, Tab *dados_jogos , int xInic , int yInic);
void menuInicJogo(Tab *dados_jogos);
void jogaJogoVida(Tab *dados_jogos);

int main()
{
    int nCiclos;
    Tab dados_jogo;
    printf("Defina o numero de ciclos do jogo: ");
    scanf("%d",&nCiclos);
    dados_jogo.dim1 = 20;
    dados_jogo.dim2 = 20;
    dados_jogo.ciclosVida = nCiclos;

    alocaMatriz(&dados_jogo);

    do{
        menuInicJogo(&dados_jogo);
        jogaJogoVida(&dados_jogo);
        printf("\nJogar Novamente? Pressione enter\nEncerrar Programa(S)\n");
    }while(getchar()!= 'S');
    desalocaMatriz(&dados_jogo);
}

void limpaMatriz(Tab *dados_jogos)
{
    int i,j;
    for(i=0;i<dados_jogos->dim1;i++)
        for(j=0;j<dados_jogos->dim2;j++)
            dados_jogos->m[i][j]=VAZ;
}
void alocaMatriz(Tab *dados_jogos)
{
    char **m;
    int i;
    dados_jogos->m = (char**)malloc(dados_jogos->dim1*sizeof(char*));
    if( dados_jogos->m == NULL) {printf ("Erro de alocacao da matriz!!");exit (1);}
    for(i=0; i<dados_jogos->dim1; i++){
         dados_jogos->m[i]=(char*)malloc(dados_jogos->dim2*sizeof(char));
        if(dados_jogos->m[i] == NULL){printf(" Erro de alocacao das linhas da matriz!");exit (1);}
    }
}
char** alocaMatrizAnterior(int nl, int nc)
{
    char **m;
    int i;
    m = (char**)malloc(nl*sizeof(char*));
    if(m == NULL) {printf ("Erro de alocacao da matriz!!");exit (1);}
    for(i=0; i<nc; i++){
        m[i]=(char*)malloc(nc*sizeof(char));
        if(m[i] == NULL){printf(" Erro de alocacao das linhas da matriz!");exit (1);}
    }
    return m;
}
void desalocaMatriz(Tab *dados_jogos)
{
    int i;
    for(i=0; i<dados_jogos->dim2; i++)
        free(dados_jogos->m[i]);

    free(dados_jogos->m);
}
void desalocaMatrizAnterior(char **mat, int nl)
{
    int i;
    for(i=0; i<nl; i++)
        free(mat[i]);
    free(mat);
}
void imprimeMatriz(Tab *dados_jogos)
{
    int i, j;
    for(i=0; i<dados_jogos->dim1; i++){
        for(j=0; j<dados_jogos->dim2; j++){
            printf(" %c ", dados_jogos->m[i][j]);
        }
        printf("\n");
    }
}
void copiaMatriz(char **mAnt, Tab *dados_jogos)
{
    int i, j;
    for(i=0; i<dados_jogos->dim1; i++){
        for(j=0; j<dados_jogos->dim2; j++){
            mAnt[i][j] = dados_jogos->m[i][j];
        }
    }
}
void atualizaMat(char **mAnt, Tab *dados_jogos)
{
    int i, j, vivos=0;

    // contando numero de vizinhos vivos
    for(i=0; i<dados_jogos->dim1; i++){
        for(j=0; j<dados_jogos->dim2; j++){
            if (i > 0){
                if(mAnt[i-1][j]==ORG){
                    vivos++;
                }
            }
            if (i < dados_jogos->dim1 -1){
                if(mAnt[i+1][j]==ORG){
                    vivos++;
                }
            }
            if (j > 0){
                if(mAnt[i][j-1]==ORG) vivos++;
            }
            if (j < dados_jogos->dim2 -1){
                if(mAnt[i][j+1]==ORG){
                    vivos++;
                }
            }
            if (i > 0 && j > 0){
                if(mAnt[i-1][j-1]==ORG){
                    vivos++;
                }
            }
            if (i > 0 && j < dados_jogos->dim2-1){
                if(mAnt[i-1][j+1]==ORG){
                    vivos++;
                }
            }
            if (i < dados_jogos->dim1-1 && j > 0){
                if(mAnt[i+1][j-1]==ORG){
                    vivos++;
                }
            }
            if (i < dados_jogos->dim1-1 && j < dados_jogos->dim2-1){
                if(mAnt[i+1][j+1]==ORG){
                    vivos++;
                }
            }
            // Aplicando regras do jogo
            if (dados_jogos->m[i][j] == ORG){
                if (vivos < 2 || vivos > 3){
                    dados_jogos->m[i][j] = VAZ;
                }else {
                    dados_jogos->m[i][j] = ORG;
                }
            }else {
                if (vivos == 3)
                    dados_jogos->m[i][j] = ORG;
                else
                    dados_jogos->m[i][j] = VAZ;
            }
            vivos = 0;
        }
    }
}

void leInicializador(const char *arquivo, Tab *dados_jogos , int xInic , int yInic)
{
    int i=0, j=0;
    char line[MAX_LINHA], *p_tok;

    // Ponteiro para o arquivo de inicializadores
    FILE *p_csv;
    // Abre arquivo para leitura
    p_csv = fopen(arquivo, "r");
    if(p_csv==NULL){
        printf("erro");
        exit(1);
    }
    while(fgets(line, MAX_LINHA, p_csv) != NULL){
        /* função strtok quebra o conteudo da string 'line' em strings menores((tokens))*/
        p_tok = strtok(line, ",");// pega o primeiro token

        // corre pelos outros tokens
        while(p_tok!=NULL){
            j = atoi(p_tok)-1;
            dados_jogos->m[xInic+i][yInic+j]=ORG;
            p_tok = strtok(NULL, ",");
        }
        i++;
    }
    fclose(p_csv);
}

void menuInicJogo(Tab *dados_jogos)
{
    int opcao;
    printf("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\nEntre com a opcao: ");
    scanf("%d",&opcao);
    limpaMatriz(dados_jogos);
    switch(opcao)
    {
         case 1:    leInicializador("bloco.csv", dados_jogos, dados_jogos->dim1/2 , dados_jogos->dim1/2);
                    strcpy ( dados_jogos->nomeJogo, "Jogo da Vida - Bloco" );
                    break;
         case 2:    leInicializador("blinker.csv", dados_jogos,  dados_jogos->dim1/2 , dados_jogos->dim1/2);
                    strcpy ( dados_jogos->nomeJogo, "Jogo da Vida - Blinker" );
                    break;
         case 3:    leInicializador("sapo.csv", dados_jogos ,  dados_jogos->dim1/2 , dados_jogos->dim1/2);
                    strcpy ( dados_jogos->nomeJogo, "Jogo da Vida - Sapo" );
                    break;
         case 4:    leInicializador("glider.csv", dados_jogos ,  dados_jogos->dim1 - 4 , dados_jogos->dim1 - 4);
                    strcpy ( dados_jogos->nomeJogo, "Jogo da Vida - Glider" );
                    break;
         case 5:    leInicializador("LWSS.csv", dados_jogos ,  dados_jogos->dim1 - 5 , dados_jogos->dim1 - 6);
                    strcpy ( dados_jogos->nomeJogo, "Jogo da Vida - LWSS" );
                    break;
    }
    imprimeMatriz(dados_jogos);
    printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo...");while(getchar()!='\n');getchar();
}

void jogaJogoVida(Tab *dados_jogos)
{
    char **mAnt;
    int c;
    //imprimindo na tela a matriz inicial
    system("cls");
    imprimeMatriz(dados_jogos);
    Sleep(100);

    mAnt = alocaMatrizAnterior(dados_jogos->dim1 , dados_jogos->dim2);

    for(c=1;c<=dados_jogos->ciclosVida;c++)
    {
        copiaMatriz(mAnt,dados_jogos);
        atualizaMat(mAnt,dados_jogos);
        Sleep(50);
        system("cls");
        imprimeMatriz(dados_jogos);
        if (dados_jogos->ciclosVida/2==c){
            leInicializador("invasao.csv", dados_jogos, 0, 0);
        }
    }
    desalocaMatrizAnterior(mAnt , dados_jogos->dim2);
}
