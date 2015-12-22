#include <stdio.h>
#include <stdlib.h>

int tabuleiro[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int modo_jogo, dificuldade;

int nivelfacil(int tab[3][3], int vez){
    return 0;
}
int nivelmedio(int tab[3][3], int vez){
    return 0;
}
int niveldificil(int tab[3][3], int vez){
    return 0;
}

int verificarJogo(int tab[3][3]){
    //retorna 0 caso o jogo não tenha terminado
    //retorna 1 caso o jogo tenha terminado e o jogador 1 ganhou
    //retorna 2 caso o jogo tenha terminado e o jogador 2 ganhou
    //retorna 3 caso o jogo terminou e deu velha
    return 0;
}

void imprimeTabuleiro(int tab[3][3]){
    //Imprimir formatado o tabuleiro
}



int main(){

    do{
        printf("Digite o modo de jogo\n1- Humano contra Humano\n2- Computador contra Computador\n3- Humano contra Computador:\n");
        scanf("%d", &modo_jogo);
    }while(modo_jogo<1 && modo_jogo>3);


    if(modo_jogo ==2 || modo_jogo ==3){

        do{
            printf("Digite a dificuldade\n1-facil\n2-medio\n3-dificil:\n");
            scanf("%d", &dificuldade);
        }while(dificuldade<1 && dificuldade>3);

    }
    while(verificarJogo(tabuleiro) == 0){

    }


    return 0;
}


