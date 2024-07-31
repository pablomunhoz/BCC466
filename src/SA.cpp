#include "SA.h"


Solucao SA(Instancia& inst, Solucao& sol, float alpha, int SAmax, float T0, float TF)
{
    //atualizando a melhor solução até então
    Solucao melhorSol = sol;
    float melhorFO = avalia(inst, melhorSol);
    float fo = melhorFO;

    float T = T0;
    int iterT = 0;

    cout<< "SA T0: "<< T0 << " FO: "<<fo << endl;

    while(T > TF)
    {
        while(iterT < SAmax)
        {
            iterT++;
            //gerando um vizinho aletório de troca
            int i,j;
            i = rand()%inst.n;
            do
            {
                j = rand()%inst.n;
            } while (j == i);
            //calculando delta => custo do movimento
            float delta = custoMovimentoTroca(inst,sol,i,j);
            //se houve melhora em relação à solução corrente
            if(delta < 0)
            {
                //movento a solução atual para a solução vizinha
                movimentoTroca(sol,i,j);
                fo += delta;
                //se houve melhora em relação à melhor solução do método
                if(fo < melhorFO)
                {
                    melhorSol = sol;
                    melhorFO = fo;
                    cout<< "SA Melhorou T: "<< T << " FO: " << melhorFO << endl;
                }
            }
            else
            {
                //sorteando um valor entre 0 e 1
                float x = rand() / (float)RAND_MAX;
                if(x < exp(-delta/T))
                {
                    //movo a solução corrente para a solução vizinha
                    movimentoTroca(sol,i,j);
                    fo+=delta;
                }
            }
            
        }//fim while SAmax
        T = alpha * T;
        iterT = 0;
    }//fim while TF

    return melhorSol;
}


float SA_temperaturaInicial(Instancia& inst, Solucao&sol, int SAmax, float beta, float gamma, float T0)
{
    
    float T = T0;
    bool continua = true;
    int iterT,aceitos;

    while(continua)
    {
        aceitos = 0;
        iterT = 0;
        while(iterT < SAmax)
        {
            iterT++;
            //gerando um vizinho aletório de troca
            int i,j;
            i = rand()%inst.n;
            do
            {
                j = rand()%inst.n;
            } while (j == i);
            //calculando delta => custo do movimento
            float delta = custoMovimentoTroca(inst,sol,i,j);
            //se houve melhora em relação à solução corrente
            if(delta < 0)
            {
                aceitos++;
            }
            else
            {
                //sorteando um valor entre 0 e 1
                float x = rand() / (float)RAND_MAX;
                if(x < exp(-delta/T))
                {
                    aceitos++;
                }
            }
            
        }//fim while SAmax
        if(aceitos >=  gamma*SAmax)
        {
            continua = false;
        }
        else
        {
            T*=beta;
        }
    }//fim while TF

    return T;    
}