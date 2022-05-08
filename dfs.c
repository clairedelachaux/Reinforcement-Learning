#include "mazeEnv.h" 
#include"dbl_qlearning.h"
#include "qlearning.h"
#include <time.h>


int dfs(int row, int col){
    int* current = &visited[row][col];

    if(*current == goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        if (dfs(row, col-1)){
            *current = crumb;
            return 1;
        } else if (dfs(row+1, col)){
            *current = crumb;
            return 1;
        }  else if (dfs(row, col+1)){
            *current = crumb;
            return 1;
        }  else if (dfs(row-1, col)){
            *current = crumb;
            return 1;
        }

    }

    return 0;
}

void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] ='.';
              }
          }
     }
     maze[start_row][start_col]= 's';
}



int q_learning(){
    //initialisation de Q, s et a
    initializeQ();
    envOutput s = {start_col, start_row, 0, 0};
    for(int i = 0; i<200; i++){
        state_col = start_col;
        state_row = start_row;
        s.new_row = start_row;
        s.new_col = start_col;
        s.done = 0;
        s.reward = 0;
        int k=0;
        int done = 0;
        while(!done && k<500){
            done = ql_next_step(s);
            k++;
        }
        printf("%d %d\n", k, i); 
    }
    return 0;
}

int dbl_q_learning(){
    //initialisation de Q, s et a
    initialize_Q1_Q2();
    envOutput s = {start_col, start_row, 0, 0};
    for(int i = 0; i<200; i++){
        state_col = start_col;
        state_row = start_row;
        s.new_row = start_row;
        s.new_col = start_col;
        s.done = 0;
        s.reward = 0;
        int k=0;
        int done = 0;
        while(!done && k<500){
            done = dql_next_step(s);
            k++;
            /*if(k%20==0){
                int st = s.new_row*cols +s.new_col;
                printf("%d (%f %f %f %f), (%f %f %f %f)\n", st, Q1[st][0], Q1[st][1], Q1[st][2], Q1[st][3], Q2[st][0], Q2[st][1], Q2[st][2], Q2[st][3]);
            }*/
        }
        printf("%d %d\n", k, i); 
    }
    return 0;
}

int main(){
    // on initialise la generateur de nombres aléatoires
    srand( time( NULL ) );
    maze_make("maze.txt");
    maze_render();
    q_learning();
    afficher_Q();
    //maze_render();
    return 0;
}

/* Makefile :

prog : dfs.o functions.o mazeEnv.o
gcc -o prog dfs.o functions.o mazeEnv.o
dfs.o : dfs.c
gcc -c -Wall -Werror -Wfatal-errors dfs.c
function.o function.c function.h
gcc -c -Wall -Werror -Wfatal-errors functions.c
mazeEnv.o : mazeEnv.c mazeEnv.h
gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c
clean
rm -f prog dfs.o functions.o mazeEnv.o //reinitialise le processus

Methode Gabriel

CC = gcc
CFlags = -W -Wall
INC = I include/
SRC = src/
exec = dfs.
all : $(EXEC)
$(SRC)%.o: $(SRC)%.c
$(CC) $(INC) -o %@ -c %.< $(CFLAGS)
dfs : $(SRC)dfs.o $(SRC)functions.o $(SRC)mazeEnv.o
_$(CC) $(INC) -o $(SRC) $@ $^ $(CFLAGS)
clean
rm -f $(SRC)*.o $(EXEC) //reinitialise le processus

*/





