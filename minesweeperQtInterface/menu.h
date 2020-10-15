#ifndef MENU_H
#define MENU_H

#include "headerqt.h"
#include "datosbuscaminas.h"

/**
 *  Class du Menu des Options
 */
class Menu: public QMainWindow{
    Q_OBJECT
    QLabel*  menuO;
    QPushButton* newGame;
    QPushButton* stats;
    QPushButton* exit;
public:
    explicit Menu(QWidget *parent = nullptr);
signals:
private slots:
    //! Action para un nuevo juego
    void actionNewGame();
    void actionStats();
};

#endif // MENU_H
