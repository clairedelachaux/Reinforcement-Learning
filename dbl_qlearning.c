#include "dbl_qlearning.h"
#define eps 0.1
#define gamma 1
#define alpha 0.95
#define true 1
#define false 0

void initialize_Q1_Q2()
{
    Q1 = malloc(cols*rows * sizeof(float*)); //nombre d'etat = nb colonnes * nb lignes
     for(int i=0; i<rows*cols; i++) {
         Q1[i] = malloc(number_actions * sizeof(float));
         for(int j=0; j< number_actions; j++){
             Q1[i][j]=0;
         }
     }
     Q2 = malloc(cols*rows * sizeof(float*)); //nombre d'etat = nb colonnes * nb lignes
     for(int i=0; i<rows*cols; i++) {
         Q2[i] = malloc(number_actions * sizeof(float));
         for(int j=0; j< number_actions; j++){
             Q2[i][j]=0;
         }
     }
}

int dql_eps_greedy(){
    int a = up;
    float nb_alea = (1.*rand())/RAND_MAX;
    if (nb_alea<eps){
        a = rand()%4;
        //printf(" greedy ");
    }
    else{
        int s = state_row*cols +state_col;
        for (int a_i=1; a_i< number_actions; a_i++){
            if (Q1[s][a_i]+Q2[s][a_i]> Q1[s][a]+Q2[s][a]){
                a = a_i;
            }
            if(Q1[s][a_i]+Q2[s][a_i]==Q1[s][a]+Q2[s][a]){
                if (1.*rand()/RAND_MAX<0.5){
                    a = a_i;
                }
            }
        }
    }
    return a;
}

int dql_max_a(int state, float**Q){
    int max = Q[state][0];
    int i_max = 0;
    for (int k=1; k<4; k++){
        if (Q[state][k]> max){
            max = Q[state][k];
            i_max= k;
        }
        if(Q[state][k]== max){
            if (rand()/RAND_MAX<0.5){
                max = Q[state][k];
                i_max= k;
            }
        }
    }
    return i_max;
}

int dql_next_step(envOutput s){
    int a = dql_eps_greedy();
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
    int s_state = cols*state_row+state_col;
    int s_prime = cols*s.new_row+s.new_col; 
    if(1.*rand()/RAND_MAX<0.5){
        Q1[s_state][a] += alpha*(s.reward + gamma*(Q2[s_prime][dql_max_a(s_prime, Q1)] - Q1[s_state][a]));
    }
    else{
        Q2[s_state][a] += alpha*(s.reward + gamma*(Q1[s_prime][dql_max_a(s_prime, Q2)] - Q2[s_state][a]));
    }
    state_col = s.new_col;
    state_row = s.new_row;
    return s.done;
}