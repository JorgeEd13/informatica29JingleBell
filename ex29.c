/*
Progama: ex29.c;
Funcao: Rodar Jogo da velha;
Autores: Jorge Edson Ribeiro da Silva Neto, Joao Gabriel Gouveia de Souza Brito, Bruna Mayumi Hori, Silas Wesley Maia Marinho;
Contatos: jorge.ed.ribeiro00@gmail.com & gabriel.gouveia@live.com, brunahori19@gmail.com, silas.wesley@hotmail.com;
Orientador: Profº Dr. Ruben Carlo Benante;
Compile com:
   $ gcc ex29.c -o ex29.x -std=c99

Obs: Licença da GNU 2.0
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>


/* Bordas UTF 8 */

#define WUL L'\u2518' /* ^VU2518 ┘ */
#define WDL L'\u2510' /* ^VU2510 ┐ */
#define WDR L'\u250c' /* ^VU250c ┌ */
#define WUR L'\u2514' /* ^VU2514 └ */
#define WVH L'\u253c' /* ^VU253c ┼ */
#define WHH L'\u2500' /* ^VU2500 ─ */
#define WVR L'\u251c' /* ^VU251c ├ */
#define WVL L'\u2524' /* ^VU2524 ┤ */
#define WUH L'\u2534' /* ^VU2534 ┴ */
#define WDF L'\u252c' /* ^VU252c ┬ */
#define WVV L'\u2502' /* ^VU2502 │ */
#define WGL L'\u2571' /* ^VU2571 ╱ */
#define WGR L'\u2572' /* ^VU2572 ╲ */
#define WGX L'\u2573' /* ^VU2573 ╳ */



int modo_jogo=0, dificuldade=0, g_vez=1, jogada=0,jogador=1;
char comeca='o', jogarNovamente='p';

int nivelfacil(int tab[3][3], int vez)  
{

    srand(time(NULL));
    int r = rand()%9; //sorteia uma posição aleatoria de 0 a 8

    while(verificaJogadaValida(tab, r)==0){ //caso a posição ja tenha sido escolhida, vai decrementando ate achar uma posicao
        r--;
        if(r==-1) //caso extrapole a primeira posição, vai pra ultima pra começar a busca
            r=8;
    }

    return r;
}

int nivelmedio(int tab[3][3], int vez)
{
    /*Se a posição atual da matriz impedir o adversario de ganhar, ou me levar a vitoria, jogo nessa posição*/

    if(tab[0][0] == 0 && ((tab[0][1]==tab[0][2]&&tab[0][1]!=0&&tab[0][2]!=0)||
                (tab[1][0]==tab[2][0]&&tab[1][0]!=0&&tab[2][0]!=0)||
                (tab[1][1]==tab[2][2]&&tab[1][1]!=0&&tab[2][2]!=0)))
        return 0;
    else if(tab[0][1] == 0 && ((tab[0][0]==tab[0][2]&&tab[0][0]!=0&&tab[0][2]!=0)||
                (tab[1][1]==tab[2][1]&&tab[1][1]!=0&&tab[2][1]!=0)))
        return 1;
    else if(tab[0][2] == 0 && ((tab[0][0]==tab[0][1]&&tab[0][0]!=0&&tab[0][1]!=0)||
                (tab[1][2]==tab[2][2]&&tab[1][2]!=0&&tab[2][2]!=0)||
                (tab[1][1]==tab[2][0]&&tab[1][1]!=0&&tab[2][0]!=0)))
        return 2;
    else if(tab[1][0] == 0 && ((tab[1][1]==tab[1][2]&&tab[1][1]!=0&&tab[1][2]!=0)||
                (tab[0][0]==tab[2][0]&&tab[0][0]!=0&&tab[2][0]!=0)))
        return 3;
    else if(tab[1][1] == 0 && ((tab[1][0]==tab[1][2]&&tab[1][0]!=0&&tab[1][2]!=0)||
                (tab[0][1]==tab[2][1]&&tab[0][1]!=0&&tab[2][1]!=0)||
                (tab[0][0]==tab[2][2]&&tab[0][0]!=0&&tab[2][2]!=0)||
                (tab[0][2]==tab[2][0]&&tab[0][2]!=0&&tab[2][0]!=0)))
        return 4;
    else if(tab[1][2] == 0 && ((tab[1][0]==tab[1][1]&&tab[1][0]!=0&&tab[1][1]!=0)||
                (tab[0][2]==tab[2][2]&&tab[0][2]!=0&&tab[2][2]!=0)))
        return 5;
    else if(tab[2][0] == 0 && ((tab[0][0]==tab[1][0]&&tab[0][0]!=0&&tab[1][0]!=0)||
                (tab[2][1]==tab[2][2]&&tab[2][1]!=0&&tab[2][2]!=0)||
                (tab[0][2]==tab[1][1]&&tab[0][2]!=0&&tab[1][1]!=0)))
        return 6;
    else if(tab[2][1] == 0 && ((tab[2][0]==tab[2][2]&&tab[2][0]!=0&&tab[2][2]!=0)||
                (tab[0][1]==tab[1][1]&&tab[0][1]!=0&&tab[1][1]!=0)))
        return 7;
    else if(tab[2][2] == 0 && ((tab[2][0]==tab[2][1]&&tab[2][0]!=0&&tab[2][1]!=0)||
                (tab[0][2]==tab[1][2]&&tab[0][2]!=0&&tab[1][2]!=0)||
                (tab[0][0]==tab[1][1]&&tab[0][0]!=0&&tab[1][1]!=0)))
        return 8;
    else
        return nivelfacil(tab, vez);
}


