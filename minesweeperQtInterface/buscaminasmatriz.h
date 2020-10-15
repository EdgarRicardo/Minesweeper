#ifndef BUSCAMINASMATRIZ_H
#define BUSCAMINASMATRIZ_H
#include "headerqt.h"

class BuscaminasException {
public:
    BuscaminasException(const QString& message) :info(message) {}
    QString getInfo() const { return info; }
private:
    QString info;
};

/*class Casilla{
    int abierta=0;
    int valor=0;
public:
    Casilla(int val);
    void abrir(){abierta=1;}
    void cerrar(){abierta=0;}
    void updateVal(int val) {valor=val;}
    void operator++() {valor=valor+1;}
    int getVal() const {return valor;}
};*/

class Buscaminas {
    int filas;
    int columnas;
    int porcentajeBombas;
    int **matriz;
    bool **casillasPrendidas;
public:
    Buscaminas(int f, int c, int porcetajeBombas);
    ~Buscaminas();
    int numeroBombas() const { return filas*columnas*porcentajeBombas/100;}
    int getFilas() const { return filas; }
    int getColumnas() const {return columnas;}
    int getValorIJ(int i, int j) const;
    bool casillaPrendida(int i, int j) const {return casillasPrendidas[i][j];}
    void prenderCasilla(int i, int j) {casillasPrendidas[i][j]=true;}
    void apagarCasilla(int i, int j) {casillasPrendidas[i][j]=false;}
    void iniciarMatriz();
    void recursividadAbrirCasillas(int i,int j);
};



#endif // BUSCAMINASMATRIZ_H
