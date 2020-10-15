#include "datosbuscaminas.h"

DatosBuscaminas::DatosBuscaminas(QWidget *parent):QDialog(parent){
    db =new QLabel("Parametros del juego",this);
    db->setFont(QFont("Segoe UI Light", 20));

    largo =new QLabel("Largo",this);
    largo->setFont(QFont("Segoe UI Light", 12));
    valorLargo =new QLabel("5",this);
    valorLargo->setFont(QFont("Segoe UI Light", 12));

    ancho =new QLabel("Ancho",this);
    ancho->setFont(QFont("Segoe UI Light", 12));
    valorAncho =new QLabel("5",this);
    valorAncho->setFont(QFont("Segoe UI Light", 12));

    porcentajeBombas = new QLabel("Porcentaje de Bombas",this);
    porcentajeBombas->setFont(QFont("Segoe UI Light", 12));
    valorPB =new QLabel("5",this);
    valorPB->setFont(QFont("Segoe UI Light", 12));

    result = new QLabel(this);
    result->setFont(QFont("Segoe UI Light", 12));

    largoLE = new QSlider(Qt::Horizontal,this);
    largoLE->setTickPosition(QSlider::TicksBelow);
    largoLE->setTickInterval(10);
    largoLE->setMinimum(5);
    largoLE->setMaximum(30);

    anchoLE = new QSlider(Qt::Horizontal,this);
    anchoLE->setTickPosition(QSlider::TicksBelow);
    anchoLE->setTickInterval(10);
    anchoLE->setMinimum(5);
    anchoLE->setMaximum(50);

    porcentajeBombasLE = new QSlider(Qt::Horizontal,this);
    porcentajeBombasLE->setTickPosition(QSlider::TicksBelow);
    porcentajeBombasLE->setTickInterval(10);
    porcentajeBombasLE->setMinimum(5);
    porcentajeBombasLE->setMaximum(50);

    ok= new QPushButton("Start");
    ok->setFont(QFont("Segoe UI Light", 12));
    connect(ok,SIGNAL(clicked()),this, SLOT(okAction()));

    connect(largoLE, SIGNAL(valueChanged(int)), valorLargo, SLOT(setNum(int)));
    connect(anchoLE, SIGNAL(valueChanged(int)), valorAncho, SLOT(setNum(int)));
    connect(porcentajeBombasLE, SIGNAL(valueChanged(int)), valorPB, SLOT(setNum(int)));


    cancelar= new QPushButton("Cancelar",this);
    cancelar->setFont(QFont("Segoe UI Light", 12));
    connect(cancelar, SIGNAL(clicked()), this, SLOT(close()));

    layoutHLargo = new QHBoxLayout;
    layoutHAncho = new QHBoxLayout;
    layoutHporcentajeBombas = new QHBoxLayout;
    layoutHOkCancelarResult = new QHBoxLayout;
    layoutVGeneral = new QVBoxLayout;

    layoutHLargo->addWidget(largo);
    layoutHLargo->addWidget(largoLE);
    layoutHLargo->addWidget(valorLargo);

    layoutHAncho->addWidget(ancho);
    layoutHAncho->addWidget(anchoLE);
    layoutHAncho->addWidget(valorAncho);

    layoutHporcentajeBombas->addWidget(porcentajeBombas);
    layoutHporcentajeBombas->addWidget(porcentajeBombasLE);
    layoutHporcentajeBombas->addWidget(valorPB);

    layoutHOkCancelarResult->addWidget(result);
    layoutHOkCancelarResult->addWidget(cancelar);
    layoutHOkCancelarResult->addWidget(ok);

    layoutVGeneral->addWidget(db);
    layoutVGeneral->addLayout(layoutHLargo);
    layoutVGeneral->addLayout(layoutHAncho);
    layoutVGeneral->addLayout(layoutHporcentajeBombas);
    layoutVGeneral->addLayout(layoutHOkCancelarResult);

    setLayout(layoutVGeneral);
}

void DatosBuscaminas::okAction(){
    try {
        int largo,ancho,porcentajeBombas;
        largo = valorLargo->text().toInt();
        ancho = valorAncho->text().toInt();
        porcentajeBombas = valorPB->text().toInt();
        Buscaminas bm(largo,ancho,porcentajeBombas);
        //bm.iniciarMatriz();
        Juego *game=new Juego(largo,ancho,porcentajeBombas,this);
        game->setModal(true);
        game->setWindowFlag(Qt::WindowCloseButtonHint,false);
        game->show();
    } catch (BuscaminasException e) {
        result->setText(e.getInfo());
    }
}
