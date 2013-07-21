/* 
 * File:   sintatico.c
 * Authors: Rodrigo Acosta, Rodrigo Oliveira
 *
 * Created on 14 de Julho de 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"

char busca_reservada(char * palavra){
    
    char
        * reservadas[15];
    int
        i, quant = 11;
    
    for(i = 0; i<quant; i++)
        reservadas[i] = (char*) calloc(10, sizeof(char));
    
    reservadas[ 0] = "program";
    reservadas[ 1] = "var";
    reservadas[ 2] = "real";
    reservadas[ 3] = "boolean";
    reservadas[ 4] = "begin";
    reservadas[ 5] = "end";
    reservadas[ 6] = "read";
    reservadas[ 7] = "write";
    reservadas[ 8] = "if";
    reservadas[ 9] = "then";
    reservadas[10] = "else";
    
    for(i = 0; i < quant; i++){
        if(!strcmp(palavra, reservadas[i])){
            return 'v';
        }
    }
    return 'f';
}
