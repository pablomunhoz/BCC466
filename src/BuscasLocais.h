#ifndef BUSCASLOCAIS_H
#define BUSCASLOCAIS_H

#include "Solucao.h"
#include "Instancia.h"
#include "Avaliador.h"

void movimentoTroca(Solucao& sol, int posI, int posJ);
float custoMovimentoTroca(Instancia&inst, Solucao& sol, int posI, int posJ);

Solucao BITroca(Instancia& inst, Solucao& sol);
Solucao BITrocaO1(Instancia& inst, Solucao& sol);

Solucao DescidaTrocaBI(Instancia& inst, Solucao& sol);
Solucao DescidaTrocaBIO1(Instancia& inst, Solucao& sol);

#endif