prog : dfs.o functions.o mazeEnv.o qlearning.o dbl_qlearning.o
	gcc -o prog functions.o mazeEnv.o qlearning.o dfs.o dbl_qlearning.o

dfs.o : dfs.c
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

qlearning.o : qlearning.c qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c

dbl_qlearning.o : dbl_qlearning.c dbl_qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors dbl_qlearning.c

clean :
	rm -f prog dfs.o functions.o mazeEnv.o qlearning.o dbl_qlearning.o