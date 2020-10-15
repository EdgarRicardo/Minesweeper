#ifndef JUEGO_H
#define JUEGO_H

#include "headerqt.h"
#include "buscaminasmatriz.h"

class Juego : public QDialog{
    Q_OBJECT
    Buscaminas  buscaminas;
    QVBoxLayout* layoutVGeneral;
    QPushButton *arrayBotones[100][100];
    QHBoxLayout* layoutHBotones[100];
    QHBoxLayout* layoutHReiniciarNewGame;
    QPushButton* reiniciar;
    QPushButton* newGame;
    QLabel* result;
    int ganaste=0;
public:
    Juego(int l, int a, int pb,QWidget *parent = nullptr);
    void mostrarTodo();
    void bloquearCasilla();
signals:
private slots:
    void reiniciarAction();
    void botonAction(QPushButton*);
};


#endif // JUEGO_H
