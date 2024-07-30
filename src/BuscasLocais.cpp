#include "BuscasLocais.h"

void movimentoTroca(Solucao& sol, int posI, int posJ)
{

    int aux = sol.at(posI);
    sol.at(posI) = sol.at(posJ);
    sol.at(posJ) = aux;

}

float custoMovimentoTroca(Instancia&inst, Solucao& sol, int posI, int posJ)
{
    float custo = 0;
    int anteriorI, anteriorJ, posteriorI, posteriorJ;
    anteriorI = posI -1;
    anteriorJ = posJ -1;
    posteriorI = posI + 1;
    posteriorJ = posJ+1;
    if(anteriorI < 0)
        anteriorI = inst.n - 1;
    if(posteriorJ >= inst.n)
        posteriorJ = 0;

    if(anteriorJ == posI) // quando a troca é adjacente
    {
        custo = (inst.distancia[ sol.at(anteriorI) ][ sol.at(posJ)]+
                inst.distancia[sol.at(posJ)][sol.at(posI)] +
                inst.distancia[sol.at(posI)][sol.at(posteriorJ)])-
                (inst.distancia[ sol.at(anteriorI) ][ sol.at(posI)]+
                inst.distancia[sol.at(posI)][sol.at(posJ)] +
                inst.distancia[sol.at(posJ)][sol.at(posteriorJ)]);
    }   
    else
    {
        if( posteriorJ == posI) // quando a troca é nas pontas do vetor
        {
            custo = (inst.distancia[ sol.at(posJ) ][ sol.at(posteriorI)]+
                inst.distancia[sol.at(posJ)][sol.at(posI)] +
                inst.distancia[sol.at(anteriorJ)][sol.at(posI)])-
                (inst.distancia[ sol.at(posI) ][ sol.at(posteriorI)]+
                inst.distancia[sol.at(posI)][sol.at(posJ)] +
                inst.distancia[sol.at(anteriorJ)][sol.at(posJ)]);
        }
        else // outros casos
        {
            custo = (inst.distancia[ sol.at(anteriorI) ][ sol.at(posJ)] +
                inst.distancia[ sol.at(posJ)][sol.at(posteriorI)] +
                inst.distancia[ sol.at(anteriorJ)][ sol.at(posI)]+
                inst.distancia[sol.at(posI)][sol.at(posteriorJ)]) -
                (inst.distancia[ sol.at(anteriorI) ][ sol.at(posI)] +
                inst.distancia[ sol.at(posI)][sol.at(posteriorI)] +
                inst.distancia[ sol.at(anteriorJ)][ sol.at(posJ)]+
                inst.distancia[sol.at(posJ)][sol.at(posteriorJ)]);
        }

    }
    
    return custo;
}


Solucao BITroca(Instancia& inst, Solucao& sol)
{
    int melhorPosI = -1, melhorPosJ = -1;
    Solucao melhorSol = sol;
    float vizFO, melhorFO = avalia(inst, sol);

    for(int posI = 0; posI < inst.n-1; posI++)
    {
        for(int posJ = posI+1; posJ < inst.n; posJ++)
        {
            //aplicando o movimento de troca da posI e posJ
            movimentoTroca(sol, posI, posJ);

            vizFO = avalia(inst, sol);
            //printf("Pos i: %d Pos j: %d, fo: %.2f\n", posI, posJ, vizFO);

            if(vizFO < melhorFO)
            {
                melhorFO = vizFO;
                melhorPosI = posI;
                melhorPosJ = posJ;
            }

            //desfazendo o movimento de troca
            movimentoTroca(sol, posJ, posI);
        }
    }

    if(melhorPosI != -1) // houve vizinho melhor
    {
        //aplicando o melhor movimentos
        movimentoTroca(melhorSol, melhorPosI, melhorPosJ);
    }
    return melhorSol;

}

Solucao BITrocaO1(Instancia& inst, Solucao& sol)
{
    int melhorPosI = -1, melhorPosJ = -1;
    Solucao melhorSol = sol;    
    float vizCusto, melhorCusto = 0;

    for(int posI = 0; posI < inst.n-1; posI++)
    {
        for(int posJ = posI+1; posJ < inst.n; posJ++)
        {
            //calculando o custo do movimento
            vizCusto = custoMovimentoTroca(inst, sol, posI, posJ);
                        
            if(vizCusto < melhorCusto) // o melhor custo é o mais negativo (Minimização)
            {
                melhorCusto = vizCusto;
                melhorPosI = posI;
                melhorPosJ = posJ;
            }
        }
    }

        
    if(melhorPosI != -1) // houve vizinho melhor
    {
        //aplicando o melhor movimentos
        movimentoTroca(melhorSol, melhorPosI, melhorPosJ);
    }
    float fo = avalia(inst,melhorSol);

    return melhorSol;

}

Solucao DescidaTrocaBI(Instancia& inst, Solucao& sol)
{
    Solucao melhorSol = sol;
    Solucao atualSol = sol;
    float atualFO,melhorFO = avalia(inst,melhorSol);

    bool melhorou = false;
    do
    {
        atualSol = BITroca(inst, atualSol);
        atualFO = avalia(inst,atualSol);
        if(atualFO < melhorFO)
        {
            cout<<"Melhora BI-Troca -  FO: "<< atualFO << endl;
            melhorSol = atualSol;
            melhorFO = atualFO;
            melhorou = true;
        }
        else
        {
            melhorou = false;
        }
    } while (melhorou);
    
    return melhorSol;
}

Solucao DescidaTrocaBIO1(Instancia& inst, Solucao& sol)
{
    Solucao melhorSol = sol;
    Solucao atualSol = sol;
    float atualFO,melhorFO = avalia(inst,melhorSol);

    bool melhorou = false;
    do
    {
        atualSol = BITrocaO1(inst, atualSol);
        atualFO = avalia(inst,atualSol);
        if(atualFO < melhorFO)
        {
            cout<<"Melhora BI-Troca (O1) -  FO: "<< atualFO << endl;
            melhorSol = atualSol;
            melhorFO = atualFO;
            melhorou = true;
        }
        else
        {
            melhorou = false;
        }
    } while (melhorou);
    
    return melhorSol;
}