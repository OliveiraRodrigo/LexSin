/* 
 * File:   analisador.c
 * Authors: Rodrigo Acosta, Rodrigo Oliveira
 *
 * Created on 28 de Junho de 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

int main(int argc, char** argv) {
    
    int
        i,
        j,
        arg = 1,
        num_caracteres,
        num_linhas;
    char
        * string,
        * clean_string;
    FILE
        *arquivo;
    
/* Abre cada arquivo passado por parametro ou por entrada */
    if (argc < 2){ // Nao veio nenhum arquivo por paramentro.
        printf("\n== Dica do dia ===================================================\n"
               " \"Voce poderia ter passado o(s) arquivo(s) por linha de comando!\""
               "\n==================================================================\n"
               "Digite aqui o(s) arquivo(s) separado(s) por espaco:\n");
        
        /* Aloca espaco para 10 nomes com 50 caracteres cada */
        for(i = 1; i <= 10; i++){
            argv[i] = (char*) malloc(50*sizeof(char));
        }
        
        i = 1;
        j = 0;
        argv[i][j] = getchar();
        j++;
        while(argv[i][j-1] != '\n'){
            argv[i][j] = getchar();
            if(argv[i][j] == ' '){
                argv[i][j] = '\0'; // Descarta o ' '.
                j = 0;
                i++;
                argc++;
            }
            else{
                j++;
            }
        }
        argv[i][j-1] = '\0'; // Descarta o '\n'.
        argc++;
    }
    for(arg = 1; arg < argc; arg++){
    
/* Abre o arquivo para leitura */
        arquivo = fopen(argv[arg],"r");
        if(!arquivo){
            printf("\nTem certeza de que o arquivo %d se chama \"%s\"?\n"
                   "Eu acho que nao!\n"
                   "Ou nao e' um arquivo de texto valido.\n\n"
                   "Digite novamente o nome do arquivo %d: ", arg, argv[arg], arg);
            
            gets(argv[arg]);
            
            arquivo = fopen(argv[arg], "r");
            if(!arquivo){
                printf("\nAh... Continua dando erro nesse teu arquivo. Desisto!\n\n");
            }
        }
        if(arquivo){
/* Gera estatisticas do arquivo */
            num_linhas = conta_linhas(arquivo);
            num_caracteres = conta_caracteres(arquivo);
            
/* Dimensiona a string de acordo com o tamanho do arquivo */
            string       = (char*) malloc((num_caracteres+num_linhas)*sizeof(char));
            clean_string = (char*) malloc((num_caracteres+num_linhas)*sizeof(char));
            
/* Grava cada caracter na string */
            i = 0;
            while((string[i] = getc(arquivo)) != EOF){
                i++;
            }
            string[i] = '\0'; //Limpa a sujeira do final do arquivo.
            fclose(arquivo);
            
/* Limpa os comentarios da string */
            limpa_comentarios(string, clean_string);
            //limpa_espacos(clean_string, string);
            
/* Ao trabalho! */
            printf("\n== Arquivo %d ==========================\n", arg);
            
            printf("\nLinhas: %*d\n",
            printf("\nCaracteres: %d", num_caracteres)-9, num_linhas);
            /* Usando o segundo printf como argumento para o primeiro,
             * ja que o printf retorna o numero de caracteres impressos.
             * Isto e' so' para alinhar a direita os numeros. */
            /*
            printf("\nString %d:\n"
                   "_______________________________________\n"
                   "%s\n"
                   "_______________________________________\n", arg,
                   "string);*/
            printf("\nClean_String %d:\n"
                   "_______________________________________\n"
                   "%s\n"
                   "_______________________________________\n", arg,
                   clean_string);
            
            free(string);
            
            printf("\nPrograma %d:\n"
                   "%s\n"
                   "_______________________________________\n", arg,
                   analise_lexica(clean_string));
            
            printf("\n%s\n", START(clean_string));
            
            free(clean_string);
        }
    }
    
    return (EXIT_SUCCESS);
}
