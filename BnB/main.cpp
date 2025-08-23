#include <iostream>
#include <queue>
#include <list>
#include "EstadoAsignacionBnB.h"
#define N 4
using namespace std;

struct comparator
{
    bool operator()(EstadoAsignacionBnB &p, EstadoAsignacionBnB &q) const
    {
        return p.getCotaLocal() < q.getCotaLocal();
    }
};

list <EstadoAsignacionBnB> expandir (const EstadoAsignacionBnB & e, int **B)
{

    list <EstadoAsignacionBnB> hijos;
    for (int h=0; h<N; h++)
    {
        if (!e.estaAsignada(h))
        {
            EstadoAsignacionBnB nuevo(e);
            nuevo.asignar(h,B);
            hijos.push_back(nuevo);
        }
    }
    return hijos;
}

EstadoAsignacionBnB asignacionBnB(const EstadoAsignacionBnB& inicial,int cota_global,int** B)
{
    EstadoAsignacionBnB solucion(N);

    priority_queue<EstadoAsignacionBnB,vector<EstadoAsignacionBnB>,comparator> vivos;
    vivos.push(inicial);
    list <EstadoAsignacionBnB> hijos;

    bool encontre = false;

    while (!vivos.empty() && ! encontre)
    {

        EstadoAsignacionBnB en_expansion = vivos.top();
        vivos.pop();

        if (en_expansion.getCotaLocal() > cota_global || en_expansion.getNivel()==-1)
        {

            hijos = expandir (en_expansion,B);

            for (h: hijos)
            {
                int aux_cota = h.getCotaLocal();
                if (aux_cota  > cota_global )
                {
                    if (h.getNivel()  == N-1 )
                    {
                        solucion = h;
                        cota_global = aux_cota;
                    }
                    else
                        vivos.push(h);
                }
            }
        }
        else
            encontre = true;
    }
    return solucion;
}
void iniciar_beneficios(int ** B)
{
    B[0]=new int[N];
    B[0][0]=25;
    B[0][1]=40;
    B[0][2]=30;
    B[0][3]=10;
    B[1]=new int[N];
    B[1][0]=40;
    B[1][1]=35;
    B[1][2]=5;
    B[1][3]=50;
    B[2]=new int[N];
    B[2][0]=15;
    B[2][1]=5;
    B[2][2]=50;
    B[2][3]=40;
    B[3]=new int[N];
    B[3][0]=10;
    B[3][1]=35;
    B[3][2]=40;
    B[3][3]=30;
}
int getCotaInicial(int **B)
{
    int cota_inicial = 0;
    for (int i=0; i<N; i++)
        cota_inicial+=B[i][i];
    return cota_inicial;
}
int main()
{
    int **B = new int *[N];
    iniciar_beneficios(B);

    int cota_inicial = getCotaInicial(B);

    EstadoAsignacionBnB estado_inicial(N);
    EstadoAsignacionBnB estado_solucion = asignacionBnB(estado_inicial,cota_inicial,B);

    string * pintas = new string[N];
    pintas[0] = "Porter";
    pintas[1] = "IPA";
    pintas[2] = "Blonde";
    pintas[3] = "Amber";
    string * tapas = new string[N];
    tapas[0] = "Rabas";
    tapas[1] = "Hamburguesa";
    tapas[2] = "Papas";
    tapas[3] = "Verduras";

    estado_solucion.mostrar(pintas,tapas);

    delete[] tapas;
    delete[] pintas;
    for (int i=0; i<N; i++)
        delete[] B[i];
    delete[] B;

    return 0;
}
