#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
// #include <windows.h>
#include <time.h>

#define ORG 'X'
#define VAZ '.'
#define TAM 101

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

typedef struct tab{
char nomeJogo[TAM];		//o nome do jogo deve ser relativo ao padrao
						//de inicializacao. Por exemplo, JogoSapo ou JogoBloco
int ciclosVida;			// Define quanto cada jogo vai rodar (ciclos)
int dim1,dim2;			//dimensoes do tabuleiro linhas x colunas
char **m;				//Atenção! Essa matriz terá que ser alocada dinamicamente
						//para que a funcao que inicializa possa funcionar
}Tab;

// # ifdef_WIN32
// #  define IS_WIN 1
// # else
// #  define IS_WIN 0
// # endif

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
