==================================
PCS2056 - Compilador
==================================



Como compilar o projeto
--------------------------------------

Utilizando o ambiente *nix (Mac OS X com XCode instalado ou Linux), entre na raiz do projeto e:
	
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
