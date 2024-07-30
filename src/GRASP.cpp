#include "GRASP.h"

Solucao GRASP(Instancia& inst,int GRASPMax, float alpha)
{
    float melhorFO = FLT_MAX,fo;
    Solucao melhorSol;

    for(int iter = 0; iter < GRASPMax;iter++)
    {
        //constroi
        Solucao sol = VMP_GRASP(inst,alpha);
        //aplica busca local
        sol = DescidaTrocaBIO1(inst,sol);
        fo = avalia(inst,sol);
        if(fo < melhorFO)
        {
            melhorFO = fo;
            melhorSol = sol;
        }       
    }
    return melhorSol;
}