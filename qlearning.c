#include "qlearning.h"
#define eps 0.1
#define gamma 0.9
#define alpha 0.99 
#define true 1
#define false 0

void initializeQ()
{
    Q = malloc(cols*rows * sizeof(float*)); //nombre d'etat = nb colonnes * nb lignes
     for(int i=0; i<rows*cols; i++) {
         Q[i] = malloc(number_actions * sizeof(float));
         for(int j=0; j< number_actions; j++){
             Q[i][j]=0;
         }
     }
     /*for (int j=0; j<cols; j++) {
         Q[j][up]=-RAND_MAX;
         Q[rows*cols-j-1][down]=-RAND_MAX;

     }
     for (int j=0; j<rows; j++) {
         Q[j*cols][left]=-RAND_MAX;
         Q[(j+1)*cols-1][right]=-RAND_MAX;
     }*/
}

void afficher_Q(){
    for(int i=0; i<rows*cols; i++){
        printf("%d, %d ", i/cols, i%cols);
        for (int j=0; j<number_actions; j++){
            printf("%f ", Q[i][j]);
        }
        printf("\n");
    }

}

int eps_greedy(int s){
    int a = up;
    float nb_alea = (1.*rand())/RAND_MAX;
    if (nb_alea<eps){
        a = rand()%4;
        //printf(" greedy ");
    }
    else{;
        for (int a_i=1; a_i< number_actions; a_i++){
            if (Q[s][a_i]> Q[s][a]){
                a = a_i;
            }
            if(Q[s][a_i] == Q[s][a]){
                if (1.*rand()/RAND_MAX<0.5){
                    a = a_i;
                }
            }
        }
    }
    return a;
}

int max_a(envOutput s, int a){
    int state_s = cols*state_row +state_col;
    int new_s = cols*s.new_row + s.new_col;
    int delta_up = Q[new_s][up] - Q[state_s][a];
    int delta_down = Q[new_s][down] - Q[state_s][a];
    int delta_left = Q[new_s][left] - Q[state_s][a];
    int delta_right = Q[new_s][right] - Q[state_s][a];
    return max(max(delta_up, delta_down), max(delta_left, delta_right));
}

int ql_next_step(envOutput s){
    int a = eps_greedy(state_row*cols+state_col);
    switch (a)
    {
    case up:
        s.new_row = state_row-1;
        s.new_col = state_col;
        break;
    
    case down:
        s.new_row = state_row+1;
        s.new_col = state_col;
        break;

    case left:
        s.new_col = state_col-1;
        s.new_row = state_row;
        break;
    
    case right:
        s.new_col = state_col+1;
        s.new_row = state_row;
        break;
    
    default:
        break;
    }
    if (s.new_col == goal_col && s.new_row == goal_row){
        s.reward = 1000;
        s.done = true;
    }
    else if(maze[s.new_row][s.new_col] == '+'){
        s.reward = -100;
        s.new_col = state_col;
        s.new_row = state_row;
    }
    else{
        s.reward = -1;
    }
    Q[cols*state_row+state_col][a] += alpha*(s.reward + gamma*max_a(s, a));
    state_col = s.new_col;
    state_row = s.new_row;
    return s.done;
}

int sarsa(envOutput s, int a){
    switch (a)
    {
    case up:
        s.new_row = state_row-1;
        s.new_col = state_col;
        break;
    
    case down:
        s.new_row = state_row+1;
        s.new_col = state_col;
        break;

    case left:
        s.new_col = state_col-1;
        s.new_row = state_row;
        break;

    case right:
        s.new_col = state_col+1;
        s.new_row = state_row;
        break;
    
    default:
        break;
    }
    if (s.new_col == goal_col && s.new_row == goal_row){
        s.reward = 1000;
        s.done = true;
        //printf("well done %d\n", s.done);
    }
    else if(maze[s.new_row][s.new_col] == '+'){
        //printf(" mur! %c %d %d ", maze[s.new_row][s.new_col-1], s.new_row, s.new_col);
        s.reward = -100;
        s.new_col = state_col;
        s.new_row = state_row;
    }
    else{
        s.reward = -1;
    }
    int st = cols*state_row+state_col;
    int st_prime = s.new_row*cols+s.new_col;
    int a_prime = eps_greedy(st_prime);
    Q[st][a] += alpha*(s.reward + gamma*(Q[st_prime][a_prime]-Q[st][a]));
    state_col = s.new_col;
    state_row = s.new_row;
    a = a_prime;
    return s.done;
}
