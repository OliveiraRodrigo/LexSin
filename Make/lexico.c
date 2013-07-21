/* 
 * File:   lexico.c
 * Authors: Rodrigo Acosta, Rodrigo Oliveira
 *
 * Created on 28 de Junho de 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"

int conta_caracteres(FILE *arquivo){
    
    char
        c;
    int
        num_caracteres = 0;
    
    while((c = getc(arquivo)) != EOF){
        //printf("%d ", c);
        if(c != '\n'){  // O '\n' conta 2 caracteres (13 10).
            num_caracteres++;
        }
    }
    rewind(arquivo);
    return num_caracteres;
}

int conta_linhas(FILE *arquivo){
    
    char
        c;
    int
        num_linhas = 1; // Se tiver ao menos 1 caracter, ja tem uma linha.
    
    /* So retorna 0 se o arquivo esta vazio. */
    if((c = getc(arquivo)) == EOF){
        return 0;
    }
    else {
        rewind(arquivo);
        while((c = getc(arquivo)) != EOF){
            if(c == '\n'){
                num_linhas++;
            }
        }
    }
    rewind(arquivo);
    return num_linhas;
}

void remove_comentarios(char * entrada, char * saida){
    
    int
        i = 0,
        j = 0,
        tamanho;
    
    tamanho = strlen(entrada);
    
    while(i < tamanho){
        if(entrada[i] == '{'){
            i++;
            while(entrada[i] != '}'){
                if(i < tamanho){
                    i++;
                }
                else
                    break;
            }
            i++;
        }
        else{
            if(i + 1 < tamanho){
            if((entrada[i] == '/') && (entrada[i+1] == '/')){
                i = i + 2;
                while((entrada[i]<10) || (entrada[i]>13)){
                    if(i < tamanho){
                        i++;
                    }
                    else
                        break;
                }
            }
            }
        }
        if(i < tamanho){
            saida[j] = entrada[i];
            i++;
            j++;
        }
    }
    saida[j] = '\0';
}

void limpa_comentarios(char * entrada, char * saida){
    
    int
        i = 0,
        tamanho;
    
    tamanho = strlen(entrada);
    
    while(i < tamanho){
        if(entrada[i] == '{'){
            saida[i] = ' ';
            i++;
            while(entrada[i] != '}'){
                if(i < tamanho){
                    if((entrada[i]>9) && (entrada[i]<14))
                        //ENTER//
                        saida[i] = entrada[i];
                    else
                        saida[i] = ' ';
                    i++;
                }
                else
                    break;
            }
            if(i < tamanho){
                saida[i] = ' ';
                i++;
            }
        }
        else{
            if(i + 1 < tamanho){
                if((entrada[i] == '/') && (entrada[i+1] == '/')){
                    saida[i] = ' ';
                    saida[i+1] = ' ';
                    i = i + 2;
                    while((entrada[i]<10) || (entrada[i]>13)){
                        //Nao eh ENTER//
                        if(i < tamanho){
                            saida[i] = ' ';
                            i++;
                        }
                        else
                            break;
                    }
                }
            }
        }
        if(i < tamanho){
            saida[i] = entrada[i];
            i++;
        }
    }
    saida[i] = '\0';
}

char busca_caracter(char caracter, int ini, int fim){
    
    char
        * vocabulario;
    
    vocabulario = (char*) calloc(100, sizeof(char));

    vocabulario = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789.+-*/<>():=,;#";
    vocabulario[77] = '\0';
    
    for(ini; ini <= fim; ini++){
        if(caracter == vocabulario[ini]){
            return 'v';
        }
    }
    return 'f';
}

