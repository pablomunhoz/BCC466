#ifndef MULTISTART_H
#define MULTISTART_H

#include <float.h>

#include "Solucao.h"
#include "Instancia.h"
#include "BuscasLocais.h"
#include "HeuristicasConstrutivas.h"


Solucao MultiStart(Instancia& inst, int iterMax);

#endif