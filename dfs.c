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






