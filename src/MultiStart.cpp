#include "MultiStart.h"

Solucao MultiStart(Instancia& inst, int iterMax)
{
    //faça iterMax iterações sem melhora
    // construo uma solução
    // faça uma busca local
    // se é melhor que a melhor solução atual, atualizo, senão repito
    int iter = 1;
    Solucao melhorSol;
    float melhorFO = FLT_MAX,fo;
    while(iter <= iterMax)
    {   
        //criando a solução
        Solucao sol = Randomica(inst);
        //aplico a busca local
        sol = DescidaTrocaBIO1(inst,sol);
        //avalio a solucao
        fo = avalia(inst,sol);
        if(fo < melhorFO)
        {
            melhorSol = sol;
            melhorFO = fo;
            iter = 1;
        }
        else   
        {
            //conta mais uma iteração sem melhora
            iter++;
        }
        
    }

    return melhorSol;
}