niveldificil(int tab[3][3], int vez)
{
    /*Se a posição atual da matriz impedir o adversario de ganhar e ao mesmo tempo outra posição da matriz me fizer ganha prefiro jogar na outra posição*/
    int jogada=9;

    if(tab[0][0] == 0 && ((tab[0][1]==vez*-1 && tab[0][2]==vez*-1)||
                (tab[1][0]==vez*-1 &&tab[2][0]==vez*-1 )||
                (tab[1][1]==vez*-1&&tab[2][2]==vez*-1)))
        jogada=0;
    if(tab[0][1] == 0 && ((tab[0][0]==vez*-1&&tab[0][2]==vez*-1)||
                (tab[1][1]==vez*-1&&tab[2][1]==vez*-1)))
        jogada=1;
    if(tab[0][2] == 0 && ((tab[0][0]==vez*-1&&tab[0][1]==vez*-1)||
                (tab[1][2]==vez*-1&&tab[2][2]==vez*-1)||
                (tab[1][1]==vez*-1&&tab[2][0]==vez*-1)))
        jogada=2;
    if(tab[1][0] == 0 && ((tab[1][1]==vez*-1&&tab[1][2]==vez*-1)||
                (tab[0][0]==vez*-1&&tab[2][0]==vez*-1)))
        jogada=3;
    if(tab[1][1] == 0 && ((tab[1][0]==vez*-1&&tab[1][2]==vez*-1)||
                (tab[0][1]==vez*-1&&tab[2][1]==vez*-1)||
                (tab[0][0]==vez*-1&&tab[2][2]==vez*-1)||
                (tab[0][2]==vez*-1&&tab[2][0]==vez*-1)))
        jogada=4;
    if(tab[1][2] == 0 && ((tab[1][0]==vez*-1&&tab[1][1]==vez*-1)||
                (tab[0][2]==vez*-1&&tab[2][2]==vez*-1)))
        jogada=5;
    if(tab[2][0] == 0 && ((tab[0][0]==vez*-1&&tab[1][0]==vez*-1)||
                (tab[2][1]==vez*-1&&tab[2][2]==vez*-1)||
                (tab[0][2]==vez*-1&&tab[1][1]==vez*-1)))
        jogada=6;
    if(tab[2][1] == 0 && ((tab[2][0]==vez*-1&&tab[2][2]==vez*-1)||
                (tab[0][1]==vez*-1&&tab[1][1]==vez*-1)))
        jogada=7;
    if(tab[2][2] == 0 && ((tab[2][0]==vez*-1&&tab[2][1]==vez*-1)||
                (tab[0][2]==vez*-1&&tab[1][2]==vez*-1)||
                (tab[0][0]==vez*-1&&tab[1][1]==vez*-1)))
        jogada=8;
    if(tab[0][0] == 0 && ((tab[0][1]==vez && tab[0][2]==vez)||
                (tab[1][0]==vez &&tab[2][0]==vez)||
                (tab[1][1]==vez &&tab[2][2]==vez)))
        return 0;
    if(tab[0][1] == 0 && ((tab[0][0]==vez&&tab[0][2]==vez)||
                (tab[1][1]==vez&&tab[2][1]==vez)))
        return 1;
    if(tab[0][2] == 0 && ((tab[0][0]==vez&&tab[0][1]==vez)||
                (tab[1][2]==vez&&tab[2][2]==vez)||
                (tab[1][1]==vez&&tab[2][0]==vez)))
        return 2;
    if(tab[1][0] == 0 && ((tab[1][1]==vez&&tab[1][2]==vez)||
                (tab[0][0]==vez&&tab[2][0]==vez)))
        return 3;
    if(tab[1][1] == 0 && ((tab[1][0]==vez&&tab[1][2]==vez)||
                (tab[0][1]==vez&&tab[2][1]==vez)||
                (tab[0][0]==vez&&tab[2][2]==vez)||
                (tab[0][2]==vez&&tab[2][0]==vez)))
        return 4;
    if(tab[1][2] == 0 && ((tab[1][0]==vez&&tab[1][1]==vez)||
                (tab[0][2]==vez&&tab[2][2]==vez)))
        return 5;
    if(tab[2][0] == 0 && ((tab[0][0]==vez&&tab[1][0]==vez)||
                (tab[2][1]==vez&&tab[2][2]==vez)||
                (tab[0][2]==vez&&tab[1][1]==vez)))
        return 6;
    if(tab[2][1] == 0 && ((tab[2][0]==vez&&tab[2][2]==vez)||
                (tab[0][1]==vez&&tab[1][1]==vez)))
        return 7;
    if(tab[2][2] == 0 && ((tab[2][0]==vez&&tab[2][1]==vez)||
                (tab[0][2]==vez&&tab[1][2]==vez)||
                (tab[0][0]==vez&&tab[1][1]==vez)))
        return 8;

    if(jogada!=9)
        return jogada;
    srand(time(NULL));
    int r = rand()%5; //sorteia uma das 4 diagonais
    int vetorDiagonais[5]={0,2,4,6,8};//vetor com a posição das diagonais e do centro
    int cont=1;
    while(verificaJogadaValida(tab, vetorDiagonais[r])==0){ //caso a posição ja tenha sido escolhida, vai decrementando ate achar uma posicao
        r--;
        cont++;
        if(r==-1) //caso extrapole a primeira posição, vai pra ultima pra começar a busca
            r=4;
        if(cont>=5)// se ele tentou jogar nas diagonais e no centro e não funcionou, joga aleatorio
            return nivelfacil(tab, vez);
    }


}

