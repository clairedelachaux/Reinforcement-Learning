prog2 : main.o pacman.o env.o
	gcc -o prog2 main.o pacman.o env.o

main.o : main.c
	gcc -c -Wall -Werror -Wfatal-errors main.c

env.o : env.c env.h
	gcc -c -Wall -Werror -Wfatal-errors env.c

pacman.o : pacman.c pacman.h
	gcc -c -Wall -Werror -Wfatal-errors pacman.c


clean :
	rm -f prog2 main.o pacman.o env.o