char * gera_token(char * entrada, int * index, char * fim, int * linha, int * coluna){
    
    char
        * saida,
        //* temp,
          continua = 'v';
    int
        estado = 0,
        e = *index;
    static char
        teve_token = 'f';
    
    saida = (char*) calloc(1000, sizeof(char));
    saida = "!ERRO!";
    //temp  = (char*) calloc(1000, sizeof(char));
    //temp  = " " ;
    *fim = 'f';
    
    if(strlen(entrada) == 0){
        continua = 'f';
        *fim = 'v';
    }
    
    while(continua == 'v'){
        switch(estado){
            case 0:
                saida = "!ERRO!";
                if(entrada[e] == 'd'){
                    continua = 'v';
                    e++;
                    estado = 5;
                }
                else{
                if(entrada[e] == 'o'){
                    continua = 'v';
                    e++;
                    estado = 26;
                }
                else{
                if(entrada[e] == 'a'){
                    continua = 'v';
                    e++;
                    estado = 23;
                }
                else{
                if(entrada[e] == 'n'){
                    continua = 'v';
                    e++;
                    estado = 20;
                }
                else{
                if(busca_caracter(entrada[e], 0, 52) == 'v'){ //a-z,A-Z,_
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                if(busca_caracter(entrada[e], 53, 62) == 'v'){ //0-9
                    continua = 'v';
                    e++;
                    estado = 1;
                }
                else{
                if(entrada[e] == '+'){
                    continua = 'v';
                    e++;
                    estado = 8;
                }
                else{
                if(entrada[e] == '-'){
                    continua = 'v';
                    e++;
                    estado = 9;
                }
                else{
                if(entrada[e] == '*'){
                    continua = 'v';
                    e++;
                    estado = 10;
                }
                else{
                if(entrada[e] == '/'){
                    continua = 'v';
                    e++;
                    estado = 11;
                }
                else{
                if(entrada[e] == '>'){
                    continua = 'v';
                    e++;
                    estado = 12;
                }
                else{
                if(entrada[e] == '='){
                    continua = 'v';
                    e++;
                    estado = 14;
                }
                else{
                if(entrada[e] == '<'){
                    continua = 'v';
                    e++;
                    estado = 15;
                }
                else{
                if(entrada[e] == '('){
                    continua = 'v';
                    e++;
                    estado = 18;
                }
                else{
                if(entrada[e] == ')'){
                    continua = 'v';
                    e++;
                    estado = 19;
                }
                else{
                if(entrada[e] == ':'){
                    continua = 'v';
                    e++;
                    estado = 28;
                }
                else{
                if(entrada[e] == ','){
                    continua = 'v';
                    e++;
                    estado = 30;
                }
                else{
                if(entrada[e] == ';'){
                    continua = 'v';
                    e++;
                    estado = 31;
                }
                else{
                if((entrada[e] == ' ') || (entrada[e] == 9)){//9: TAB
                    continua = 'v';
                    e++;
                    estado = 0;
                }
                else{
                if((entrada[e]>9) && (entrada[e]<14)){
                    //ENTER//
                    //Em ANSI eh 13 depois 10
                    if(entrada[e] == 13){
                        e = e + 1;
                    }
                    if(entrada[e] == 10){
                        e = e + 1;
                    }
                    if(entrada[e] == 11 || entrada[e] == 12){
                        e = e + 1;
                    }
                    continua = 'v';
                    estado = 0;
                    *coluna = 0;
                    *linha = *linha + 1;
                }
                else{
                    if(e >= strlen(entrada)){
                        if(teve_token == 'v'){
                            saida = "";
                        }
                    }
                    continua = 'f';
                    *fim = 'v';
                }}}}}}}}}}}}}}}}}}}
                }
                break;
            case 1:
                saida = "[REAL]";
                if(busca_caracter(entrada[e], 53, 62) == 'v'){ //0-9
                    continua = 'v';
                    e++;
                    estado = 1;
                }
                else{
                    if(entrada[e] == '.'){
                        continua = 'v';
                        e++;
                        estado = 2;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 2:
                saida = "!ERRO!";
                if(busca_caracter(entrada[e], 53, 62) == 'v'){ //0-9
                    continua = 'v';
                    e++;
                    estado = 3;
                }
                else{
                    continua = 'f';
                    *fim = 'v';
                }
                break;
            case 3:
                saida = "[REAL]";
                if(busca_caracter(entrada[e], 53, 62) == 'v'){ //0-9
                    continua = 'v';
                    e++;
                    estado = 3;
                }
                else{
                    continua = 'f';
                }
                break;
            case 4:
                saida = "[ID]";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
                break;
            case 5:
                saida = "[ID]";
                if(entrada[e] == 'i'){
                    continua = 'v';
                    e++;
                    estado = 6;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 6:
                saida = "[ID]";
                if(entrada[e] == 'v'){
                    continua = 'v';
                    e++;
                    estado = 7;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 7:
                saida = "[DIVINT]";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
                break;
            case 8:
                saida = "[SOMA]";
                continua = 'f';
                break;
            case 9:
                saida = "[SUBT]";
                continua = 'f';
                break;
            case 10:
                saida = "[MULT]";
                continua = 'f';
                break;
            case 11:
                saida = "[DIV]";
                continua = 'f';
                break;
            case 12:
                saida = "[MAIOR]";
                if(entrada[e] == '='){
                    continua = 'v';
                    e++;
                    estado = 13;
                }
                else{
                    continua = 'f';
                }
                break;
            case 13:
                saida = "[MAIOR-IGUAL]";
                continua = 'f';
                break;
            case 14:
                saida = "[IGUAL]";
                continua = 'f';
                break;
            case 15:
                saida = "[MENOR]";
                if(entrada[e] == '='){
                    continua = 'v';
                    e++;
                    estado = 16;
                }
                else{
                    if(entrada[e] == '>'){
                        continua = 'v';
                        e++;
                        estado = 17;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 16:
                saida = "[MENOR-IGUAL]";
                continua = 'f';
                break;
            case 17:
                saida = "[DIF]";
                continua = 'f';
                break;
            case 18:
                saida = "[APAR]";
                continua = 'f';
                break;
            case 19:
                saida = "[FPAR]";
                continua = 'f';
                break;
            case 20:
                saida = "[ID]";
                if(entrada[e] == 'o'){
                    continua = 'v';
                    e++;
                    estado = 21;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 21:
                saida = "[ID]";
                if(entrada[e] == 't'){
                    continua = 'v';
                    e++;
                    estado = 22;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 22:
                saida = "[NOT]";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
                break;
            case 23:
                saida = "[ID]";
                if(entrada[e] == 'n'){
                    continua = 'v';
                    e++;
                    estado = 24;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 24:
                saida = "[ID]";
                if(entrada[e] == 'd'){
                    continua = 'v';
                    e++;
                    estado = 25;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 25:
                saida = "[AND]";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
                break;
            case 26:
                saida = "[ID]";
                if(entrada[e] == 'r'){
                    continua = 'v';
                    e++;
                    estado = 27;
                }
                else{
                    if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                        continua = 'v';
                        e++;
                        estado = 4;
                    }
                    else{
                        continua = 'f';
                    }
                }
                break;
            case 27:
                saida = "[OR]";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
                break;
            case 28:
                saida = "[TIPO]";
                if(entrada[e] == '='){
                    continua = 'v';
                    e++;
                    estado = 29;
                }
                else{
                    continua = 'f';
                }
                break;
            case 29:
                saida = "[ATRIB]";
                continua = 'f';
                break;
            case 30:
                saida = "[VIRG]";
                continua = 'f';
                break;
            case 31:
                saida = "[PTVIR]";
                continua = 'f';
                break;
        }
        
        if(continua == 'v'){
            *coluna = *coluna + 1;
        }
        
        if((estado != 0)&&(estado != 2)){
        /* 0 e 2 sao os estado NAO-FINAIS. */
            teve_token = 'v';
        }
        
        if(e >= strlen(entrada)){
            *fim = 'v';
        }
    }
    
    if(*fim == 'v'){
        if(saida == "!ERRO!"){
            *fim = 'e';
        }
        teve_token = 'f';
    }
    
    *index = e;
    return saida;
}

char * codifica_expressao(char * entrada){
    
    char
        * saida,
        * temp,
        * fim;
    int
        * index,
        * linha,
        * coluna;
    
    saida  = (char*) calloc(1000, sizeof(char));
    temp   = (char*) calloc(1000, sizeof(char));
    fim    = (char*) calloc(   1, sizeof(char));
    index  =  (int*) calloc(   1, sizeof(int));
    linha  =  (int*) calloc(   1, sizeof(int));
    coluna =  (int*) calloc(   1, sizeof(int));
    
    *fim = 'f';
    *index = 0;
    *linha = 1;
    *coluna = 1;
    
    while(*fim == 'f'){
        /* Vai concatenando os tokens */
        strcat(saida, gera_token(entrada, index, fim, linha, coluna));
    }
    
    if(*fim == 'v'){
        strcat(saida, "\n\nAnalise completada com sucesso.\n");
    }
    else{ // *fim == 'e'
        if(strlen(entrada) > 0){
            sprintf(temp, "\n\n[Erro lexico na linha %d, coluna %d]\n", *linha, *coluna);
            strcat(saida, temp);
        }
        else{
            strcat(saida, "\n\n[Erro sintatico na linha 1, coluna 1]\n");
        }
    }
    
    free(fim);
    free(index);
    
    return saida;
}
