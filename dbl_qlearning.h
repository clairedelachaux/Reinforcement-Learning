#ifndef DQLEARNING_H
#define DQLEARNING_H
#include <stdio.h>
#include <stdlib.h>
#include "mazeEnv.h"
#include "functions.h"



float** Q1;
float** Q2;

void initialize_Q1_Q2();

int dql_eps_greedy();

int dql_max_a(int state, float**Q);

int dql_next_step(envOutput s);


#endif