#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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

# if __APPLE__
#  define IS_MACOS 1
# else
#  define IS_MACOS 0
# endif

#endif
