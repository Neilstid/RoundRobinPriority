# Usage:
# make        # compile all binary
CC = gcc
all:generate	execute

generate:	
	@echo "Compiling..."
	${CC} -w -o projetV15 projetV15.c 1AccesMemoire.c 2GestionDesSignaux.c 6VarAdmin.c 7Processus.c 8TableCpu.c 9GestionDesArg.c 10Menu.c 11Queue.c 12GestionDesThreads.c 13ElectionProcessus.c 14FinPrgrm.c  -pthread
	@echo "\n"

execute:
	@echo "Executing..."
	./projetV15
	