int verificarJogo(int tab[3][3])
{

    int i,j,status=3;

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(tab[i][j]==0)
            {
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




    // retorna 0 caso o jogo não tenha terminado
    // retorna 1 caso o jogo tenha terminado e o jogador 1 ganhou
    // retorna 2 caso o jogo tenha terminado e o jogador 2 ganhou
    // retorna 3 caso o jogo terminou e deu velha

    return status;
}

int verificaJogadaValida(int tab[3][3], int pos){
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

void imprimeTabuleiro(int tab[3][3]){
    int i,j;

    printf("\n\n");

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(tab[i][j]==1)
            {
                printf("X");
            }
            else if(tab[i][j]==-1) 
            {
                printf("O");
            }
            else
            {
                printf(" ");
            }

            if(j==0 || j==1)
            {
                printf("%lc",WVV);
            }
            else if(j==2)
            {
                printf("\n");
            }
        }
        if(i==0 || i==1)
            printf("%lc%lc%lc%lc%lc\n", WHH, WVH, WHH, WVH, WHH);


    }

    printf("\n\n");

}

void jogadaHumano(int tab[3][3], int jogador)
{

    int jogador_Hum =1;

    if((modo_jogo==3 && comeca =='c')|| jogador==-1)
        jogador_Hum = 2;
    else
        jogador_Hum = 1;

    do
    {
        printf("Jogador %d: Digite uma posicao para jogar de 0 a 8 que nao esteja ocupada:\n", jogador_Hum);
        scanf("%d", &jogada);
    }
    while(verificaJogadaValida(tab, jogada) == 0);

    fazerJogada(tab,jogada);

}

void jogadaPC(int dificuldade, int tab[3][3], int vez)
{

    switch(dificuldade)
    {
        case 1:jogada= nivelfacil(tab, vez);
               break;
        case 2:jogada= nivelmedio(tab, vez);
               break;
        case 3:jogada= niveldificil(tab, vez);
               break;
    }


    fazerJogada(tab,jogada);
}

int main()
{
    setlocale(LC_ALL, "");
    do
    {
        int tabuleiro[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
        g_vez=1;

        do
        {
            printf("Digite o modo de jogo:\n1- Humano contra Humano\n2- Computador contra Computador\n3- Humano contra Computador\n");
            scanf("%d", &modo_jogo);
            printf("\n\n");
        }
        while(modo_jogo<1 && modo_jogo>3);

        if(modo_jogo ==3)
        {

            do
            {
                printf("Quem comeca:\nh- Humano\nc- computador\n");
                fflush(stdin)||__fpurge(stdin);//limpar o buffer da ultima escolha
                comeca=getchar();
                printf("\n\n");
            }
            while(comeca!='c' && comeca!='h');

        }

        if(modo_jogo ==2 || modo_jogo ==3)
        {

            do
            {
                printf("Digite a dificuldade:\n1-facil\n2-medio\n3-dificil\n");
                scanf("%d", &dificuldade);
                printf("\n\n");
            }
            while(dificuldade<1 && dificuldade>3);

        }

        while(1)
        {

            imprimeTabuleiro(tabuleiro);

            if(verificarJogo(tabuleiro) != 0)
                break;

            if(modo_jogo == 1 ||
                    (comeca == 'h' && g_vez == 1 && modo_jogo==3) ||
                    (comeca == 'c' && g_vez == -1 && modo_jogo==3))
                jogadaHumano(tabuleiro,g_vez);
            else
                jogadaPC(dificuldade, tabuleiro,g_vez);

        }

        switch(verificarJogo(tabuleiro))
        {
            case 1: printf("Jogador 1 ganhou\n");break;
            case 2: printf("Jogador 2 ganhou\n");break;
            case 3: printf("Deu velha\n");break;
        }


        do
        {
            printf("Deseja jogar novamente:\ns- sim\nn- nao\n");
            fflush(stdin)||__fpurge(stdin);//limpar o buffer da ultima escolha
            jogarNovamente=getchar();
        }
        while(jogarNovamente!='s' && jogarNovamente!='n');


    }
    while(jogarNovamente=='s');

    return 0;
}

