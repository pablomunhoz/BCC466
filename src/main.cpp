#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include <chrono>
#include "Instancia.h"
#include "Solucao.h"
#include "Avaliador.h"
#include "Menu.h"
#include "HeuristicasConstrutivas.h"
#include "BuscasLocais.h"
#include "MultiStart.h"
#include "GRASP.h"
#include "SA.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Instancia inst;
    Solucao sol;
    float fo,t0;
    int SAmax; 
    string nomeArq = argv[1];
    float tempo;

    int op, hc, bl, mh;
    do
    {
        op = menuPrincipal();
        switch (op)
        {
            case 1:
            { 
                leInstancia(inst, nomeArq);
                printf("\n\n Arquivo carregado com sucesso!\n\n");
                /*
                sol.push_back(0);
                sol.push_back(2);
                sol.push_back(1);
                sol.push_back(3);

                float fo = avalia(inst, sol);

                cout<< "Valor da FO: " << fo << endl;
                */
            }    
            break;
            case 2: 
                hc = menuHeuristicaConstrutiva();
                switch (hc)
                {                 
                    case 1:
                        cout<< "  ---- VMP --- " <<endl;
                        sol = VizinhoMaisProximo(inst);
                        impSol(sol);
                        fo = avalia(inst, sol);
                        printf("\nFO: %.2f\n", fo);
                    break;
                    case 2:
                        cout << " ---- IMB ---- " <<endl;
                        sol = InsercaoMaisBarata(inst);
                        impSol(sol);
                        fo = avalia(inst, sol);
                        printf("\nFO: %.2f\n", fo);
                    break;
                    case 3:
                        cout << " ---- Randômico ---- " <<endl;
                        sol = Randomica(inst);
                        impSol(sol);
                        fo = avalia(inst, sol);
                        printf("\nFO: %.2f\n", fo);
                    break;
                    case 4:
                        cout << " ---- VMP Parcialmente Guloso ---- " <<endl;
                        sol = VizinhoMaisProximoParcialmenteGuloso(inst,3);
                        impSol(sol);
                        fo = avalia(inst, sol);
                        printf("\nFO: %.2f\n", fo);
                    break;
                    case 5:
                        cout << " ---- IMB Parcialmente Guloso ---- " <<endl;
                        sol = InsercaoMaisBarataParcialmenteGuloso(inst,3);
                        impSol(sol);
                        fo = avalia(inst, sol);
                        printf("\nFO: %.2f\n", fo);
                    break;                
                    case 6:
                        cout << " ---- IMB GRASP ---- " <<endl;
                        
                    break;                
                    case 7:
                        cout << " ---- IMB Parcialmente Guloso ---- " <<endl;
                        sol = InsercaoMaisBarataParcialmenteGuloso(inst,3);
                        impSol(sol);
                        fo = avalia(inst, sol);
                        printf("\nFO: %.2f\n", fo);
                    break;                
                    default:
                        cout << "Opção inválida" <<endl;
                    break;
                }
            break;
            case 3:
                bl = menuBuscaLocal();
                switch (bl)
                {
                    case 1:
                         cout<<" ### Busca Local Troca (BI) ### " <<endl;
                         sol = DescidaTrocaBI(inst, sol);
                         impSol(sol);
                         fo = avalia(inst, sol);
                         printf("\nFO: %.2f\n", fo);
                    break;
                    case 2:
                         cout<<" ### Busca Local Troca (BI - O(1)) ### " <<endl;
                         sol = DescidaTrocaBIO1(inst, sol);
                         impSol(sol);
                         fo = avalia(inst, sol);
                         printf("\nFO: %.2f\n", fo);
                    break;
                    case 4:
                         cout<<" ### Busca Local Realocacao (BI) ### " <<endl;
                         sol = DescidaRealocacaoBI(inst, sol);
                         impSol(sol);
                         fo = avalia(inst, sol);
                         printf("\nFO: %.2f\n", fo);
                    break;
                    default:
                        cout<< "Opção Inválida" << endl;
                    break;
                }    
            break;
            case 4:
                mh = menuMetaheuristicas();
                switch (mh)
                {
                    case 1:
                         cout<<" ### MultiStart ### " <<endl;
                         sol = MultiStart(inst,10000);
                         impSol(sol);
                         fo = avalia(inst, sol);
                         printf("\nFO MultiStart: %.2f\n", fo);
                    break;
                    case 2:
                         cout<<" ### GRASP ### " <<endl;
                         sol = GRASP(inst,10000,0.2);
                         impSol(sol);
                         fo = avalia(inst, sol);
                         printf("\nFO GRASP: %.2f\n", fo);
                    break;
                    case 3:
                    {
                         cout<<" ### SA ### " <<endl;
                         auto inicio = chrono::high_resolution_clock::now();
                         sol = VMP_GRASP(inst,0.2);
                         SAmax = 1000;
                         //calculando a temperatura inicial
                         t0 = SA_temperaturaInicial(inst,sol,SAmax,2.0,0.85, 3);
                         sol = SA(inst,sol,0.99,SAmax,t0,0.01);
                         auto fim = chrono::high_resolution_clock::now();
                         tempo = chrono::duration_cast<chrono::milliseconds>(fim-inicio).count();
                         tempo/=1000;
                         impSol(sol);
                         fo = avalia(inst, sol);
                         printf("\nFO SA: %.2f tempo: %.3fs\n", fo, tempo);
                    }
                    break;
                    default:
                        cout<< "Opção Inválida" << endl;
                    break;
                }    
            break;
            case 0:
                cout << "Até a próxima!!!" << endl;
            break;
            default:
                printf("Algo deu errado!\n");
            break;
        }
    }while(op != 0);

    return 0; 
}
