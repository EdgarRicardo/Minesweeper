#include <iostream>
#include<string>
#include "buscaminas.h"

using namespace std;

int main()
{
    int largo=0;
    int ancho=0;
    int porcentajeBombas=0;
    string coordenadas;
    int i,j;
    bool win;
    cout<<"***BIENVENIDO AL BUSCAMINAS EN CONSOLA***";
    cout<<"\nDame el largo del tablero (Entre 5-30 filas): "; cin>>largo;
    cout<<"Dame el ancho del tablero (Entre 5-50 columnas): "; cin>>ancho;
    cout<<"Dame el porcentaje de bombas deseadas (Entre 5-50 %): "; cin>>porcentajeBombas;
    try{
        Buscaminas bm(largo,ancho,porcentajeBombas);
        bm.iniciarMatriz();

        ///Este es solo para ver donde estan las bombas
        bm.verBombas();
        cout<<"\nEl tablero aqui arriba es el tablero mostrando las bombas (representadas por una X)\n\n";
        do{
            bm.imprimirMatriz();
            cout<<"\nDame la coordenada a activar (Ex."<<largo/2<<","<<ancho/2<<"): "; cin>>coordenadas;
            int posComa=coordenadas.find(",");
            i=stoi(coordenadas.substr(0,posComa));
            j=stoi(coordenadas.substr(posComa+1));
            if(i>bm.getFilas() || j>bm.getColumnas() || i<0 || j<0) throw BuscaminasException("Dato innexistente");
            bm.recursividadAbrirCasillas(i,j);
            win=bm.win();
        }  while(!bm.isBomba(i,j) && !win);
        bm.verBombas();
        if (win) cout<<"\nGanaste campeon!!!";
        else cout<<"\nLoser!!!";
    }catch (BuscaminasException e) {
        cout<<"\n"<<e.getInfo();
    }


    return 0;
}
