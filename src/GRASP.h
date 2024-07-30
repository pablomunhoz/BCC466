#ifndef GRASP_H
#define GRASP_H

#include <float.h>

#include "Instancia.h"
#include "HeuristicasConstrutivas.h"
#include "Solucao.h"
#include "BuscasLocais.h"

Solucao GRASP(Instancia& inst,int GRASPMax, float alpha);

#endif