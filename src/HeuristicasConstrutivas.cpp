#include "HeuristicasConstrutivas.h"

int melhorCandidato(Instancia& inst, set<int>& C, int idUltimo)
{
    int idMelhor;
    float custoMelhor = MAXFLOAT;
    set<int>::iterator it;
    for(it = C.begin(); it != C.end(); it++)
    {
        if( inst.distancia[idUltimo][*(it)] < custoMelhor)
        {
            custoMelhor = inst.distancia[idUltimo][*(it)];
            idMelhor = *it;
        }
    }

    return idMelhor;
}

Solucao VizinhoMaisProximo(Instancia& inst)
{
    Solucao sol;
    //criando minha lista de candidatos
    set<int> C;
    //inicializando minha lista de candidatos
    for(int i = 1; i < inst.n; i++)
    {
        C.insert(i);
    }
    sol.push_back(0); //adicionando a cidade origem do Caixeiro
 
    while(! C.empty())
    {
        int id = melhorCandidato(inst, C, sol.at(sol.size()-1));
        sol.push_back(id);
        C.erase(id);
    }
 
    return sol;
}


set<pair<int,float>,compVMP> atualiza_LRC_VMP(Instancia& inst, set<int>& C, int ultimoId)
{
    //criando a lista restrita de candidatos
    set<pair<int,float>,compVMP> LRC;
    
    for(auto it: C)
    {
        LRC.insert(make_pair((it), inst.distancia[ultimoId][it]));
    }


    return LRC;
}


Solucao VizinhoMaisProximoParcialmenteGuloso(Instancia& inst, int k)
{
    Solucao sol;
    //criando minha lista de candidatos
    set<int> C;
    //inicializando minha lista de candidatos
    for(int i = 1; i < inst.n; i++)
    {
        //adicionando os candidatos já com a distância calculada para o nó origem 0
        C.insert(i); 
    }
    sol.push_back(0); //adicionando a cidade origem do Caixeiro
 
    while(! C.empty())
    {
        //atualiza a lista restrita de candidatos à partir dos candidatos ainda disponíveis
        set<pair<int,float>,compVMP> LRC = atualiza_LRC_VMP(inst,C, sol.at(sol.size()-1));

        //impressão da LRC
        /*for(auto it: LRC)
        {
            cout<<" id: " << it.first << " value: " << it.second << endl;
        }*/
        

        //sorteando um dos melhores 'k' elementos
        int pos = rand()%k;
        int id = next(LRC.begin(),pos)->first;
        //adicionando o elemento à solução
        sol.push_back(id);
        //removendo o elemento já adicionado da lista de candidatos
        C.erase(id);
    }
 
    return sol;
}




float melhorCandidatoIMB(Instancia& inst, set<int>& C,Solucao& sol,int& id,int& pos)
{
    float custoMelhor = MAXFLOAT, custo;   
    
    for(int i = 0; i < sol.size(); i++)
    {   int proxCidade = i+1;
        if(i+1 == sol.size())//ultima posição
        {
            proxCidade = 0;
        }
        set<int>::iterator it;
        for(it = C.begin(); it != C.end(); it++)
        {
            custo = inst.distancia[sol.at(i)][*(it)]+inst.distancia[*(it)][sol.at(proxCidade)] - inst.distancia[sol.at(i)][sol.at(proxCidade)];            
           
            if( custo < custoMelhor)
            {
                custoMelhor = custo;
                id = *it;
                pos = i+1;
            }
        }
    }
    return custoMelhor;
}


Solucao InsercaoMaisBarata(Instancia& inst)
{
    //variaveis que controlam o id da cidade ser inserida e sua posição
    int id, pos;
    //variavel que controla o valor da FO
    float fo = 0;
    //criando uma solução vazia
    Solucao sol;
    //criando uma lista de candidatos
    set<int> C;
    //inicializando minha lista de cadidatos
    for(int i = 2; i < inst.n; i++)
    {
        C.insert(i);
    }
    //inicializando minha solução com a cidade origem e a cidade 1
    sol.push_back(0);
    sol.push_back(1);
    //atualizando a FO
    fo = inst.distancia[sol.at(0)][sol.at(1)]+inst.distancia[sol.at(1)][sol.at(0)];
    while( ! C.empty())
    {
        fo+=melhorCandidatoIMB(inst, C, sol, id, pos);        
        sol.insert(sol.begin()+pos, id);
        C.erase(id);
    }

    printf("\nFO calculada: %.2f\n", fo);

    return sol;

}



