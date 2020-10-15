#include "juego.h"

Juego::Juego(int l, int a, int pb,QWidget *parent):QDialog(parent),buscaminas(l,a,pb){
    int i,j;
    int filas=buscaminas.getFilas();
    int columnas=buscaminas.getColumnas();

    //int totalBotones=filas*columnas;
    buscaminas.iniciarMatriz();

    result = new QLabel(this);
    result->setFont(QFont("Segoe UI Light", 12));

    layoutVGeneral = new QVBoxLayout;
    layoutVGeneral->setSpacing(0);
    for(i=0;i<filas;i++){
        layoutHBotones[i]=new QHBoxLayout;
        layoutHBotones[i]->setSpacing(0);
        for(j=0;j<columnas;j++){
            arrayBotones[i][j] = new QPushButton(this);
            arrayBotones[i][j]->setFixedSize(20,20);
            arrayBotones[i][j]->setFont(QFont("Segoe UI Light", 10));
            arrayBotones[i][j]->setObjectName(QString::number(i)+","+QString::number(j));
            layoutHBotones[i]->addWidget(arrayBotones[i][j]);
            connect( arrayBotones[i][j], &QPushButton::clicked, [=] { botonAction(arrayBotones[i][j]);} );
        }
        layoutVGeneral->addLayout(layoutHBotones[i]);
    }


    layoutHReiniciarNewGame = new QHBoxLayout;

    reiniciar= new QPushButton("Reiniciar",this);
    reiniciar->setFont(QFont("Segoe UI Light", 12));
    connect(reiniciar, SIGNAL(clicked()), this, SLOT(reiniciarAction()));

    newGame= new QPushButton("Nuevo Juego",this);
    newGame->setFont(QFont("Segoe UI Light", 12));
    connect(newGame, SIGNAL(clicked()), this, SLOT(close()));

    layoutHReiniciarNewGame->addWidget(result);
    layoutHReiniciarNewGame->addWidget(reiniciar);
    layoutHReiniciarNewGame->addWidget(newGame);
    layoutVGeneral->addLayout(layoutHReiniciarNewGame);

    setLayout(layoutVGeneral);
}

void Juego::reiniciarAction(){
    buscaminas.iniciarMatriz();
    for(int i=0;i<buscaminas.getFilas();i++){
        for(int j=0;j<buscaminas.getColumnas();j++){
            arrayBotones[i][j]->setText(nullptr);
            arrayBotones[i][j]->setEnabled(true);
            arrayBotones[i][j]->setStyleSheet("");
            buscaminas.apagarCasilla(i,j);
        }
    }
}

void Juego::botonAction(QPushButton* button){
    result->setText(button->objectName());
    int fila=button->objectName().split(',')[0].toInt();
    int columna=button->objectName().split(',')[1].toInt();
    try {
        int valorIJ= buscaminas.getValorIJ(fila,columna);
        if(valorIJ>=10){
            mostrarTodo();
            QMessageBox::information(this,"Loser","Has perdido jeje");
            reiniciarAction();
        }else{
            if(valorIJ!=0) arrayBotones[fila][columna]->setText(QString::number(valorIJ));
            arrayBotones[fila][columna]->setEnabled(false);
            if(valorIJ==0){
                buscaminas.recursividadAbrirCasillas(fila,columna);
                bloquearCasilla();
            }
            buscaminas.prenderCasilla(fila,columna);
        }
    } catch (BuscaminasException e) {
        result->setText(e.getInfo());
    }
}

void Juego::mostrarTodo(){
    int i,j;
    int filas=buscaminas.getFilas();
    int columnas=buscaminas.getColumnas();
    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            if(buscaminas.getValorIJ(i,j)>=10) arrayBotones[i][j]->setStyleSheet("background-color: black;");
            buscaminas.prenderCasilla(i,j);

        }

    }
}

void Juego::bloquearCasilla(){
    int i,j;
    int filas=buscaminas.getFilas();
    int columnas=buscaminas.getColumnas();
    for(i=0;i<filas;i++)
        for(j=0;j<columnas;j++)
           if(buscaminas.casillaPrendida(i,j)) arrayBotones[i][j]->setEnabled(false);
}

