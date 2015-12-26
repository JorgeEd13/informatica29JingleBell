/*
Progama: ex29.c;
Funcao: Rodar Jogo da velha;
Autores: Jorge Edson Ribeiro da Silva Neto, Joao Gabriel Gouveia de Souza Brito, Bruna Mayumi Hori, Silas Wesley Maia Marinho;
Contatos: jorge.ed.ribeiro00@gmail.com & gabriel.gouveia@live.com, brunahori19@gmail.com, silas.wesley@hotmail.com;
Orientador: Profº Dr. Ruben Carlo Benante;

Obs: Licença da GNU 2.0
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int modo_jogo=0, dificuldade=0, g_vez=0;

int nivelfacil(int tab[3][3], int vez)
{
    srand(time(NULL));
    int r = rand()%9; //sorteia uma posição aleatoria de 0 a 8

    while(verificaJogadaValida(tab, r)==0) /*caso a posicao ja tenha sido escolhida, decrementa ate achar um posicao*/
    { 
        r--;
        if(r==-1) //caso extrapole a primeira posição, vai pra ultima pra começar a busca
            r=8;
    }

    return r;
}
nivelmedio(int tab[3][3], int vez)
{

    srand(time(NULL));
    int r = rand()%9;

    while(verificaJogadaValida(tab, r)==0)
    {
        r--;
        if(r==-1)
            r=8;
    }

    return r;
}
int niveldificil(int tab[3][3], int vez)
{
    srand(time(NULL));
    int r = rand()%9;

    while(verificaJogadaValida(tab, r)==0)
    {
        r--;
        if(r==-1)
            r=8;
    }                                 
    return r;    

}

int verificarJogo(int tab[3][3])
{
    int i,j,status=3;

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tab[i][j]==0){
                status=0;
            }
        }
    }

    if((tab[0][0] == 1 && tab[0][1] == 1 && tab[0][2] == 1)
            || (tab[1][0] == 1 && tab[1][1] == 1 && tab[1][2] == 1)
            ||(tab[2][0] == 1 && tab[2][1] == 1 && tab[2][2] == 1)
            ||(tab[0][0] == 1 && tab[1][0] == 1 && tab[2][0] == 1)
            ||(tab[0][1] == 1 && tab[1][1] == 1 && tab[2][1] == 1)
            ||(tab[2][0] == 1 && tab[2][1] == 1 && tab[2][2] == 1)
            ||(tab[0][0] == 1 && tab[1][1] == 1 && tab[2][2] == 1)
            ||(tab[2][0] == 1 && tab[1][1] == 1 && tab[0][2] == 1))
        status =1;

    if((tab[0][0] == -1 && tab[0][1] == -1 && tab[0][2] == -1)
            || (tab[1][0] == -1 && tab[1][1] == -1 && tab[1][2] == -1)
            ||(tab[2][0] == -1 && tab[2][1] == -1 && tab[2][2] == -1)
            ||(tab[0][0] == -1 && tab[1][0] == -1 && tab[2][0] == -1)
            ||(tab[0][1] == -1 && tab[1][1] == -1 && tab[2][1] == -1)
            ||(tab[2][0] == -1 && tab[2][1] == -1 && tab[2][2] == -1)
            ||(tab[0][0] == -1 && tab[1][1] == -1 && tab[2][2] == -1)
            ||(tab[2][0] == -1 && tab[1][1] == -1 && tab[0][2] == -1))
        status =2;

    //retorna 0 caso o jogo não tenha terminado
    //retorna 1 caso o jogo tenha terminado e o jogador 1 ganhou
    //retorna 2 caso o jogo tenha terminado e o jogador 2 ganhou
    //retorna 3 caso o jogo terminou e deu velha
    return status;
}

int verificaJogadaValida(int tab[3][3], int pos)
{
    int x=pos/3, y=pos%3;
    if(tab[x][y]==0)
        return 1;

    return 0;
}

void fazerJogada(int tab[3][3], int pos){
    int x=pos/3, y=pos%3;

    tab[x][y]= g_vez;

    if(g_vez ==1)
        g_vez=-1;
    else
        g_vez=1;
}

void imprimeTabuleiro(int tab[3][3]) //imprimir tabuleiro
{
    int i,j;

    printf("\n\n");

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tab[i][j]==1){
                printf(" X ");
            }else if(tab[i][j]==-1) {
                printf(" O ");
            }else{
                printf("   ");
            }

            if(j==0 || j==1){
                printf("|");
            }else if(j==2){
                printf("\n");
            }
        }
        if(i==0 || i==1)
            printf("---+---+---\n");

    }

    printf("\n\n");

}



int main(void)
{
    int tabuleiro[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    do
    {
        printf("Digite o modo de jogo\n1- Humano contra Humano\n2- Computador contra Computador\n3- Humano contra Computador:\n");
        scanf("%d", &modo_jogo);
    }while(modo_jogo<1 && modo_jogo>3);


    if(modo_jogo ==2 || modo_jogo ==3)
    {

        do{
            printf("Digite a dificuldade\n1-facil\n2-medio\n3-dificil:\n");
            scanf("%d", &dificuldade);
        }while(dificuldade<1 && dificuldade>3);

    }
    while(verificarJogo(tabuleiro) == 0)
    {

    }


    return 0;
}