set<pair<int,CustoPos>,compIMB> atualiza_LRC_IMB(Instancia& inst, set<int>& C,Solucao& sol)
{
    float custo;   
    set<pair<int,CustoPos>,compIMB> LRC;

    for(int i = 0; i < sol.size(); i++)
    {   int proxCidade = i+1;
        if(i+1 == sol.size())//ultima posição
        {
            proxCidade = 0;
        }
        set<int>::iterator it;

        for(it = C.begin(); it != C.end(); it++)
        {
            custo = inst.distancia[sol.at(i)][*(it)]+inst.distancia[*(it)][sol.at(proxCidade)] - inst.distancia[sol.at(i)][sol.at(proxCidade)];
            CustoPos cp;
            cp.custo = custo;
            cp.pos = i+1;
            LRC.insert(make_pair(*it, cp));        
            
        }
    }
    return LRC;
}

Solucao InsercaoMaisBarataParcialmenteGuloso(Instancia& inst, int k)
{
    //variaveis que controlam o id da cidade ser inserida e sua posição
    int id, pos;
    //criando uma solução vazia
    Solucao sol;
    //criando uma lista de candidatos
    set<int> C;
    //inicializando minha lista de cadidatos
    for(int i = 2; i < inst.n; i++)
    {
        C.insert(i);
    }
    //inicializando minha solução com a cidade origem e a cidade 1
    sol.push_back(0);
    sol.push_back(1);
    while( ! C.empty())
    {
        //atualizando a lista restrita de candidatos
        set<pair<int, CustoPos>, compIMB> LRC = atualiza_LRC_IMB(inst, C, sol);
        
        //impressão da LRC
        /*cout<<" ----------- ###### -----------------"<<endl;
        for(auto it: LRC)
        {
            cout<<" id: " << it.first << " value: " << it.second.custo << " pos: " << it.second.pos <<endl;
            
        }
        //*/

         //sorteando um dos melhores 'k' elementos
        int index = rand()%k;
        auto it = next(LRC.begin(), index);
        int id = it->first;
        int pos = it->second.pos;

        //adicionando o elemento à solução
        sol.insert(sol.begin()+pos, id);
        C.erase(id);
    }

    return sol;
}

Solucao Randomica(Instancia& inst)
{
    Solucao sol;

    for(int i = 0; i < inst.n; i++)
    {
        sol.push_back(i);
    }
    
    random_shuffle(sol.begin(), sol.end());

    return sol;

}


Solucao VMP_GRASP(Instancia& inst, float alpha)
{
    Solucao sol;
    //criando minha lista de candidatos
    set<int> C;
    //inicializando minha lista de candidatos
    for(int i = 1; i < inst.n; i++)
    {
        //adicionando os candidatos já com a distância calculada para o nó origem 0
        C.insert(i); 
    }
    sol.push_back(0); //adicionando a cidade origem do Caixeiro
 
    while(! C.empty())
    {
        //atualiza a lista restrita de candidatos à partir dos candidatos ainda disponíveis
        set<pair<int,float>,compVMP> LRC = atualiza_LRC_VMP(inst,C, sol.at(sol.size()-1));

        //impressão da LRC
        /*for(auto it: LRC)
        {
            cout<<" id: " << it.first << " value: " << it.second << endl;
        }*/
       //pegando o menor e maior custo de inserção
        float gmin,gmax;
        auto it = LRC.begin();
        gmin = it->second;
        it = LRC.end();
        it--;
        gmax = it->second;

        //calculando o limitante da LRC
        float limitante = gmin + alpha*(gmax-gmin);

        //contando o numero de elemetos com custo menor que o limitante
        int cont=0;
        for( auto i: LRC)
        {
            if(i.second <= limitante)
                cont++;
            else
                break;
        }

        //sorteando um dos melhores 'k' elementos
        int pos = rand()%cont;
        int id = next(LRC.begin(),pos)->first;
        //adicionando o elemento à solução
        sol.push_back(id);
        //removendo o elemento já adicionado da lista de candidatos
        C.erase(id);
    }
 
    return sol;

}