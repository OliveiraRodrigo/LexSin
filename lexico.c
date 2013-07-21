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

char ** gera_token(char * entrada, int * index, char * fim, int * linha, int * coluna){
    
    char
        * temp,
        **saida,
        continua = 'v';
    int
        i = 0,
        estado = 0,
        e = *index;
    static char
        teve_token = 'f';
    static int
        c = 0;
    
    saida = (char**) malloc(2*sizeof(char));
    saida[0] = (char*) calloc(20, sizeof(char));
    saida[1] = (char*) calloc(200, sizeof(char));
    temp = (char*) calloc(2, sizeof(char));
    saida[0] = "!ERRO!";
    //saida[1] = " ";
    temp = " ";
    *fim = 'f';
    
    if(strlen(entrada) == 0){
        continua = 'f';
        *fim = 'v';
    }
    
    while(continua == 'v'){
        switch(estado){
            case 0:
                saida[0] = "!ERRO!";
                if(entrada[e] == 'd'){ //div
                    continua = 'v';
                    e++;
                    estado = 5;
                }
                else{
                if(entrada[e] == 'o'){ //or
                    continua = 'v';
                    e++;
                    estado = 26;
                }
                else{
                if(entrada[e] == 'a'){ //and
                    continua = 'v';
                    e++;
                    estado = 23;
                }
                else{
                if(entrada[e] == 'n'){ //not
                    continua = 'v';
                    e++;
                    estado = 20;
                }
                else{
                if(entrada[e] == 't'){ //true
                    continua = 'v';
                    e++;
                    estado = 32;
                }
                else{
                if(entrada[e] == 'f'){ //false
                    continua = 'v';
                    e++;
                    estado = 36;
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
                if((entrada[e] == ' ') || (entrada[e] == 9)){ //9: TAB
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
                            saida[0] = "";
                        }
                    }
                    continua = 'f';
                    *fim = 'v';
                }}}}}}}}}}}}}}}}}}}}}
                }
                break;
            case 1:
                saida[0] = "[REAL]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "!ERRO!";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[REAL]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[DIVINT]";
                saida[1] = "";
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
                saida[0] = "[SOMA]";
                saida[1] = "";
                continua = 'f';
                break;
            case 9:
                saida[0] = "[SUBT]";
                saida[1] = "";
                continua = 'f';
                break;
            case 10:
                saida[0] = "[MULT]";
                saida[1] = "";
                continua = 'f';
                break;
            case 11:
                saida[0] = "[DIV]";
                saida[1] = "";
                continua = 'f';
                break;
            case 12:
                saida[0] = "[MAIOR]";
                saida[1] = "";
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
                saida[0] = "[MAIOR-IGUAL]";
                saida[1] = "";
                continua = 'f';
                break;
            case 14:
                saida[0] = "[IGUAL]";
                saida[1] = "";
                continua = 'f';
                break;
            case 15:
                saida[0] = "[MENOR]";
                saida[1] = "";
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
                saida[0] = "[MENOR-IGUAL]";
                saida[1] = "";
                continua = 'f';
                break;
            case 17:
                saida[0] = "[DIF]";
                saida[1] = "";
                continua = 'f';
                break;
            case 18:
                saida[0] = "[APAR]";
                saida[1] = "";
                continua = 'f';
                break;
            case 19:
                saida[0] = "[FPAR]";
                saida[1] = "";
                continua = 'f';
                break;
            case 20:
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[NOT]";
                saida[1] = "";
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[AND]";
                saida[1] = "";
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
                saida[0] = "[ID]";
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
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
                saida[0] = "[OR]";
                saida[1] = "";
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
                saida[0] = "[TIPO]";
                saida[1] = "";
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
                saida[0] = "[ATRIB]";
                saida[1] = "";
                continua = 'f';
                break;
            case 30:
                saida[0] = "[VIRG]";
                saida[1] = "";
                continua = 'f';
                break;
            case 31:
                saida[0] = "[PTVIR]";
                saida[1] = "";
                continua = 'f';
                break;
            case 32:
                saida[0] = "[ID]"; //true
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 'r'){
                    continua = 'v';
                    e++;
                    estado = 33;
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
            case 33:
                saida[0] = "[ID]"; //true
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 'u'){
                    continua = 'v';
                    e++;
                    estado = 34;
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
            case 34:
                saida[0] = "[ID]"; //true
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 'e'){
                    continua = 'v';
                    e++;
                    estado = 35;
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
            case 35:
                saida[0] = "[BOOL]";
                saida[1] = "true";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
                break;
            case 36:
                saida[0] = "[ID]"; //false
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 'a'){
                    continua = 'v';
                    e++;
                    estado = 37;
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
            case 37:
                saida[0] = "[ID]"; //false
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 'l'){
                    continua = 'v';
                    e++;
                    estado = 38;
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
            case 38:
                saida[0] = "[ID]"; //false
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 's'){
                    continua = 'v';
                    e++;
                    estado = 39;
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
            case 39:
                saida[0] = "[ID]"; //false
                sprintf(temp, "%c", entrada[e-1]);
                strcat(saida[1], temp);
                if(entrada[e] == 'e'){
                    continua = 'v';
                    e++;
                    estado = 40;
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
            case 40:
                saida[0] = "[BOOL]";
                saida[1] = "false";
                if(busca_caracter(entrada[e], 0, 62) == 'v'){ //a-z,A-Z,_,0-9
                    continua = 'v';
                    e++;
                    estado = 4;
                }
                else{
                    continua = 'f';
                }
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
        if(saida[0] == "!ERRO!"){
            *fim = 'e';
        }
        teve_token = 'f';
    }
    
    *index = e;
    return saida;
}

char * analise_lexica(char * entrada){
    
    char
        **recebe,
        * saida,
        * temp,
        * fim;
    int
        * index,
        * linha,
        * coluna;
    
    recebe = (char**) malloc(2*sizeof(char));
    recebe[0] = (char*) calloc(20, sizeof(char));
    recebe[1] = (char*) calloc(200, sizeof(char));
    recebe[0] = " ";
    
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
        recebe = gera_token(entrada, index, fim, linha, coluna);
        strcat(saida, recebe[0]);
        strcat(saida, recebe[1]);
    }
    
    if(*fim == 'v'){
        strcat(saida, "\n\nAnalise lexica completada com sucesso.\n");
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
