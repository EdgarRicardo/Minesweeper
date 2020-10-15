#ifndef BUSCAMINAS_H_INCLUDED
#define BUSCAMINAS_H_INCLUDED
#include <iostream>
#include<string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class BuscaminasException {
public:
    BuscaminasException(const string& message) :info(message) {}
    string getInfo() const { return info; }
private:
    string info;
};

class Casilla{
    bool activa=false;
    int valor=0; /// 10 indicara que es bomba
public:
    //Casilla(int val);
    void abrir(){activa=true;}
    void newVal(int val) {valor=val;}
    void operator++(int) {valor=valor+1;}
    int getVal() const {return valor;}
    bool isActivated() const {return activa;}
    bool isBomb() const {return valor>=10;}
};

class Buscaminas {
    int filas;
    int columnas;
    int porcentajeBombas;
    int numCasillasAbiertas=0;
    Casilla **matriz=nullptr;
public:
    Buscaminas(int f, int c, int porcetajeBombas);
    ~Buscaminas();
    int numeroBombas() const { return filas*columnas*porcentajeBombas/100;}
    int getFilas() const { return filas; }
    int getColumnas() const {return columnas;}
    int getValorIJ(int i, int j) const;

    bool casillaPrendida(int i, int j) const {return matriz[i][j].isActivated();}
    void prenderCasilla(int i, int j) {matriz[i][j].abrir();}
    bool isBomba(int i, int j) const {return matriz[i][j].isBomb();}

    void iniciarMatriz();
    void verBombas();
    void recursividadAbrirCasillas(int i,int j);
    void imprimirMatriz();
    bool win() const {return numeroBombas()+numCasillasAbiertas==filas*columnas;}
};

#endif // BUSCAMINAS_H_INCLUDED
