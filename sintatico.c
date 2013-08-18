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
#include "sintatico.h"

char * START(char * entrada){
    
    char * saida = (char*) calloc(200, sizeof(char));
    
    preLinha(1);
    preColuna(1);
    temqueler(1);
    
    if(testaToken(entrada, "[PROGRAM]")){
        
        if(testaToken(entrada, "[ID]")){
            
            if(testaToken(entrada, "[PTVIR]")){
                
                if(LISTADEC(entrada)){
                    
                    if(BLOCOM(entrada)){
                        return "Analise completada com sucesso.";
                    }
                }
            }
        }
    }
    if(testaToken(entrada, "!ERRO!")){
        sprintf(saida,"Erro lexico na linha %d, coluna %d.", getLinha(-1), getColuna(-1));
        return saida;
    }
    else{
        sprintf(saida,"Erro sintatico na linha %d, coluna %d.", preLinha(-1), preColuna(-1));
        return saida;
    }
}

int LISTADEC(char * entrada){
    
    if(testaToken(entrada, "[VAR]")){
        
        if(testaToken(entrada, "[ID]")){
            
            if(LISTAID(entrada)){
                
                if(testaToken(entrada, "[DOISPT]")){
                    
                    if(TIPO(entrada)){
                        
                        if(testaToken(entrada, "[PTVIR]")){
                            
                            if(DEC(entrada)){
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int DEC(char * entrada){
    
    if(testaToken(entrada, "[ID]")){
        
        if(LISTAID(entrada)){
            
            if(testaToken(entrada, "[DOISPT]")){
                
                if(TIPO(entrada)){
                    
                    if(testaToken(entrada, "[PTVIR]")){
                        
                        if(DEC(entrada)){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    else{
        return 1;
    }
    return 0;
}

int LISTAID(char * entrada){
    
    if(testaToken(entrada, "[VIRG]")){
        
        if(testaToken(entrada, "[ID]")){
            
            if(LISTAID(entrada)){
                return 1;
            }
        }
    }
    else{
        return 1;
    }
    return 0;
}

int TIPO(char * entrada){
    
    if(testaToken(entrada, "[REAL]"))
        return 1;

    if(testaToken(entrada, "[BOOLEAN]"))
        return 1;
    
    return 0;
}

int BLOCOM(char * entrada){
    
    if(testaToken(entrada, "[BEGIN]")){
        
        if(COM(entrada)){
            
            if(LISTACOM(entrada)){
                
                if(FIMCOM(entrada)){
                    
                    if(testaToken(entrada, "[END]")){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int COM(char * entrada){
    
    if(testaToken(entrada, "[READ]")){
        
        if(testaToken(entrada, "[APAR]")){
            
            if(testaToken(entrada, "[ID]")){
                
                if(LISTAID(entrada)){
                    
                    if(testaToken(entrada, "[FPAR]")){
                        return 1;
                    }
                }
            }
        }
    }
    else{
        if(testaToken(entrada, "[WRITE]")){
        
            if(testaToken(entrada, "[APAR]")){
                
                if(EXP(entrada)){
                    
                    if(OP(entrada)){
                        
                        if(LISTAEXP(entrada)){
                            
                            if(testaToken(entrada, "[FPAR]")){
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        else{
            if(testaToken(entrada, "[ID]")){
                
                if(testaToken(entrada, "[ATRIB]")){
                    
                    if(EXP(entrada)){
                    
                        if(OP(entrada)){
                            return 1;
                        }
                    }
                }
            }
            else{
                if(BLIF(entrada)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int LISTACOM(char * entrada){
    
    if(testaToken(entrada, "[PTVIR]")){
        
        if(COM(entrada)){
            
            if(LISTACOM(entrada)){
                return 1;
            }
        }
    }
    else{
        return 1;
    }
    return 0;
}

int FIMCOM(char * entrada){
    
    if(testaToken(entrada, "[PTVIR]"))
        return 1;
    
    return 1;
}

int BLIF(char * entrada){
    
    if(testaToken(entrada, "[IF]")){
        
        if(EXP(entrada)){
            
            if(OP(entrada)){
                
                if(testaToken(entrada, "[THEN]")){
                    
                    if(BLOCOM(entrada)){
                        
                        if(BLELSE(entrada)){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int BLELSE(char * entrada){
    
    if(testaToken(entrada, "[ELSE]")){
        
        if(BLOCOM(entrada)){
            return 1;
        }
    }
    else{
        return 1;
    }
    return 0;
}

int LISTAEXP(char * entrada){
    
    if(testaToken(entrada, "[VIRG]")){
        
        if(EXP(entrada)){
            
            if(OP(entrada)){
                
                if(LISTAEXP(entrada)){
                    return 1;
                }
            }
        }
    }
    else{
        return 1;
    }
    return 0;
}

int EXP(char * entrada){
    
    if(testaToken(entrada, "[NOT]"));
    
    if(UNI(entrada)){
        
        if(OP3(entrada)){
            
            if(OP2(entrada)){
                
                if(OP1(entrada)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int OP(char * entrada){
    
    if(testaToken(entrada, "[IGUAL]")){
        
        if(EXP(entrada)){
            return 1;
        }
    }
    else{
        if(testaToken(entrada, "[DIF]")){
            
            if(EXP(entrada)){
                return 1;
            }
        }
        else{
            if(testaToken(entrada, "[MAIOR]")){
                
                if(EXP(entrada)){
                    return 1;
                }
            }
            else{
                if(testaToken(entrada, "[MENOR]")){
                    
                    if(EXP(entrada)){
                        return 1;
                    }
                }
                else{
                    if(testaToken(entrada, "[MAIORIG]")){
                        
                        if(EXP(entrada)){
                            return 1;
                        }
                    }
                    else{
                        if(testaToken(entrada, "[MENORIG]")){
                            
                            if(EXP(entrada)){
                                return 1;
                            }
                        }
                        else{
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int OP1(char * entrada){
    
    if(testaToken(entrada, "[AND]")){
        
        if(EXP(entrada)){
            return 1;
        }
    }
    else{
        if(testaToken(entrada, "[OR]")){
            
            if(EXP(entrada)){
                return 1;
            }
        }
        else{
            return 1;
        }
    }
    return 0;
}

int OP2(char * entrada){
    
    if(testaToken(entrada, "[SOMA]")){
        
        if(UNI(entrada)){
            
            if(OP3(entrada)){
                
                if(OP2(entrada)){
                    return 1;
                }
            }
        }
    }
    else{
        if(testaToken(entrada, "[SUBT]")){
            
            if(UNI(entrada)){
                
                if(OP3(entrada)){
                    
                    if(OP2(entrada)){
                        return 1;
                    }
                }
            }
        }
        else{
            return 1;
        }
    }
    return 0;
}

int OP3(char * entrada){
    
    if(testaToken(entrada, "[MULT]")){
        
        if(UNI(entrada)){
            
            if(OP3(entrada)){
                return 1;
            }
        }
    }
    else{
        if(testaToken(entrada, "[DIV]")){
            
            if(UNI(entrada)){
                
                if(OP3(entrada)){
                    return 1;
                }
            }
        }
        else{
            if(testaToken(entrada, "[DIVINT]")){
                
                if(UNI(entrada)){
                    
                    if(OP3(entrada)){
                        return 1;
                    }
                }
            }
            else{
                return 1;
            }
        }
    }
    return 0;
}

int UNI(char * entrada){
    
    if(testaToken(entrada, "[APAR]")){
        
        if(EXP(entrada)){
            
            if(OP(entrada)){
                
                if(testaToken(entrada, "[FPAR]")){
                    return 1;
                }
            }
        }
    }
    else{
        if(testaToken(entrada, "[ID]")){
            return 1;
        }
        else{
            if(testaToken(entrada, "[CONST]")){
                return 1;
            }
            else{
                if(testaToken(entrada, "[BOOL]")){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int testaToken(char * entrada, char * tk){
    
    static char * temp_tk;
    
    if(temqueler(-1)){
        preLinha(getLinha(-1));
        preColuna(getColuna(-1));
        temp_tk = (char*) malloc(20*sizeof(char));
        temp_tk = token(entrada)[0];
    }
    
    if(!strcmp(temp_tk, tk)){
        temqueler(1);
        return 1;
    }
    else{
        temqueler(0);
        return 0;
    }
}

int temqueler(int in){
    
    static int out = 1;
    
    if(in >= 0)
        out = in;
    
    return out;
}

int preLinha(int in){
    
    static int out = 1;
    
    if(in >= 0)
        out = in;
    
    return out;
}

int preColuna(int in){
    
    static int out = 1;
    
    if(in >= 0)
        out = in;
    
    return out;
}
