#include "menu.h"

 //!< Interfaz pricipal
Menu::Menu(QWidget *parent):QMainWindow(parent){
    int x=60;
    menuO =new QLabel("Buscaminas",this);
    menuO->setGeometry(150,20,200,40); // X Y Dimensiones
    menuO->setFont(QFont("Segoe UI Light", 20));

    newGame=new QPushButton("New Game",this);
    newGame->setGeometry(x,70,300,30);
    newGame->setFont(QFont("Segoe UI Light", 12));
    connect(newGame,SIGNAL(clicked()),this, SLOT(actionNewGame()));

    stats=new QPushButton("Stats",this);
    stats->setGeometry(x,110,300,30);
    stats->setFont(QFont("Segoe UI Light", 12));
    connect(stats,SIGNAL(clicked()),this, SLOT(actionStats()));

    exit= new QPushButton("Exit",this);
    exit->setGeometry(x+120,150,80,30);
    exit->setFont(QFont("Segoe UI Light", 12));
    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
}

void Menu::actionNewGame(){
    DatosBuscaminas *db=new DatosBuscaminas(this);
    db->setFixedSize(400,250);
    db->setModal(true);
    db->setWindowFlag(Qt::WindowCloseButtonHint,false);
    db->show();
}

void Menu::actionStats(){
    /*DatosBuscaminas *c=new DatosBuscaminas(this);
    c->setFixedSize(400,300);
    c->setModal(true);
    c->setWindowFlag(Qt::WindowCloseButtonHint,false);
    c->show();*/
}

