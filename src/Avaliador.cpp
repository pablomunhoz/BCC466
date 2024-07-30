#include "Avaliador.h"

float avalia(Instancia& inst, Solucao& sol)
{
    float fo = 0;
    for(int i = 0 ; i < (inst.n - 1); i++)
    {
        fo+= inst.distancia[sol.at(i)][sol.at(i+1)];
    }
    // adicionando o retorno à cidade inicial ao valor da FO
    fo+= inst.distancia[sol.at(inst.n-1)][sol.at(0)];
    
    return fo; 
}