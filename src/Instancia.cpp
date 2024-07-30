#include "Instancia.h"

void calculaDistancias(Instancia& inst)
{
    for(int i = 0; i < inst.n; i++)
    {
        for(int j = 0; j < inst.n; j++)
        {
            inst.distancia[i][j] = sqrt(pow(inst.coords[i].x - inst.coords[j].x, 2) + pow(inst.coords[i].y - inst.coords[j].y, 2));
        }
    }

}

void leInstancia(Instancia& inst, string nome_arq)
{
    ifstream arq(nome_arq);
    if(arq.is_open())
    {
        // número de cidades
        arq >> inst.n;

        // criando o vetor de pontos
        inst.coords = new Ponto[inst.n];        

        //lendo as coordenadas
        for(int i = 0; i < inst.n; i++)
        {
            arq >> inst.coords[i].id >> inst.coords[i].x >> inst.coords[i].y;
        }

        //criando a matriz de distâncias
        inst.distancia = new float*[inst.n];
        for(int i = 0; i < inst.n; i++)
        {
            inst.distancia[i] = new float[inst.n];
        }

        //calculando a matriz
        calculaDistancias(inst);
    }
}