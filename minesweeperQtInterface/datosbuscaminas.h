#ifndef DATOSBUSCAMINAS_H
#define DATOSBUSCAMINAS_H

#include "headerqt.h"
#include "buscaminasmatriz.h"
#include "juego.h"

class DatosBuscaminas : public QDialog{
    Q_OBJECT
    QLabel*  db;

    QVBoxLayout* layoutVGeneral;

    QHBoxLayout* layoutHLargo;
    QLabel*  largo;
    QSlider* largoLE;
    QLabel*  valorLargo;

    QHBoxLayout* layoutHAncho;
    QLabel*  ancho;
    QSlider* anchoLE;
    QLabel*  valorAncho;

    QHBoxLayout* layoutHporcentajeBombas;
    QLabel*  porcentajeBombas;
    QSlider* porcentajeBombasLE;
    QLabel*  valorPB;

    QHBoxLayout* layoutHOkCancelarResult;
    QPushButton* ok;
    QPushButton* cancelar;
    QLabel* result;

public:
    explicit DatosBuscaminas(QWidget *parent = nullptr);
signals:
private slots:
    void okAction();
};

#endif // DATOSBUSCAMINAS_H
