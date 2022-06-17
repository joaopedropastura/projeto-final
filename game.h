#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define ORG 'X'
#define VAZ '.'
#define TAM 101
typedef struct tab{
char nomeJogo[TAM];		//o nome do jogo deve ser relativo ao padrao
						//de inicializacao. Por exemplo, JogoSapo ou JogoBloco
int ciclosVida;			// Define quanto cada jogo vai rodar (ciclos)
int dim1,dim2;			//dimensoes do tabuleiro linhas x colunas
char **m;				//Atenção! Essa matriz terá que ser alocada dinamicamente
						//para que a funcao que inicializa possa funcionar
}Tab;

void limpaMatriz(Tab *dados_jogos);
void alocaMatriz(Tab *dados_jogos);
void desalocaMatriz(Tab *dados_jogos);
void imprimeMatriz(Tab *dados_jogos);
void copiaMatriz(char **mAnt, Tab *dados_jogos);
void atualizaMat( char **mAnt,Tab *dados_jogos);

void inicBloco(Tab *dados_jogos);
void inicBlinker(Tab *dados_jogos);
void inicSapo(Tab *dados_jogos);
void inicGlider(Tab *dados_jogos);
void inicLWSS(Tab *dados_jogos);

void menuInicJogo(Tab *dados_jogos);
void jogaJogoVida(Tab *dados_jogos);

#endif
