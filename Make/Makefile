
# Universidade Federal de Pelotas
# Ciencia da Computacao
# Linguagens Formais
# Analisador Lexico e Sintatico de um Subconjunto da Linguagem Pascal
# Rodrigo Acosta, Rodrigo Oliveira

#############################################################################

compila_help: compila help

compila: analisador.c lexico.c sintatico.c lexico.h sintatico.h

	@echo  ..............................................................
	@echo Making...

# Gera os objetos
	gcc -c analisador.c lexico.c sintatico.c

# Gera as bibliotecas estaticas 'lexico.a' e 'sintatico.a'
	ar rcs lexico.a lexico.o
	ar rcs sintatico.a sintatico.o

# Liga os objetos e gera o executavel utilizando as bibliotecas
	gcc -o lexsin analisador.o lexico.a sintatico.a

help:
	@echo  ..............................................................
	@echo   Para executar:
	@echo
	@echo   No Windows digite: lexsin [arq_1] [arq_2] ... [arq_n]
	@echo   Exemplo: lexsin prog.txt vazio.txt teste.txt
	@echo
	@echo   No Linux digite: ./lexsin [arq_1] [arq_2] ... [arq_n]
	@echo   Exemplo: ./lexsin entrada.txt vazio.txt teste.txt
	@echo  ..............................................................

clear:
	rm *.a *.o lexsin
