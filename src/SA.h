#ifndef SA_H
#define SA_H

#include<iostream>

#include "Solucao.h"
#include "Instancia.h"
#include "Avaliador.h"
#include "HeuristicasConstrutivas.h"
#include "BuscasLocais.h"

float SA_temperaturaInicial(Instancia& inst, Solucao&sol, int SAmax, float beta, float gamma, float T0);
Solucao SA(Instancia& inst,Solucao& sol, float alpha, int SAmax, float T0, float TF);



#endif