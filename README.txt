==================================
PCS2056 - Compilador
==================================



Como compilar o projeto
--------------------------------------

Utilizando o ambiente *nix (Mac OS X com XCode instalado ou Linux), entre na raiz do projeto e:

	$ mkdir bin #caso o diretorio não exista	
	$ make
	$ bin/compiler <arquivo de entrada>

Testes
-----------

Preparamos três casos de testes (PCS2056/testes/):
	- teste_0.txt: programa completo, reconhecido pelo compilador
	- texte_1.txt: programa com erro
	- teste_2.txt: programa com erro
Para roda-los com nosso compilador:
	$ bin/compiler testes/teste_0.txt


Modo Debug
-----------

Para ativar o modo debug, pode-se apenas incluir a macro no arquivo main:

	#define DEBUG

E o analisador sintático irá imprimir em tela mensagens na tela sobre a análise do programa.