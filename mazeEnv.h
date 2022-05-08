#ifndef MAZEENV_H
#define MAZEENV_H

#include <stdio.h>
#include <stdlib.h>

// un tableau, a colonne, s, ligne
// choisit action, prends plus grande valeur

//definition de variables globales
char** maze;
int** visited;// utilise par dfs pas besoin ici
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

//inutile?
enum terrain{// valeur des cases du tableau
    unknown,
    wall,
    known,
    goal,
    crumb
};

enum action{
     up,
     down,
     left,
     right,
     number_actions 
};
 
typedef enum action action ;

struct envOutput{//nouvel etat, le recompense et si on est arrive 
  int new_col;
  int new_row;
  int reward;
  int done;

};

typedef struct envOutput envOutput;

void alloc_maze();

void maze_make(char* );

void maze_render(); // affiche labyrinthe

void maze_reset();

envOutput maze_step(action a); // executer une action et avoir la recompense

action env_action_sample();// choisi une action

void alloc_visited();

void init_visited();

#endif /* MAZEENV_H */
