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
