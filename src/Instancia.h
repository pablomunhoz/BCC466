#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef struct sPonto
{
    float x,y;
    int id;
}Ponto;

typedef struct sInstancia
{
    int n;
    float** distancia;
    Ponto* coords;
}Instancia;

void calculaDistancias(Instancia& inst);

void leInstancia(Instancia& inst, string nome_arq);

#endif /*INSTANCIA_H*/