#ifndef HEURISTICASCONSTRUTIVAS_H
#define HEURISTICASCONSTRUTIVAS_H

#include <set>
#include <algorithm>
#include <random>
#include <utility> //pair

#include "Instancia.h"
#include "Solucao.h"

using namespace std;

typedef struct sCustoPos
{
    float custo;
    int pos;
}CustoPos;

// Comparador de pares para a Lista de Candidatos para o Vizinho Mais Próximo
struct compVMP {
    // Sobreponto o operador ()
    bool operator()(const pair<int, float>& p1,
                    const pair<int, float>& p2) const
    {
        // nova definição de comparação
        return p1.second < p2.second;
    }
};
// Comparador de pares para a Lista de Candidatos para a Inserção Mais Barata
struct compIMB {
    // Sobreponto o operador ()
    bool operator()(const pair<int, CustoPos>& p1,
                    const pair<int, CustoPos>& p2) const
    {
        // nova definição de comparação
        return p1.second.custo < p2.second.custo;
    }
};

//retorno o ID do candidato com melhor avaliacao
int melhorCandidato(Instancia& inst, set<int>& C, int idUltimo);
Solucao VizinhoMaisProximo(Instancia& inst);

set<pair<int,float>,compVMP> atualiza_LRC_VMP(Instancia& inst, set<int>& C, int ultimoId);
Solucao VizinhoMaisProximoParcialmenteGuloso(Instancia& inst, int k);

//retorna o melhor custo, além de atualizar as variaveis id e pos com os melhores valores
float melhorCandidatoIMB(Instancia& inst, set<int>& C,Solucao& sol,int& id,int& pos);
Solucao InsercaoMaisBarata(Instancia& inst);

set<pair<int,CustoPos>,compIMB> atualiza_LRC_IMB(Instancia& inst, set<int>& C,Solucao& sol);
Solucao InsercaoMaisBarataParcialmenteGuloso(Instancia& inst, int k);
//construção randômica
Solucao Randomica(Instancia& inst);

Solucao VMP_GRASP(Instancia& inst, float alpha);

#endif /*HEURISTICASCONSTRUTIVAS_H*/