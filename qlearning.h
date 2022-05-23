#ifndef QLEARNING
#define QLEARNING

#include <stdio.h>
#include <stdlib.h>
#include "mazeEnv.h"
#include "functions.h"

float** Q;

void initializeQ();

int eps_greedy(int s);

void afficher_Q();

int max_a(envOutput s, int a);

int ql_next_step(envOutput s);


#endif
