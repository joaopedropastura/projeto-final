#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define ORG 'X'
#define VAZ '.'
#define TAM 101
/*
void limpaMatriz(char **mat, int nl, int nc);
char** alocaMatriz(int nl, int nc);
void desalocaMatriz(char **mat, int nl);
void imprimeMatriz(char **mat, int nl, int nc);
void copiaMatriz(char **mAnt, char **mAtual, int nl, int nc);
void atualizaMat(char **mAtual, char **mAnt, int nl, int nc);

void inicBloco(char **m, int nl, int nc);
void inicBlinker(char **m, int nl, int nc);
void inicSapo(char **m, int nl, int nc);
void inicGlider(char **m, int nl, int nc);
void inicLWSS(char **m, int nl, int nc);

void menuInicJogo(char **mat, int nl, int nc);
void jogaJogoVida(char **mAtual, int nl, int nc, int nCiclos);
*/
typedef struct tab{
char nomeJogo[TAM]; //o nome do jogo deve ser relativo ao padrao
//de inicializacao. Por exemplo, JogoSapo ou JogoBloco
int ciclosVida; // Define quanto cada jogo vai rodar (ciclos)
int dim1,dim2; //dimensoes do tabuleiro linhas x colunas
char **m; //Atenção! Essa matriz terá que ser alocada dinamicamente
//para que a funcao que inicializa possa funcionar
}Tab;




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
void atualizaMat( char **mAnt,Tab *dados_jogos)
{
    int i, j, vivos;

    vivos=0;

    // contar n� de vizinhos vivos
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
                if(mAnt[i][j-1]==ORG){
                    vivos++;
                }
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

            vivos = 0 ;
        }
    }
}

void inicBloco(Tab *dados_jogos)
{
    char padrao[2][2]={{ORG,ORG},{ORG,ORG}};
    int i, j, xInic = dados_jogos->dim1/2, yInic=dados_jogos->dim2/2;

    limpaMatriz(dados_jogos);

    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            (dados_jogos->m)[xInic+i][yInic+j]=padrao[i][j];
}
void inicBlinker(Tab *dados_jogos)
{
    char padrao[1][3]={{ORG,ORG,ORG}};
    int i,j, xInic = dados_jogos->dim1/2, yInic=dados_jogos->dim2/2;

    limpaMatriz(dados_jogos);

    for(i=0;i<1;i++)
        for(j=0;j<3;j++)
            dados_jogos->m[xInic+i][yInic+j]=padrao[i][j];
}
void inicSapo(Tab *dados_jogos)
{
    char padrao[2][4]={{VAZ,ORG,ORG,ORG},{ORG,ORG,ORG,VAZ}};
    int i,j,xInic = dados_jogos->dim1/2, yInic=dados_jogos->dim2/2;

    limpaMatriz(dados_jogos);

    for(i=0;i<2;i++)
        for(j=0;j<4;j++)
            dados_jogos->m[xInic+i][yInic+j]=padrao[i][j];
}
void inicGlider(Tab *dados_jogos)
{
    char padrao[3][3]={{ORG,ORG,ORG},{ORG,VAZ,VAZ},{VAZ,ORG,VAZ}};
    int i,j,xInic,yInic;

    limpaMatriz(dados_jogos);
    xInic = dados_jogos->dim1 - 4;
    yInic = dados_jogos->dim2 - 4;


    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            dados_jogos->m[xInic+i][yInic+j]=padrao[i][j];
}
void inicLWSS(Tab *dados_jogos)
{
    char padrao[4][5]={{VAZ,ORG,VAZ,VAZ,ORG},{ORG,VAZ,VAZ,VAZ,VAZ},{ORG,VAZ,VAZ,VAZ,ORG},{ORG,ORG,ORG,ORG,VAZ}};
    int i,j,xInic,yInic;

    limpaMatriz(dados_jogos);
    xInic = dados_jogos->dim1 - 5;
    yInic = dados_jogos->dim2 - 6;

    for(i=0;i<4;i++)
        for(j=0;j<5;j++)
       dados_jogos->m[xInic+i][yInic+j]=padrao[i][j];
}

void menuInicJogo(Tab *dados_jogos)
{
    int opcao;

    printf("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\nEntre com a opcao: ");
    scanf("%d",&opcao);
    switch(opcao)
    {
         case 1:   inicBloco(dados_jogos); break;
         case 2:   inicBlinker(dados_jogos); break;
         case 3:   inicSapo(dados_jogos); break;
         case 4:   inicGlider(dados_jogos); break;
         case 5:   inicLWSS(dados_jogos); break;
    }

    imprimeMatriz(dados_jogos);
    printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo..."); while(getchar()!='\n'); getchar();
}

void jogaJogoVida(Tab *dados_jogos)
{
    char **mAnt;
    int c;

    //imprimindo na tela a matriz inicial
    system("cls");
    imprimeMatriz(dados_jogos);
    // getchar();
    Sleep(100);

    mAnt = alocaMatrizAnterior(dados_jogos->dim1 , dados_jogos->dim2);

    for(c=1;c<=dados_jogos->ciclosVida;c++)
    {
        copiaMatriz(mAnt,dados_jogos);

        atualizaMat(mAnt,dados_jogos);
        Sleep(10);
        system("cls");
        imprimeMatriz(dados_jogos);
        // getchar();

    }
    desalocaMatrizAnterior(mAnt , dados_jogos->dim2);

}
int main()
{
    Tab dados_jogo;
    dados_jogo.dim1 = 20;
    dados_jogo.dim2 = 20;
    dados_jogo.ciclosVida = 65;
    alocaMatriz(&dados_jogo);
    //imprimeMatriz(&dados_jogo);
    do{
        menuInicJogo(&dados_jogo);
        jogaJogoVida(&dados_jogo);
        printf("\nJogar Novamente? Pressione enter\nEncerrar Programa(S)\n");
    }while(getchar()!= 'S');

    desalocaMatriz(&dados_jogo);
}

test